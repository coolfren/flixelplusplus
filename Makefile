#!/usr/bin/make -f
all:
	@echo "Specify what platform you want to build"
pc:
ifeq ($(SDL_LEGACY),1)
	@mkdir -p build
	@cd build && cmake -DSDL_LEGACY .. && make
else
	@mkdir -p build
	@cd build && cmake .. && make
endif
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