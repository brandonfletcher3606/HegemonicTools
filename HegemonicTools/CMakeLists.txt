# cmake setup
cmake_minimum_required(VERSION 3.24)
project(HegemonicTools VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# get all sources files
file(GLOB SRC_FILES_HEGEMONIC_TOOLS 
        ${PROJECT_SOURCE_DIR}/src/*.cpp)

# get all include files
file(GLOB INC_FILES_HEGEMONIC_TOOLS 
        ${PROJECT_SOURCE_DIR}/include/*.h)

# set the directories for the install locations
# set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON) # this ignores any declspec compiler property, Hegemonic Math has no non-templates as of right now

configure_file(${PROJECT_SOURCE_DIR}/include/HegemonicToolsVersion.h.in "${PROJECT_SOURCE_DIR}/include/HegemonicToolsVersion.h")

# build executable and link libraries
include_directories(${PROJECT_SOURCE_DIR}/include/)
add_library(HegemonicTools SHARED ${SRC_FILES_HEGEMONIC_TOOLS})

# this add a compile tile variable to be used, BUILDING_HEGEMONIC_TOOLS is specific for declspec
target_compile_definitions(HegemonicTools PRIVATE BUILDING_HEGEMONIC_TOOLS=1)

# select directies for the dll/so/lib
set_target_properties(HegemonicTools PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/external/lib"   # Path for .lib
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/external/lib"   # Path for .so (Linux)
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/external/bin"   # Path for .dll
)

target_include_directories(HegemonicTools
    PUBLIC ${PROJECT_SOURCE_DIR}/include/)

# copy over files
#file(COPY ${PROJECT_SOURCE_DIR}/include/ DESTINATION ${PROJECT_SOURCE_DIR}/external/include/)
