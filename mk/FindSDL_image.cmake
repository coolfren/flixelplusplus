# from: https://github.com/aminosbh/SDL2-image-sample/blob/master/cmake/SDL2/FindSDL2_image.cmake
# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#  Copyright 2019 Amine Ben Hassouna <amine.benhassouna@gmail.com>
#  Copyright 2000-2019 Kitware, Inc. and Contributors
#  All rights reserved.

#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:

#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.

#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.

#  * Neither the name of Kitware, Inc. nor the names of Contributors
#    may be used to endorse or promote products derived from this
#    software without specific prior written permission.

#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
#  HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#[=======================================================================[.rst:
FindSDL_image
--------------

Locate SDL_image library

This module defines the following 'IMPORTED' target:

::

  SDL::Image
    The SDL_image library, if found.
    Have SDL::Core as a link dependency.



This module will set the following variables in your project:

::

  SDL_IMAGE_LIBRARIES, the name of the library to link against
  SDL_IMAGE_INCLUDE_DIRS, where to find the headers
  SDL_IMAGE_FOUND, if false, do not try to link against
  SDL_IMAGE_VERSION_STRING - human-readable string containing the
                              version of SDL_image



This module responds to the following cache variables:

::

  SDL_IMAGE_PATH
    Set a custom SDL_image Library path (default: empty)

  SDL_IMAGE_NO_DEFAULT_PATH
    Disable search SDL_image Library in default path.
      If SDL_IMAGE_PATH (default: ON)
      Else (default: OFF)

  SDL_IMAGE_INCLUDE_DIR
    SDL_image headers path.

  SDL_IMAGE_LIBRARY
    SDL_image Library (.dll, .so, .a, etc) path.


Additional Note: If you see an empty SDL_IMAGE_LIBRARY in your project
configuration, it means CMake did not find your SDL_image library
(SDL_image.dll, libSDL_image.so, etc). Set SDL_IMAGE_LIBRARY to point
to your SDL_image library, and  configure again. This value is used to
generate the final SDL_IMAGE_LIBRARIES variable and the SDL::Image target,
but when this value is unset, SDL_IMAGE_LIBRARIES and SDL::Image does not
get created.


$SDLIMAGEDIR is an environment variable that would correspond to the
./configure --prefix=$SDLIMAGEDIR used in building SDL_image.

$SDLDIR is an environment variable that would correspond to the
./configure --prefix=$SDLDIR used in building SDL.



Created by Amine Ben Hassouna:
  Adapt FindSDL_image.cmake to SDL_image (FindSDL_image.cmake).
  Add cache variables for more flexibility:
    SDL_IMAGE_PATH, SDL_IMAGE_NO_DEFAULT_PATH (for details, see doc above).
  Add SDL as a required dependency.
  Modernize the FindSDL_image.cmake module by creating a specific target:
    SDL::Image (for details, see doc above).

Original FindSDL_image.cmake module:
  Created by Eric Wing.  This was influenced by the FindSDL.cmake
  module, but with modifications to recognize OS X frameworks and
  additional Unix paths (FreeBSD, etc).
#]=======================================================================]

# SDL Library required
find_package(SDL QUIET)
if(NOT SDL_FOUND)
  set(SDL_IMAGE_SDL_NOT_FOUND "Could NOT find SDL (SDL is required by SDL_image).")
  if(SDL_image_FIND_REQUIRED)
    message(FATAL_ERROR ${SDL_IMAGE_SDL_NOT_FOUND})
  else()
      if(NOT SDL_image_FIND_QUIETLY)
        message(STATUS ${SDL_IMAGE_SDL_NOT_FOUND})
      endif()
    return()
  endif()
  unset(SDL_IMAGE_SDL_NOT_FOUND)
endif()


# Define options for searching SDL_image Library in a custom path

set(SDL_IMAGE_PATH "" CACHE STRING "Custom SDL_image Library path")

set(_SDL_IMAGE_NO_DEFAULT_PATH OFF)
if(SDL_IMAGE_PATH)
  set(_SDL_IMAGE_NO_DEFAULT_PATH ON)
endif()

set(SDL_IMAGE_NO_DEFAULT_PATH ${_SDL_IMAGE_NO_DEFAULT_PATH}
    CACHE BOOL "Disable search SDL_image Library in default path")
unset(_SDL_IMAGE_NO_DEFAULT_PATH)

set(SDL_IMAGE_NO_DEFAULT_PATH_CMD)
if(SDL_IMAGE_NO_DEFAULT_PATH)
  set(SDL_IMAGE_NO_DEFAULT_PATH_CMD NO_DEFAULT_PATH)
endif()

# Search for the SDL_image include directory
find_path(SDL_IMAGE_INCLUDE_DIR SDL_image.h
  HINTS
    ENV SDLIMAGEDIR
    ENV SDLDIR
    ${SDL_IMAGE_NO_DEFAULT_PATH_CMD}
  PATH_SUFFIXES SDL
                # path suffixes to search inside ENV{SDLDIR}
                # and ENV{SDLIMAGEDIR}
                include/SDL include
  PATHS ${SDL_IMAGE_PATH}
  DOC "Where the SDL_image headers can be found"
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(VC_LIB_PATH_SUFFIX lib/x64)
else()
  set(VC_LIB_PATH_SUFFIX lib/x86)
endif()

# Search for the SDL_image library
find_library(SDL_IMAGE_LIBRARY
  NAMES SDL_image
  HINTS
    ENV SDLIMAGEDIR
    ENV SDLDIR
    ${SDL_IMAGE_NO_DEFAULT_PATH_CMD}
  PATH_SUFFIXES lib ${VC_LIB_PATH_SUFFIX}
  PATHS ${SDL_IMAGE_PATH}
  DOC "Where the SDL_image Library can be found"
)

# Read SDL_image version
if(SDL_IMAGE_INCLUDE_DIR AND EXISTS "${SDL_IMAGE_INCLUDE_DIR}/SDL_image.h")
  file(STRINGS "${SDL_IMAGE_INCLUDE_DIR}/SDL_image.h" SDL_IMAGE_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_IMAGE_MAJOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL_IMAGE_INCLUDE_DIR}/SDL_image.h" SDL_IMAGE_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL_IMAGE_MINOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL_IMAGE_INCLUDE_DIR}/SDL_image.h" SDL_IMAGE_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL_IMAGE_PATCHLEVEL[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+SDL_IMAGE_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL_IMAGE_VERSION_MAJOR "${SDL_IMAGE_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_IMAGE_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL_IMAGE_VERSION_MINOR "${SDL_IMAGE_VERSION_MINOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_IMAGE_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" SDL_IMAGE_VERSION_PATCH "${SDL_IMAGE_VERSION_PATCH_LINE}")
  set(SDL_IMAGE_VERSION_STRING ${SDL_IMAGE_VERSION_MAJOR}.${SDL_IMAGE_VERSION_MINOR}.${SDL_IMAGE_VERSION_PATCH})
  unset(SDL_IMAGE_VERSION_MAJOR_LINE)
  unset(SDL_IMAGE_VERSION_MINOR_LINE)
  unset(SDL_IMAGE_VERSION_PATCH_LINE)
  unset(SDL_IMAGE_VERSION_MAJOR)
  unset(SDL_IMAGE_VERSION_MINOR)
  unset(SDL_IMAGE_VERSION_PATCH)
endif()

set(SDL_IMAGE_LIBRARIES ${SDL_IMAGE_LIBRARY})
set(SDL_IMAGE_INCLUDE_DIRS ${SDL_IMAGE_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL_image
                                  REQUIRED_VARS SDL_IMAGE_LIBRARIES SDL_IMAGE_INCLUDE_DIRS
                                  VERSION_VAR SDL_IMAGE_VERSION_STRING)


mark_as_advanced(SDL_IMAGE_PATH
                 SDL_IMAGE_NO_DEFAULT_PATH
                 SDL_IMAGE_LIBRARY
                 SDL_IMAGE_INCLUDE_DIR)


if(SDL_IMAGE_FOUND)

  # SDL::Image target
  if(SDL_IMAGE_LIBRARY AND NOT TARGET SDL::Image)
    add_library(SDL::Image UNKNOWN IMPORTED)
    set_target_properties(SDL::Image PROPERTIES
                          IMPORTED_LOCATION "${SDL_IMAGE_LIBRARY}"
                          INTERFACE_INCLUDE_DIRECTORIES "${SDL_IMAGE_INCLUDE_DIR}"
                          INTERFACE_LINK_LIBRARIES SDL::Core)
  endif()
endif()
