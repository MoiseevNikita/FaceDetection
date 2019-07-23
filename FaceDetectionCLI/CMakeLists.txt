cmake_minimum_required(VERSION 3.1)

project(FaceDetectionCLI VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)

set (HEADERS
    analysisresultsreceiver.h
    resultsgenerator.h
)

set (SOURCES
    analysisresultsreceiver.cpp
    resultsgenerator.cpp
    main.cpp
)

add_executable(${PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
)

find_package(Qt5 COMPONENTS Core Gui REQUIRED)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui)

add_subdirectory(../FaceDetectionLib facedetectionlib)
target_link_libraries(${PROJECT_NAME} FaceDetectionLib)
