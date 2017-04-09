# ************************************************************
# Complex World - Research & Educational Project
# Copyright (C) T.Sang Tran aka "Nerdox" <t.sang.tran@outlook.com>
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
# Configurations
# ************************************************************
set(COMMON_PATH_ALGORITHM_ROOT "${PROJECT_PATH_SOURCE}/Common/Algorithm")
set(COMMON_PATH_ALGORITHM_HEADER "${COMMON_PATH_ALGORITHM_ROOT}/include")
set(COMMON_PATH_ALGORITHM_RESOURCE "${COMMON_PATH_ALGORITHM_ROOT}/res")
set(COMMON_PATH_ALGORITHM_RESOURCE_QRC "${COMMON_PATH_ALGORITHM_RESOURCE}/qrc")
set(COMMON_PATH_ALGORITHM_RESOURCE_UI "${COMMON_PATH_ALGORITHM_RESOURCE}/ui")
set(COMMON_PATH_ALGORITHM_SOURCE "${COMMON_PATH_ALGORITHM_ROOT}/src")
set(COMMON_INCLUDE_DIR_ALGORITHM "${COMMON_PATH_ALGORITHM_HEADER}")




# ************************************************************
# Header Files
# ************************************************************
set(COMMON_ALGORITHM_HEADER_FILES
    "${COMMON_PATH_ALGORITHM_HEADER}/MetaData.h"
)

set(COMMON_ALGORITHM_QT_HEADER_FILES
    "${COMMON_PATH_ALGORITHM_HEADER}/Plugin.h"
)

set(COMMON_ALGORITHM_QT_HEADER_WIDGET_FILES
    "${COMMON_PATH_ALGORITHM_HEADER}/Widgets/Controller.h"
)




# ************************************************************
# Source Files
# ************************************************************
set(COMMON_ALGORITHM_SOURCE_FILES
    "${COMMON_PATH_ALGORITHM_SOURCE}/MetaData.cpp"
)

set(COMMON_ALGORITHM_QT_SOURCE_FILES
    "${COMMON_PATH_ALGORITHM_SOURCE}/Plugin.cpp"
)

set(COMMON_ALGORITHM_QT_SOURCE_WIDGET_FILES
    "${COMMON_PATH_ALGORITHM_SOURCE}/Widgets/Controller.cpp"
)




# ************************************************************
# Resource Files
# ************************************************************
set(COMMON_ALGORITHM_QT_QRC_FILES
    "${COMMON_PATH_ALGORITHM_RESOURCE_QRC}/CommonQrc.qrc"
)

set(COMMON_ALGORITHM_QT_UI_FILES
    "${COMMON_PATH_ALGORITHM_RESOURCE_UI}/Controller.ui"
)




# ************************************************************
# Macro
# ************************************************************
# Set header and source files.
macro(ENABLE_ALGORITHM_QT_COMMON_FILES)
    # Group files.
    source_group("Header Files\\Common" FILES ${COMMON_ALGORITHM_QT_HEADER_FILES} ${COMMON_ALGORITHM_HEADER_FILES})
    source_group("Source Files\\Common" FILES ${COMMON_ALGORITHM_QT_SOURCE_FILES} ${COMMON_ALGORITHM_SOURCE_FILES})
    
    # Add into global header file variable.
    set(LOCAL_HEADER_FILES ${LOCAL_HEADER_FILES} ${COMMON_ALGORITHM_HEADER_FILES})
    set(LOCAL_SOURCE_FILES ${LOCAL_SOURCE_FILES} ${COMMON_ALGORITHM_SOURCE_FILES})
    set(LOCAL_QT_HEADER_FILES ${LOCAL_QT_HEADER_FILES} ${COMMON_ALGORITHM_QT_HEADER_FILES})
    set(LOCAL_QT_SOURCE_FILES ${LOCAL_QT_SOURCE_FILES} ${COMMON_ALGORITHM_QT_SOURCE_FILES})
    
    # Set include directory.
    include_directories(${COMMON_INCLUDE_DIR_ALGORITHM})
endmacro()


macro(ENABLE_ALGORITHM_QT_COMMON_WIDGET_FILES)
    # Group files.
    source_group("Header Files\\Common\\Widgets" FILES ${COMMON_ALGORITHM_QT_HEADER_WIDGET_FILES})
    source_group("Source Files\\Common\\Widgets" FILES ${COMMON_ALGORITHM_QT_SOURCE_WIDGET_FILES})
    
    # Add into global header file variable.
    set(LOCAL_QT_HEADER_FILES ${LOCAL_QT_HEADER_FILES} ${COMMON_ALGORITHM_QT_HEADER_WIDGET_FILES})
    set(LOCAL_QT_SOURCE_FILES ${LOCAL_QT_SOURCE_FILES} ${COMMON_ALGORITHM_QT_SOURCE_WIDGET_FILES})
    set(LOCAL_QT_SOURCE_QRC_FILES ${LOCAL_QT_SOURCE_QRC_FILES} ${COMMON_ALGORITHM_QT_QRC_FILES} )
    set(LOCAL_QT_SOURCE_UI_FILES ${LOCAL_QT_SOURCE_UI_FILES} ${COMMON_ALGORITHM_QT_UI_FILES} )
    
    # Set include directory.
    include_directories("${COMMON_INCLUDE_DIR_ALGORITHM}/Widgets")
endmacro()

