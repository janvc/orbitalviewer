#
# Copyright 2016 Jan von Cosel
#
# This file is part of orbitalviewer.
#
# orbitalviewer is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# orbitalviewer is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have recieved a copy of the GNU General Public License
# along with orbitalviewer. If not, see <http://www.gnu.org/licenses/>.
#


# Boost libraries are required
find_package(Boost COMPONENTS system iostreams filesystem program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Chemkit libraries are required
find_package(Chemkit COMPONENTS io graphics gui REQUIRED)
include_directories(${CHEMKIT_INCLUDE_DIRS})

# We are using Qt5 for the GUI
find_package(Qt5 COMPONENTS Widgets OpenGL LinguistTools REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5OpenGL_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

set(SOURCES
    orbviewwindow.cpp
)

set(MOC_HEADERS
    orbviewwindow.h
)

set(UI_FORMS
    orbviewwindow.ui
)

qt5_wrap_ui(UI_SOURCES ${UI_FORMS})
qt5_add_resources(RCC_SOURCES ${RESOURCES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")




