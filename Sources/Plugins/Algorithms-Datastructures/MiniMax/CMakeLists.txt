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
initialise_local_project("Plugin_AlgorithmsDataStructures_MiniMax" "A MiniMax algorithm.")




# ************************************************************
# Configurations
# ************************************************************
# Local paths.
initialise_local_variable()
set(LOCAL_PATH_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/res")
set(LOCAL_PATH_RESOURCE_QRC "${LOCAL_PATH_RESOURCE}/qrc")
set(LOCAL_PATH_RESOURCE_UI "${LOCAL_PATH_RESOURCE}/ui")

# Set Qt plug-in.
add_definitions(-DQT_PLUGIN)




# ************************************************************
# Header Files
# ************************************************************
set(LOCAL_HEADER_FILES
    "${LOCAL_PATH_HEADER}/Description.json"
)

set(LOCAL_QT_HEADER_FILES
    "${LOCAL_PATH_HEADER}/Cell.h"
    "${LOCAL_PATH_HEADER}/GameView.h"
    "${LOCAL_PATH_HEADER}/Widget.h"
)




# ************************************************************
# Source Files
# ************************************************************
set(LOCAL_SOURCE_FILES

)

set(LOCAL_QT_SOURCE_FILES
    "${LOCAL_PATH_SOURCE}/Cell.cpp"
    "${LOCAL_PATH_SOURCE}/GameView.cpp"
    "${LOCAL_PATH_SOURCE}/Widget.cpp"
)

set(LOCAL_QT_SOURCE_UI_FILES
    "${LOCAL_PATH_RESOURCE_UI}/Widget.ui"
)

set(LOCAL_QT_SOURCE_QRC_FILES
    "${LOCAL_PATH_RESOURCE_QRC}/Resource.qrc"
)


# ************************************************************
# Common Files
# ************************************************************
enable_complex_application_qt_common_files()
enable_complex_application_qt_common_widget_files()




# ************************************************************
# Qt Generated Files
# ************************************************************
# Group Qt headers and sources.
set(LOCAL_QT_HEADERS
    ${LOCAL_QT_HEADER_FILES}
)

set(LOCAL_QT_SOURCES
    ${LOCAL_QT_SOURCE_FILES}
)

# Qt generated files.
qt5_wrap_cpp(LOCAL_QT_GENERATED_MOC_FILES ${LOCAL_QT_HEADERS})
qt5_add_resources(LOCAL_QT_GENERATED_QRC_FILES ${LOCAL_QT_SOURCE_QRC_FILES})
qt5_wrap_ui(LOCAL_QT_GENERATED_UI_FILES ${LOCAL_QT_SOURCE_UI_FILES})

# Group files.
source_group("Generated Files\\Moc Files" FILES ${LOCAL_QT_GENERATED_MOC_FILES})
source_group("Generated Files\\Qrc Files" FILES ${LOCAL_QT_GENERATED_QRC_FILES})
source_group("Generated Files\\UI Files" FILES ${LOCAL_QT_GENERATED_UI_FILES})
source_group("Resource Files" FILES ${LOCAL_QT_SOURCE_QRC_FILES})
source_group("UI Files" FILES ${LOCAL_QT_SOURCE_UI_FILES})




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

# Project Qt files.
set(LOCAL_QT_FILES
    ${LOCAL_QT_HEADER_FILES}
    ${LOCAL_QT_SOURCE_FILES}
    ${LOCAL_QT_GENERATED_MOC_FILES}
    ${LOCAL_QT_GENERATED_QRC_FILES}
    ${LOCAL_QT_GENERATED_UI_FILES}
)

# Local include directories.
set(LOCAL_INCLUDES
    ${CMAKE_CURRENT_BINARY_DIR}
    ${LOCAL_PATH_HEADER}
    ${LOCAL_PATH_GROUP_HEADER}
    ${PROJECT_INCLUDE_DIR}
    ${NDXLIB_INCLUDE_DIR}
)

# Project libraries.
set(LOCAL_LIBRARIES
    ${PROJECT_LIBRARIES}
)

# Project includes.
include_directories(${LOCAL_INCLUDES})




# ************************************************************
# Binary Output
# ************************************************************
# Generate binary.
add_library(${PROJECT_NAME} SHARED ${LOCAL_HEADERS} ${LOCAL_SOURCES} ${LOCAL_QT_FILES})

# Link libraries.
target_link_libraries(${PROJECT_NAME} ${LOCAL_LIBRARIES} Library)

# Target options.
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}"
)

# Use Qt modules.
qt5_use_modules(${PROJECT_NAME} Charts Core Gui Widgets)

# Copy project templates.
copy_project_template()

# Copy the generated plug-in to the output directory.
copy_build_file_to_output_directory(SubPath "/Plugins")

