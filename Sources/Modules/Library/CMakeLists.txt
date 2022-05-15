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
cm_initialise_local_project("Library" "ndxLib library." Languages CXX)





# ************************************************************
# Configurations
# ************************************************************
cm_initialise_local_variable()
add_definitions(-DNDXLIB_NONCLIENT_BUILD)




# ************************************************************
# Header Files
# ************************************************************
set(LOCAL_HEADER_FILES
    "${LOCAL_PATH_HEADER}/ndxLogManager.h"
    "${LOCAL_PATH_HEADER}/ndxMacros.h"
    "${LOCAL_PATH_HEADER}/ndxNumberGenerator.h"
    "${LOCAL_PATH_HEADER}/ndxPrerequisites.h"
    "${LOCAL_PATH_HEADER}/ndxSingleton.h"
)




# ************************************************************
# Source Files
# ************************************************************
set(LOCAL_SOURCE_FILES
    "${LOCAL_PATH_SOURCE}/ndxLogManager.cpp"
    "${LOCAL_PATH_SOURCE}/ndxNumberGenerator.cpp"
)




# ************************************************************
# Build Project
# ************************************************************
# Project header files.
set(LOCAL_HEADERS
    ${LOCAL_HEADER_FILES}
)

# Project source files.
set(LOCAL_SOURCES
    ${LOCAL_SOURCE_FILES}
)

# Project include directories.
set(LOCAL_INCLUDES
	${CMAKE_CURRENT_BINARY_DIR}
    ${LOCAL_PATH_HEADER}
    ${PROJECT_INCLUDE_DIR}
)

# Project libraries.
set(LOCAL_LIBRARIES
    ${PROJECT_LIBRARIES}
)

# Make include path available for sub projects.
set(NDXLIB_INCLUDE_DIR
    ${LOCAL_PATH_HEADER}
    CACHE INTERNAL "Include path of ndxLib."
)

# Project includes.
include_directories(${LOCAL_INCLUDES})




# ************************************************************
# Binary Output
# ************************************************************
# Generate binary.
add_library(${PROJECT_NAME} SHARED ${LOCAL_HEADERS} ${LOCAL_SOURCES} ${LOCAL_QT_FILES})

# Link libraries.
target_link_libraries(${PROJECT_NAME} ${LOCAL_LIBRARIES})

# Target options.
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    OUTPUT_NAME "ndxLib"
    DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}"
)

# Copy project templates.
cm_copy_project_template()

