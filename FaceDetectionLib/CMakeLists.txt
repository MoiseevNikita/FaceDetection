cmake_minimum_required(VERSION 3.1)

project(FaceDetectionLib VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} SHARED imageanalyzer.cpp)

target_include_directories(${PROJECT_NAME}
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${PROJECT_NAME} PRIVATE BUILDING_SHARED_LIBRARY)

find_package(Qt5 COMPONENTS Core Network REQUIRED)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Network)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
    )
endif()
