#include "flixel++/FlxBackends.hpp"
#include "flixel++/FlxLog.hpp"
#include "flixel++/FlxG.hpp"

#ifdef FLIXEL_X11

#include <SOIL/SOIL.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using Flx::Backends::X11, Flx::Globals::game, Flx::Globals::width, Flx::Globals::height;

X11::X11(){
    display = XOpenDisplay(NULL);
    if(!display)
    {
        Flx::Log::error("Failed to init display");
        exit(1);
    }

    screen = DefaultScreen(display);

    window = XCreateSimpleWindow(display, RootWindow(display, screen), 100, 100, width, height, 1, 0, 0);

	visual = DefaultVisual(display, screen);
    XMapWindow(display, window);
    XFlush(display);

    gc = XCreateGC(display, window, NULL, NULL);
}

X11::~X11(){
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}

Flx::Graphic *X11::requestTexture(const char *path){
    int w,h,c;

    unsigned char* data = SOIL_load_image(path, &w, &h, &c, SOIL_LOAD_AUTO);
    XImage* image = XCreateImage(display, visual, DefaultDepth(display,screen), ZPixmap, 0, (char*)data, w, h, c*4, 0);

    return new Flx::Graphic(w,h,image);
}

Flx::Graphic *X11::requestTexture(const void *data, const size_t size){
}

Flx::Graphic *X11::requestText(const char *text){
    return nullptr;
}

Flx::Graphic *X11::requestRectangle(float width, float height, int color){
    return nullptr;
}

Flx::Shader *X11::compileShader(Flx::Shader *shader){
    return nullptr;
}

bool X11::deleteTexture(void *tex){
    XDestroyImage((XImage*)tex);
    return true;
}

void X11::runEvents(){
    if (XCheckWindowEvent(display, window, ExposureMask, &event)) {
        switch(event.type)
        {

        }
    }
}

void X11::update(){
    game->curState->update();

    XFlushGC(display, gc);
    XSetForeground(display, gc, WhitePixel(display, screen));

    game->curState->draw();
}

void X11::render(Flx::Sprite *spr){
    XPutImage(display, window, gc, (XImage*)spr->graphic->bitmap, spr->clipRect.x, spr->clipRect.y, spr->x, spr->y, spr->clipRect.width, spr->clipRect.height);
}

uint32_t X11::getTicks(){
    return 0;
}

void X11::delay(uint32_t ms){
    usleep(ms * 1000);
}
#endif