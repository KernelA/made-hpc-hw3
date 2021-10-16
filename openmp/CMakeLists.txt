find_package(OpenMP REQUIRED)


set(_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE _headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${_include_dir}/*.h*)

set(POSTFIX "hello;parsec;privateshared;sumarray;bugreduction;bugparfoc")

foreach(name ${POSTFIX})
    message(STATUS "Add target for: ${name}")
    add_executable(${name}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/omp_${name}.c)
    target_include_directories(${name} PRIVATE ${_include_dir})
    target_link_libraries(${name} PRIVATE OpenMP::OpenMP_C)
endforeach()


set(CPP_CODE "outmes;monte_carlo")

foreach(name ${CPP_CODE})
    add_executable(${name}
            ${CMAKE_CURRENT_SOURCE_DIR}/src/omp_${name}.cpp)
    target_include_directories(${name} PRIVATE ${_include_dir})
    target_compile_features(${name} PRIVATE cxx_std_17)
    target_link_libraries(${name} PRIVATE OpenMP::OpenMP_CXX)
endforeach()


unset(_include_dir)

add_test(check_bugreduction bugreduction)
add_test(check_bugparfoc bugparfoc)