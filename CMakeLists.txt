cmake_minimum_required(VERSION 3.20)
project(
    anvil 
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


file(GLOB_RECURSE srcs "${PROJECT_SOURCE_DIR}/irbuilder/**.hpp"
		"${PROJECT_SOURCE_DIR}/ir/**.hpp"
        "${PROJECT_SOURCE_DIR}/libanvil/**.cpp")

add_library(libanvil STATIC ${srcs})

add_executable(hello ${PROJECT_SOURCE_DIR}/examples/hello.cpp)

target_link_libraries(hello PRIVATE libanvil)



target_include_directories(libanvil
	PUBLIC
        ${PROJECT_SOURCE_DIR}/irbuilder
        ${PROJECT_SOURCE_DIR}/ir
        ${PROJECT_SOURCE_DIR}
)

set_target_properties(libanvil PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(libanvil PROPERTIES VERSION ${PROJECT_VERSION})

target_compile_options(libanvil PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4
        /EHsc
    >
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:
        -Wall
        -Wextra
        -Wpedantic
        -Wno-sign-compare
    >
)
