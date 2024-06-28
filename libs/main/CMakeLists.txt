add_executable(main src/main.cpp)

target_compile_features(main PUBLIC cxx_std_20)

configure_file(./test/example.TXT ./test/example.TXT COPYONLY)