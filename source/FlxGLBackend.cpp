#include "flixel++/Common.hpp"
#include "flixel++/FlxBackends.hpp"
#include "flixel++/FlxG.hpp"

#include "flixel++/FlxLog.hpp"
#include "flixel++/FlxMacros.hpp"

#include "assets/logoBlue.h"
#include "assets/default.h"

using Flx::Globals::game, Flx::Globals::width, Flx::Globals::height;

#ifdef FLIXEL_OPENGL

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

SDL_PixelFormat pf;

int widthG;

glm::mat4 perspective = glm::mat4(1.0f);
glm::mat4 model = glm::mat4(1.0f);

void gameEvents(SDL_Window *window);

struct GLVertex
{
    glm::vec3 vecPos;
    glm::vec3 colorControl;
    glm::vec2 texPos;
};

unsigned int VAO, VBO, EBO;

unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

// FOR SAVING VERTEX DATA DON'T REMOVE THIS
std::vector<GLVertex> vertices{GLVertex(), GLVertex(), GLVertex(), GLVertex()};

SDL_Surface* surface;

Flx::Backends::OpenGL::OpenGL()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();

    window = SDL_CreateWindow(game->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        Flx::Log::error("Failed to create a window");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 3);

    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    if (glContext == nullptr)
    {
        Flx::Log::error("Failed to create a GL context");
    }

    GLenum verifyGlew = glewInit() == GLEW_OK;
    if (!verifyGlew)
    {
        Flx::Log::error("Failed to initialize GLAD");
    }

    glEnable(GL_MULTISAMPLE);
    glViewport(0, 0, width, height);

    glGenVertexArrays(1, &VAO); // vertex array object
    glGenBuffers(1, &VBO);      // vertex buffer object
    glGenBuffers(1, &EBO);      // element buffer object


    SDL_RWops* rw = SDL_RWFromConstMem((void*)default_ttf, default_ttf_size);
    Flx::Assets::defaultFont = TTF_OpenFontRW(rw, 1, 24);

    pf.palette = 0;
    pf.BitsPerPixel = 32;
    pf.BytesPerPixel = 4;
    pf.Rmask = 0x000000ff;
    pf.Gmask = 0x0000ff00;
    pf.Bmask = 0x00ff0000;
    pf.Amask = 0xff000000;

}

Flx::Backends::OpenGL::~OpenGL()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    SDL_DestroyWindow(window);
}

inline Flx::Graphic* handleTexData(const void* data, int width, int height, int channels)
{
    GLenum colorMode;
    switch (channels)
    {
        case 4:
            colorMode = GL_RGBA;
            break;
        default:
            colorMode = GL_RGB;
            break;
    };

    Flx::Graphic *graphic = new Flx::Graphic(width, height, (unsigned char*)data);
    glGenTextures(1, &graphic->id);
    glBindTexture(GL_TEXTURE_2D, graphic->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, (unsigned char*)data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return graphic;
}

Flx::Graphic *Flx::Backends::OpenGL::requestTexture(const char *path)
{

    int width, height, channels;
    unsigned char *data = SOIL_load_image(path, &width, &height, &channels, SOIL_LOAD_AUTO);

    if (!data)
    {
        Flx::Log::warn("Could not load graphic!");
        return nullptr;
    }

    return handleTexData(data, width, height, channels);
    SOIL_free_image_data(data);
}

Flx::Graphic *Flx::Backends::OpenGL::requestTexture(const void *data, const size_t size)
{
    int width, height, channels;
    unsigned char* texData = SOIL_load_image_from_memory((unsigned char*)data, size, &width, &height, &channels, SOIL_LOAD_AUTO);

    return handleTexData(texData, width, height, channels);
    SOIL_free_image_data(texData);

}

Flx::Graphic *Flx::Backends::OpenGL::requestText(const char *text) { 
    surface = TTF_RenderText_Solid((TTF_Font *)Flx::Assets::defaultFont, text, {255, 255, 255, 255});
    trace(surface->format->BitsPerPixel);
    SDL_Surface* glSurface = SDL_ConvertSurface(surface, &pf, SDL_SWSURFACE);
    return handleTexData(glSurface->pixels,glSurface->w,glSurface->h,4);
}

Flx::Graphic *Flx::Backends::OpenGL::requestRectangle(float width, float height, int color) { return nullptr; }

inline void to2DOpenGLRect(std::vector<GLVertex>& buffer, Flx::Rect &rect, float z)
{

    // UPPER LEFT
    buffer[0].vecPos = glm::vec3(rect.x, rect.y, z);

    // BOTTOM LEFT
    buffer[1].vecPos = glm::vec3(rect.x, rect.y + rect.height, z);

    // BOTTOM RIGHT
    buffer[2].vecPos = glm::vec3(rect.x + rect.width, rect.y + rect.height, z);

    // UPPER RIGHT
    buffer[3].vecPos = glm::vec3(rect.x + rect.width, rect.y, z);
}

inline void to2DOpenGLRect(std::vector<GLVertex>& buffer, Flx::Rect &rect, int textureWidth, int textureHeight)
{
    // UPPER LEFT
    buffer[0].texPos = glm::vec2(rect.x, rect.y);

    // BOTTOM LEFT
    buffer[1].texPos = glm::vec2(rect.x, rect.y + rect.height);

    // BOTTOM RIGHT
    buffer[2].texPos = glm::vec2(rect.x + rect.width, rect.y + rect.height);

    // UPPER RIGHT
    buffer[3].texPos = glm::vec2(rect.x + rect.width, rect.y);
}

bool Flx::Backends::OpenGL::deleteTexture(void *spr)
{
    glDeleteTextures(1, (GLuint *)spr);
    return true;
}

void Flx::Backends::OpenGL::runEvents()
{
    gameEvents(window);
}

void Flx::Backends::OpenGL::update()
{
    game->curState->update();

    glClearColor(
        static_cast<float>(Flx::Globals::bgColor.r) / 255.0f,
        static_cast<float>(Flx::Globals::bgColor.g) / 255.0f,
        static_cast<float>(Flx::Globals::bgColor.b) / 255.0f,
        static_cast<float>(Flx::Globals::bgColor.a) / 255.0f
    );

    glClear(GL_COLOR_BUFFER_BIT);

    perspective = glm::ortho(0.0f, (float)Flx::Globals::width, (float)Flx::Globals::height, 0.0f, -1.0f, 1.0f);

    game->curState->draw();

    SDL_GL_SwapWindow(window);

}

void Flx::Backends::OpenGL::render(Flx::Sprite* spr)
{

    Flx::Rect stuff;

    stuff.x = spr->x - (spr->width / 2);
    stuff.y = spr->y - (spr->height / 2);
    stuff.width = spr->width;
    stuff.height = spr->height;

    to2DOpenGLRect(vertices, stuff, spr->z);

    stuff = spr->clipRect;

    to2DOpenGLRect(vertices, stuff, spr->graphic->width, spr->graphic->height);

    glBindVertexArray(VAO);

    glActiveTexture(GL_TEXTURE0 + spr->graphic->id);
    glBindTexture(GL_TEXTURE_2D, spr->graphic->id);

    // load data into VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(GLVertex), &vertices[0], GL_STATIC_DRAW);

    // load data into EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set vertex attribute pointers
    // vertex.position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void *)(offsetof(GLVertex, colorControl)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void *)(offsetof(GLVertex, texPos)));

    glEnableVertexAttribArray(2);

    glUseProgram(spr->graphic->id);

    spr->shader.setShaderValue("bitmap", (int)spr->graphic->id);
    spr->shader.setShaderValue("projection", perspective);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

uint32_t Flx::Backends::OpenGL::getTicks() { 
    return SDL_GetTicks();
}

void Flx::Backends::OpenGL::delay(uint32_t ms)
{
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

void checkShaderStatus(GLuint shader)
{
    using namespace std::literals::string_literals;

    GLint compiled = false;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
	    char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
        Flx::Log::warn("Error compiling shader:"s + infoLog);
        
    }
}

Flx::Shader *Flx::Backends::OpenGL::compileShader(Flx::Shader *shader)
{
    shader->program = glCreateProgram();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    const char *source = shader->vertexSource.c_str();
    int size = shader->vertexSource.size();
    glShaderSource(vs, 1, &source, &size);
    glCompileShader(vs);
    checkShaderStatus(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    source = shader->fragmentSource.c_str();
    size = shader->fragmentSource.size();
    glShaderSource(fs, 1, &source, &size);
    glCompileShader(fs);
    checkShaderStatus(fs);

    glAttachShader(shader->program, vs);
    glAttachShader(shader->program, fs);
    glLinkProgram(shader->program);

    return shader;
}

#endif