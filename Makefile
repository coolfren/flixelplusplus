#!/usr/bin/make -f
all:
	@echo "Specify what platform you want to build"
pc:
ifeq ($(PLATFORM),1)
	@mkdir -p build
	@cd build && cmake -DSDL_LEGACY=1 .. && make

else ifeq ($(PLATFORM),2)
	@mkdir -p build
	@cd build && cmake -DSDL=1 .. && make

else ifeq ($(PLATFORM),3)
	@mkdir -p build
	@cd build && cmake -DOPENGL=1 .. && make


endif

install:
	rm -rf /usr/include/flixel++
	rm -rf /usr/lib/libflixel++.so
	cp -r include/flixel++/ /usr/include
	cp -r build/libflixel++.so /usr/lib/libflixel++.so
uninstall:
	rm -rf /usr/include/flixel++
	rm -rf /usr/lib/libflixel++.so
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
example:
	@make -f examples/Makefile
	LD_LIBRARY_PATH="./build/" examples/example