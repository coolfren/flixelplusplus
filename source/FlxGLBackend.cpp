#include "flixel++/Common.hpp"
#include "flixel++/FlxBackends.hpp"
#include "flixel++/FlxG.hpp"

#include "flixel++/FlxLog.hpp"
#include "flixel++/FlxMacros.hpp"

using Flx::Globals::game, Flx::Globals::width, Flx::Globals::height;

#ifdef FLIXEL_OPENGL

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::mat4 perspective = glm::mat4(1.0f);

void gameEvents(SDL_Window *window);

struct GLVertex3{
    float x;
    float y;
    float z;
};

struct GLVertex2{
    float x;
    float y;
};

unsigned int VAO,VBO, EBO;

float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

unsigned int indices[] = {  
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

Flx::Backends::OpenGL::OpenGL()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(game->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        Flx::Log::error("Failed to create a window");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    if (glContext == nullptr)
    {
        Flx::Log::error("Failed to create a GL context");
    }
    
    GLenum verifyGlew = glewInit();
    if (verifyGlew != GLEW_OK)
    {
        Flx::Log::error("Failed to initialize GLEW");
    }

    glViewport(0, 0, width, height);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

Flx::Backends::OpenGL::~OpenGL()
{
    SDL_DestroyWindow(window);
}

Flx::Graphic *Flx::Backends::OpenGL::createGraphic(Flx::Graphic *graphic)
{
    GLuint tempBitmap;
    glGenTextures(1, &tempBitmap);
    glBindTexture(GL_TEXTURE_2D, tempBitmap);
    graphic->bitmap = (void *)tempBitmap;

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

    Flx::Graphic* graphic = new Flx::Graphic(width, height, data);
    glGenTextures(1, &graphic->id);
    glBindTexture(GL_TEXTURE_2D, graphic->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    return graphic;
}

Flx::Graphic *Flx::Backends::OpenGL::requestText(const char *text) { return nullptr; }

Flx::Graphic *Flx::Backends::OpenGL::requestRectangle(float width, float height, int color) { return nullptr; }

inline const std::vector<GLVertex3> to2DOpenGLRect(Flx::Rect &rect, float z)
{
    std::vector<GLVertex3> buffer;

    // UPPER LEFT
    buffer.push_back({rect.x, rect.y, z});

    // BOTTOM LEFT
    buffer.push_back({rect.x, rect.y + rect.height, z});

    // BOTTOM RIGHT
    buffer.push_back({rect.x + rect.width, rect.y + rect.height, z});

    // UPPER RIGHT
    buffer.push_back({rect.x + rect.width, rect.y, z});

    return buffer;
}

inline const std::vector<glm::vec2> to2DOpenGLRect(Flx::Rect &rect)
{
    std::vector<glm::vec2> buffer;

    // UPPER LEFT
    buffer.push_back(glm::vec2(rect.x, rect.y));

    // BOTTOM LEFT
    buffer.push_back(glm::vec2(rect.x, rect.y + rect.height));

    // BOTTOM RIGHT
    buffer.push_back(glm::vec2(rect.x + rect.width, rect.y + rect.height));

    // UPPER RIGHT
    buffer.push_back(glm::vec2(rect.x + rect.width, rect.y));

    return buffer;
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

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    perspective = glm::ortho(0.0f, (float)Flx::Globals::width, (float)Flx::Globals::height, 0.0f, -1.0f, 1.0f);

    game->curState->draw();

    SDL_GL_SwapWindow(window);
}

void Flx::Backends::OpenGL::render(Flx::Sprite *spr) {
    Flx::Rect stuff = spr->clipRect;

    if (spr->animation->animated)
    {
        Flx::Frame* anim = spr->animation->getCurAnim();
        stuff.x = anim->x;
        stuff.y = anim->y;
        stuff.width = anim->width;
        stuff.height = anim->height;
    }

    std::vector<GLVertex3> src = to2DOpenGLRect(stuff, spr->z);

    stuff.x = spr->x - (spr->width / 2);
    stuff.y = spr->y - (spr->height / 2);
    stuff.width = spr->width;
    stuff.height = spr->height;

    std::vector<glm::vec2> dst = to2DOpenGLRect(stuff);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, spr->graphic->id);

    glUseProgram(spr->shader.program);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

uint32_t Flx::Backends::OpenGL::getTicks() { return 0; }

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
    GLint compiled = false;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if(!compiled){
        Flx::Log::warn("Could not compile shader!");
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