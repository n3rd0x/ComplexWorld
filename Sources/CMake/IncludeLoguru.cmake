# ************************************************************
# Project:  TimeSheet
# Author:   T.Sang Tran
# ************************************************************


# ************************************************************
# Configurations
# ************************************************************
# Set path.
set(THIRD_PARTY_LOGURU_PATH_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/Third-Parties/loguru/2.1.0")

# Set path to header and source directory.
set(THIRD_PARTY_LOGURU_PATH_HEADER "${THIRD_PARTY_LOGURU_PATH_ROOT}")
set(THIRD_PARTY_LOGURU_PATH_SOURCE "${THIRD_PARTY_LOGURU_PATH_ROOT}")
set(THIRD_PARTY_LOGURU_INCLUDE_DIR "${THIRD_PARTY_LOGURU_PATH_HEADER}")

# Enable stream for Loguru.
add_definitions(-DLOGURU_WITH_STREAMS=1)


# ************************************************************
# List Files
# ************************************************************
file(GLOB THIRD_PARTY_LOGURU_HEADER_FILES ${THIRD_PARTY_LOGURU_PATH_HEADER}/*.hpp)
file(GLOB THIRD_PARTY_LOGURU_SOURCE_FILES ${THIRD_PARTY_LOGURU_PATH_SOURCE}/*.cpp)
