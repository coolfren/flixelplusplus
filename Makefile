#!/usr/bin/make -f
MYDIR = .
all:
	@echo "Specify what platform you want to build"
pc:
	@make -f mk/pc.mk SDL_LEGACY=$(SDL_LEGACY)
switch:
	@make -f mk/switch.mk
clean:
	rm -rf build/
	rm -rf obj/
install:
	cp -r build/*.so /usr/lib/libflixel++.so
	cp -r include/flixel++ /usr/include/flixel++
example:
	@make -f examples/Makefile
	LD_LIBRARY_PATH="./build/" examples/example