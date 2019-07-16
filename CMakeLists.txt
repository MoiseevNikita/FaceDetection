cmake_minimum_required(VERSION 3.1.0)

project(facedetector VERSION 1.0.0 LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets Core Gui Network REQUIRED)

set (SOURCES
    facedetectionrequestsender.cpp
    imageviewer.cpp
    mainwindow.cpp
    zoomhandler.cpp
    main.cpp
)

set (HEADERS
    facedetectionrequestsender.h
    imageviewer.h
    mainwindow.h
    ui_imageviewer.h
    ui_mainwindow.h
    zoomhandler.h
)

set (FORMS
    mainwindow.ui
    imageviewer.ui
)

add_executable(${PROJECT_NAME}
    ${HEADERS}
    ${FORMS}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network)
