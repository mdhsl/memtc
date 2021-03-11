cmake_minimum_required(VERSION 3.17)
project(native)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_FLAGS "-fpermissive -O3 -flto -fPIC ")

include_directories(.)

include_directories(/usr/lib/jvm/java-13-openjdk/include)
include_directories(/usr/lib/jvm/java-13-openjdk/include/linux)
include_directories(/usr/include/opencv4)

set(JAVA_HOME /usr/lib/jvm/java-13-openjdk)

set(JAVA_AWT_LIBRARY /usr/lib/jvm/default/include/jawt.h)
set(JAVA_INCLUDE_PATH2 /usr/lib/jvm/default/include/linux)
set(JAVA_AWT_INCLUDE_PATH /usr/lib/jvm/default/include)
set(JAVA_JVM_LIBRARY /usr/lib/jvm/default/include/jni.h)
find_package(JNI)

if (JNI_FOUND)
    message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
    message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
endif()

add_library(kduprocessor SHARED
        /usr/lib/jvm/default/include/jawt.h
        /usr/lib/jvm/default/include/jni.h
        MemoryManager.cpp MemoryManager.h)

target_link_libraries(memtc pthread tcmalloc)