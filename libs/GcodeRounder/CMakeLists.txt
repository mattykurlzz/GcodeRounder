add_library(GcodeRounder src/GcodeRounder.cpp)

target_compile_features(GcodeRounder PUBLIC cxx_std_20)

target_include_directories(GcodeRounder PUBLIC include)