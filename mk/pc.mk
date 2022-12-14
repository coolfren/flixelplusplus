# Legacy Makefile, use CMake instead!

CC = gcc
CXX = g++
INCLUDE = -Iinclude/
FILES = source/**.cpp
CFLAGS = -O3 -Wall -fPIC -g
OUT = lib$(notdir $(CURDIR)).so
OBJ = obj/pc
CLIBS = ${sdl2-config --cflags --libs}-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lopenal -lvorbisfile -lcurl

ifeq ($(SDL_LEGACY),1)
	CLIBS = ${sdl-config --cflags --libs}-lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lopenal -lvorbisfile -lcurl -DSDL_LEGACY
	OUT := $(OUT)_legacy
endif



all: ./source/*
	@mkdir -p ${OBJ}
	@for file in $^ ; do \
		echo "$${file}..." ; \
		${CXX} ${CFLAGS} ${CLIBS} ${INCLUDE} $${file} -c -o ${OBJ}/$$(basename $${file} .cpp).o || exit 1 ; \
	done
	@echo "Linking..."
	@${CXX} ${CLIBS} ${OBJ}/*.o -o build/${OUT} -shared