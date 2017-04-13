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
# Root directories.
set(COMMON_PATH_PROGRAMMING_GAME_AI_ROOT "${PROJECT_PATH_SOURCE}/Common/Programming-Game-AI")
set(COMMON_PATH_PROGRAMMING_GAME_AI_ROOT_COMMON "${COMMON_PATH_PROGRAMMING_GAME_AI_ROOT}/Common")
set(COMMON_PATH_PROGRAMMING_GAME_AI_ROOT_STEERING_BEHAVIOURS "${COMMON_PATH_PROGRAMMING_GAME_AI_ROOT}/Steering-Behaviours")

# Section directories.
set(COMMON_PATH_PROGRAMMING_GAME_AI_HEADER_COMMON "${COMMON_PATH_PROGRAMMING_GAME_AI_ROOT_COMMON}/include")
set(COMMON_PATH_PROGRAMMING_GAME_AI_SOURCE_COMMON "${COMMON_PATH_PROGRAMMING_GAME_AI_ROOT_COMMON}/src")

set(COMMON_PATH_PROGRAMMING_GAME_AI_HEADER_STEERING_BEHAVIOURS "${COMMON_PATH_PROGRAMMING_GAME_AI_ROOT_STEERING_BEHAVIOURS}/include")
set(COMMON_PATH_PROGRAMMING_GAME_AI_SOURCE_STEERING_BEHAVIOURS "${COMMON_PATH_PROGRAMMING_GAME_AI_ROOT_STEERING_BEHAVIOURS}/src")

# Include directories.
set(COMMON_INCLUDE_DIR_PROGRAMMING_GAME_AI_COMMON "${COMMON_PATH_PROGRAMMING_GAME_AI_HEADER_COMMON}")
set(COMMON_INCLUDE_DIR_PROGRAMMING_GAME_AI_STEERING_BEHAVIOURS "${COMMON_PATH_PROGRAMMING_GAME_AI_HEADER_STEERING_BEHAVIOURS}")




# ************************************************************
# Header Files
# ************************************************************
set(COMMON_PROGRAMMING_GAME_AI_HEADER_FILES_COMMON
    "${COMMON_PATH_PROGRAMMING_GAME_AI_HEADER_COMMON}/BaseGameEntity.h"
    "${COMMON_PATH_PROGRAMMING_GAME_AI_HEADER_COMMON}/MessageDispatcher.h"
    "${COMMON_PATH_PROGRAMMING_GAME_AI_HEADER_COMMON}/Telegram.h"
)

set(COMMON_PROGRAMMING_GAME_AI_HEADER_FILES_STEERING_BEHAVIOURS
)




# ************************************************************
# Source Files
# ************************************************************
set(COMMON_PROGRAMMING_GAME_AI_SOURCE_FILES_COMMON
    "${COMMON_PATH_PROGRAMMING_GAME_AI_SOURCE_COMMON}/BaseGameEntity.cpp"
    "${COMMON_PATH_PROGRAMMING_GAME_AI_SOURCE_COMMON}/MessageDispatcher.cpp"
    "${COMMON_PATH_PROGRAMMING_GAME_AI_SOURCE_COMMON}/Telegram.cpp"
)

set(COMMON_PROGRAMMING_GAME_AI_SOURCE_FILES_STEERING_BEHAVIOURS
)




# ************************************************************
# Macro
# ************************************************************
macro(ENABLE_PROGRAMMING_GAME_AI_COMMON_COMMON_FILES)
    # Group files.
    source_group("Header Files\\ProgrammingGameAI\\Common" FILES ${COMMON_PROGRAMMING_GAME_AI_HEADER_FILES_COMMON})
    source_group("Source Files\\ProgrammingGameAI\\Common" FILES ${COMMON_PROGRAMMING_GAME_AI_SOURCE_FILES_COMMON})
    
    # Add into global header file variable.
    set(LOCAL_HEADER_FILES ${LOCAL_HEADER_FILES} ${COMMON_PROGRAMMING_GAME_AI_HEADER_FILES_COMMON})
    set(LOCAL_SOURCE_FILES ${LOCAL_SOURCE_FILES} ${COMMON_PROGRAMMING_GAME_AI_SOURCE_FILES_COMMON})
    
    # Set include directory.
    include_directories(${COMMON_INCLUDE_DIR_PROGRAMMING_GAME_AI_COMMON})
endmacro()


macro(ENABLE_PROGRAMMING_GAME_AI_STEERING_BEHAVIOURS_COMMON_FILES)
    # Group files.
    source_group("Header Files\\ProgrammingGameAI\\Steering-Behaviours" FILES ${COMMON_PROGRAMMING_GAME_AI_HEADER_FILES_STEERING_BEHAVIOURS})
    source_group("Source Files\\ProgrammingGameAI\\Steering-Behaviours" FILES ${COMMON_PROGRAMMING_GAME_AI_SOURCE_FILES_STEERING_BEHAVIOURS})
    
    # Add into global header file variable.
    set(LOCAL_HEADER_FILES ${LOCAL_HEADER_FILES} ${COMMON_PROGRAMMING_GAME_AI_HEADER_FILES_STEERING_BEHAVIOURS})
    set(LOCAL_SOURCE_FILES ${LOCAL_SOURCE_FILES} ${COMMON_PROGRAMMING_GAME_AI_SOURCE_FILES_STEERING_BEHAVIOURS})
    
    # Set include directory.
    include_directories(${COMMON_INCLUDE_DIR_PROGRAMMING_GAME_AI_STEERING_BEHAVIOURS})
endmacro()

