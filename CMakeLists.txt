cmake_minimum_required(VERSION 3.10)
project(bag_of_visual_words)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(TBB REQUIRED tbb)
find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("include")

add_subdirectory(lib)

add_executable(place_recognition src/place_recognition.cpp)

target_link_libraries(place_recognition convert_dataset)
target_link_libraries(place_recognition serialize)
target_link_libraries(place_recognition imagebrowser)
target_link_libraries(place_recognition bow_histogram)
target_link_libraries(place_recognition ${OpenCV_LIBS})
target_link_libraries(place_recognition tbb)