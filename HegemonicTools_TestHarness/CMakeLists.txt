cmake_minimum_required(VERSION 3.23)
project(HegemonicTools_TestHarness)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# add the testing and google test informationd
enable_testing()
add_subdirectory(googletest)

# get all sources files
file(GLOB SRC_FILES_HEGEMONIC_TOOLS_TH 
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/StubData/*)

# get all include files
file(GLOB INC_FILES_HEGEMONIC_TOOLS_TH 
        ${PROJECT_SOURCE_DIR}/include/*.h)

# target Hegemonic tools information
set_target_properties(HegemonicTools PROPERTIES
    IMPORTED_IMPLIB               "${PROJECT_SOURCE_DIR}/../HegemonicTools/external/lib/Debug/HegemonicTools.lib"
    IMPORTED_LOCATION             "${PROJECT_SOURCE_DIR}/../HegemonicTools/external/bin/Debug/HegemonicTools.dll"
    INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/../HegemonicTools/external/include/"
)

# build Hegemonit Tools TH
include_directories(${PROJECT_SOURCE_DIR}/include/)
add_executable(HegemonicTools_TestHarness ${SRC_FILES_HEGEMONIC_TOOLS_TH})

# link the libraries using in this tool
target_link_libraries(HegemonicTools_TestHarness 
        PUBLIC gtest_main
        PRIVATE HegemonicTools)

# this command copies all the dlls to where the executable is
add_custom_command(TARGET HegemonicTools_TestHarness POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:HegemonicTools_TestHarness> $<TARGET_FILE_DIR:HegemonicTools_TestHarness>
  COMMAND_EXPAND_LISTS
)

add_test(NAME HegemonicTools_TestHarness
    COMMAND HegemonicTools_TestHarness)