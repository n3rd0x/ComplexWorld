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
# CMake Configurations
# ************************************************************
# Set minimum version requirement of CMake.
cmake_minimum_required(VERSION 3.8)

# CMake build system.
include("${CMAKE_CURRENT_SOURCE_DIR}/BuildSystem.cmake")





# ************************************************************
# Project Details
# ************************************************************
project("ComplexWorld" DESCRIPTION "Research and educational project." VERSION 0.0.1.0 LANGUAGES CXX)




# ************************************************************
# Configurations
# ************************************************************
# Compiler details.
cm_user_compiler_cxx_standard(17)

# Initialise CMake system.
cm_initialise_cmake_system()

# Initialise project SDK.
initialise_project_sdk()

# Add propterty definitions.
cm_add_definition(VERSION="${PROJECT_VERSION}")
cm_add_definition(RELEASE="${PROJECT_BUILD_TIME}")

# Initialize other paths
set(PROJECT_PATH_SOURCE "${PROJECT_PATH_ROOT}/Sources")
set(PROJECT_PATH_DATA "${PROJECT_PATH_ROOT}/Data")
set(PROJECT_PATH_THIRD_PARTY "${PROJECT_PATH_ROOT}/Third-Parties")

# Include common files.
include("CommonComplexApplicationFiles")
include("CommonProgrammingGameAIFiles")
include("CommonFiles")
include(IncludeLoguru)

# Project selections.
option(Build_AllBuilds "Enable all modules." OFF)
option(Build_Module_ComplexApplication "Enable the Complex Application module." OFF)
option(Build_Module_SampleCpp "Enable the Sample of C++ module." OFF)

# Toggle project selections.
set(Modules
    Build_Module_ComplexApplication
    Build_Module_SampleCpp
)
toggle_enabling_state(Build_AllBuilds "${Modules}")


# Searching for Qt.
set(SearchQt FALSE)
if(Build_Module_ComplexApplication_STATE)
    set(SearchQt TRUE)
endif()




# ************************************************************
# Dependencies
# ************************************************************
# Necessary dependencies.
find_package(CustomPoco)
find_package(CustomOGRE)

# Require Qt
if(SearchQt)
    # Enable auto linking to 'qtmain' (new for Qt5).
    cmake_policy(SET CMP0020 NEW)

    # On Windows, deploy Qt libraries to the executable directory.
    if(WIN32)
        set(QT_DEPLOY_LIBRARY ON CACHE BOOL "Deloy Qt libraries." FORCE)
    endif()

    find_package(CustomQt5 COMPONENTS "Qt5Core;Qt5Charts;Qt5Gui;Qt5Widgets")

    # GLM (0.9.4.6)
    find_package(CustomGLM)
endif()

# Initialise the dependencies based on the SDK.
initialise_project_sdk_library()

# Set project dependencies.
set(PROJECT_INCLUDE_DIR
    "${POCO_INCLUDE_DIR}"
    "${GLM_INCLUDE_DIR}"
)

set(PROJECT_LIBRARIES
    "${POCO_FOUNDATION_LIBRARIES}"
)

# Adding dependencies.
cm_package_copy_binary_from_target(OGRE)
cm_package_copy_binary_from_target(OGRE_Bites)
cm_package_copy_binary_from_target(OGRE_Overlay)
cm_package_copy_binary_from_target(POCO_FOUNDATION)

if(SearchQt)
    cm_package_copy_binary_from_target(QT)
    if(UNIX)
        qt_copy_configuration_file()
    endif()
    qt_copy_necessary_binary_from_target()
endif()




# ************************************************************
# Resources
# ************************************************************





# ************************************************************
# Sub Projects
# ************************************************************
message(STATUS "")
message(STATUS "Sub Projects:")
if(BUILD_SOURCE)
    add_subdirectory("Sources")
else()
    message("Run CMake again to processing sub projects.")
endif()


# Check point.
set(BUILD_SOURCE TRUE CACHE INTERNAL "Start parsing source directory.")
