cmake_minimum_required(VERSION 3.5)
project(HelloV8)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-stdlib=libc++ ")
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.9)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)


#if (CMAKE_BUILD_TYPE STREQUAL Release)
#    set(LIB_TYPE static)
#else ()
set(LIB_TYPE shared)
#endif ()
set(OS_ARCH darwin-x64-${LIB_TYPE})

function(find_include_dirs out)
    file(GLOB_RECURSE headers ${ARGN})
    foreach (path ${headers})
        get_filename_component(dir ${path} PATH)
        list(APPEND include_dirs ${dir})
    endforeach ()
    list(REMOVE_DUPLICATES include_dirs)
    set(${out} ${include_dirs} PARENT_SCOPE)
endfunction()

find_include_dirs(includes third_party/v8/include/*.h)
include_directories(${includes} src)

set(RESOURCE_FILES)

function(copy_file from to)
    set(temp ${RESOURCE_FILES})
    list(APPEND temp ${to})
    set(RESOURCE_FILES ${temp} PARENT_SCOPE)
    add_custom_command(OUTPUT ${to}
            COMMAND ${CMAKE_COMMAND} -E copy ${from} ${to}
            MAIN_DEPENDENCY ${from})
endfunction()

set(v8_lib)
if (LIB_TYPE STREQUAL static)
    file(GLOB_RECURSE v8_lib third_party/v8/${OS_ARCH}/*.a)
else ()
    file(GLOB_RECURSE v8_lib third_party/v8/${OS_ARCH}/*.dylib third_party/v8/${OS_ARCH}/*.so)
    foreach (path ${v8_lib})
        get_filename_component(fileName ${path} NAME)
        copy_file(${path} ${CMAKE_BINARY_DIR}/${fileName})
    endforeach ()
endif ()

copy_file(${CMAKE_SOURCE_DIR}/src/js/JSTest.js ${CMAKE_BINARY_DIR}/JSTest.js)
#copy natives_blob.bin and snapshot_blob.bin which v8 requires to the root of binary dir.
copy_file(${CMAKE_SOURCE_DIR}/third_party/v8/${OS_ARCH}/natives_blob.bin ${CMAKE_BINARY_DIR}/natives_blob.bin)
copy_file(${CMAKE_SOURCE_DIR}/third_party/v8/${OS_ARCH}/snapshot_blob.bin ${CMAKE_BINARY_DIR}/snapshot_blob.bin)

add_custom_target(CopyResource ALL DEPENDS ${RESOURCE_FILES})
link_directories(${CMAKE_BINARY_DIR})
add_executable(Main ${SOURCE_FILES})
target_link_libraries(Main ${v8_lib})