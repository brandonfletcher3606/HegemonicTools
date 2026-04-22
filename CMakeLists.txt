# cmake setup
cmake_minimum_required(VERSION 3.23)
project(HegemonicToolsTotal)

message("Building HegemonicTools...")
add_subdirectory(HegemonicTools)
message("...Building HegemonicTools Complete")

message("Building HegemonicTools Test Harness...")
add_subdirectory(HegemonicTools_TestHarness)
message("...Building HegemonicTools Test Harness Complete")
