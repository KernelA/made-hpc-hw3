
find_package(BLAS REQUIRED)

set(_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE _headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${_include_dir}/*.h*)

add_executable(${PROJECT_NAME} ${_headers}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/matrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp)

SET(TEST_PROJECT_NAME "${PROJECT_NAME}-test")

add_executable(${TEST_PROJECT_NAME} ${_headers}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/matrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE ${_include_dir})
target_precompile_headers(${PROJECT_NAME} PRIVATE ${_include_dir}/stdafx.h)

target_compile_features(${TEST_PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${TEST_PROJECT_NAME} PRIVATE ${_include_dir})
target_precompile_headers(${TEST_PROJECT_NAME} PRIVATE ${_include_dir}/stdafx.h)
unset(_include_dir)
target_link_libraries(${TEST_PROJECT_NAME} PRIVATE BLAS::BLAS)

add_test(test_multiply ${TEST_PROJECT_NAME})
