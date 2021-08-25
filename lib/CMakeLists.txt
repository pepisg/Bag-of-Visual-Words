find_package(Boost 1.66.0 COMPONENTS filesystem)
find_package(TBB REQUIRED tbb)
find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS}) 
include_directories("include")


# Html writer library
add_library(
    htmlwriter
    htmlwriter/html_writer.cpp
    htmlwriter/include/htmlwriter/html_writer.hpp
)
target_link_libraries(htmlwriter fmt)
target_link_libraries(htmlwriter ${Boost_LIBRARIES})
target_include_directories(htmlwriter PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/htmlwriter/include")

# Image browser library
add_library(
    imagebrowser
    imagebrowser/include/imagebrowser/image_browser.hpp
    imagebrowser/image_browser.cpp
)
target_link_libraries(imagebrowser htmlwriter)
target_include_directories(imagebrowser PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/imagebrowser/include")

# Serialization libraries
add_library(
    serialize
    serialization/src/serialize.cpp
    serialization/include/serialization/serialize.hpp
)

add_library(
    convert_dataset
    serialization/src/convert_dataset.cpp
    serialization/include/serialization/convert_dataset.hpp
)

target_include_directories(convert_dataset PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/serialization/include")
target_include_directories(serialize PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/serialization/include")

target_link_libraries(convert_dataset serialize)

# Bow dictionary and histogram library
add_library(
    bow_histogram
    bow_histogram/src/bow.cpp
    bow_histogram/include/bow_histogram/bow.hpp
)

target_link_libraries(bow_histogram convert_dataset)
target_link_libraries(bow_histogram serialize)
target_link_libraries(bow_histogram ${OpenCV_LIBS})
target_link_libraries(bow_histogram tbb)

target_include_directories(bow_histogram PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/bow_histogram/include")
