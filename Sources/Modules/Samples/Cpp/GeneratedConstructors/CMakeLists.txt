# ************************************************************
# Complex World - Research & Educational Project
# Copyright (C) T.Sang Tran aka "n3rd0x" <nerdox.tranit@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# ************************************************************




# ************************************************************
# Project Details
# ************************************************************
cm_initialise_local_project("CppGeneratedConstructors" "C++ Generated Constructor." Languages CXX)




# ************************************************************
# Configurations
# ************************************************************
cm_initialise_local_variable()


# ************************************************************
# Header & Source Files
# ************************************************************
file(GLOB LOCAL_HEADER_FILES "${LOCAL_PATH_SOURCE}/*.h")
file(GLOB LOCAL_SOURCE_FILES "${LOCAL_PATH_SOURCE}/*.cpp")


# ************************************************************
# Configure Project
# ************************************************************
# Project header files.
set(LOCAL_HEADERS
    "${LOCAL_HEADER_FILES}"
)

# Project source files.
set(LOCAL_SOURCES
    "${LOCAL_SOURCE_FILES}"
)

# Project include directories.
set(LOCAL_INCLUDES
    "${PROJECT_INCLUDE_DIR}"
)

# Project libraries.
set(LOCAL_LIBRARIES
)

# Project includes directories.
include_directories(${LOCAL_INCLUDES})





# ************************************************************
# Binary Output
# ************************************************************
# Generate binary.
add_executable(${PROJECT_NAME} ${LOCAL_HEADERS} ${LOCAL_SOURCES})

# Linking libraries.
target_link_libraries(${PROJECT_NAME} ${LOCAL_LIBRARIES})

# Target options.
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)

# Copy project templates.
cm_copy_project_template()

