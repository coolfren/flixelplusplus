#!/usr/bin/make -f
all:
	@echo "Specify what platform you want to build"
pc:
ifeq ($(SDL_LEGACY),1)
	@mkdir -p build
	@cd build && cmake -DSDL_LEGACY=1 .. && make
else
	@mkdir -p build
	@cd build && cmake .. && make
endif
switch:
	@mkdir -p build/switch
	@make -f mk/switch.mk
3ds:
	@mkdir -p build/3ds
	@make -f mk/3ds.mk
wii:
	@mkdir -p build/wii
	@make -f mk/wii.mk
clean:
	rm -rf build/
	rm -rf obj/
	@make -f mk/switch.mk clean
install:
	cp -r build/*.so /usr/lib/libflixel++.so
	cp -r include/flixel++ /usr/include/flixel++
example:
	@make -f examples/Makefile
	LD_LIBRARY_PATH="./build/" examples/example