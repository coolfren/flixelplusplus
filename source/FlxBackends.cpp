#include "flixel++/FlxBackends.hpp"
#include "flixel++/FlxG.hpp"
#include "flixel++/FlxLog.hpp"
#include "flixel++/FlxMacros.hpp"

using Flx::Globals::game, Flx::Globals::width, Flx::Globals::height;

// -------------------------------------

Flx::Backends::Backend::Backend() {}
Flx::Backends::Backend::~Backend() {}
Flx::Graphic *Flx::Backends::Backend::requestTexture(const char *path) { return nullptr; }
Flx::Graphic *Flx::Backends::Backend::requestTexture(const void *data, const size_t size) { return nullptr; }
Flx::Graphic *Flx::Backends::Backend::requestText(const char *text) { return nullptr; }
Flx::Graphic *Flx::Backends::Backend::requestRectangle(float width, float height, int color) { return nullptr; }
Flx::Shader *Flx::Backends::Backend::compileShader(Flx::Shader *shader) { return nullptr; }
bool Flx::Backends::Backend::deleteTexture(void *spr) { return false; }
void Flx::Backends::Backend::runEvents() {}
void Flx::Backends::Backend::update() {}
void Flx::Backends::Backend::render(Flx::Sprite *spr) {}
uint32_t Flx::Backends::Backend::getTicks() { return 0; }
void Flx::Backends::Backend::delay(uint32_t ms) {}
void Flx::Backends::Backend::testrender(Flx::Rect rect) {}

// -------------------------------------
