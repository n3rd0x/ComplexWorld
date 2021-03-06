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
# Configurations
# ************************************************************
set(COMMON_PATH_ROOT "${PROJECT_PATH_SOURCE}/Common/Generic")
set(COMMON_PATH_HEADER "${COMMON_PATH_ROOT}/include")
set(COMMON_PATH_SOURCE "${COMMON_PATH_ROOT}/src")
set(COMMON_INCLUDE_DIR "${COMMON_PATH_HEADER}")




# ************************************************************
# Header Files
# ************************************************************
set(COMMON_HEADER_FILES
)




# ************************************************************
# Source Files
# ************************************************************
set(COMMON_SOURCE_FILES
)




# ************************************************************
# Macro
# ************************************************************
# Set header and source files.
macro(ENABLE_COMMON_FILES)
    # Group files.
    source_group("Header Files\\Common\\Library" FILES ${COMMON_HEADER_FILES})
    source_group("Source Files\\Common\\Library" FILES ${COMMON_SOURCE_FILES})
    
    # Add into global header file variable.
    set(LOCAL_HEADER_FILES ${LOCAL_HEADER_FILES} ${COMMON_HEADER_FILES})
    set(LOCAL_SOURCE_FILES ${LOCAL_SOURCE_FILES} ${COMMON_SOURCE_FILES})
    
    # Set include directory.
    include_directories(${COMMON_INCLUDE_DIR})
endmacro()

