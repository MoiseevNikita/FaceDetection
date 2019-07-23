cmake_minimum_required(VERSION 3.1)

project(FaceDetectionGUI VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (HEADERS
    imageviewer.h
    mainwindow.h
    zoomhandler.h
)

set (SOURCES
    imageviewer.cpp
    mainwindow.cpp
    zoomhandler.cpp
    main.cpp
)

set (FORMS
    imageviewer.ui
    mainwindow.ui
)

add_executable(${PROJECT_NAME}
    ${HEADERS}
    ${FORMS}
    ${SOURCES}
)

find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui)

add_subdirectory(../FaceDetectionLib facedetectionlib)
target_link_libraries(${PROJECT_NAME} FaceDetectionLib)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
    )

    set(CPACK_GENERATOR "DEB")
    set(CPACK_PACKAGE_CONTACT "Nikita Moiseev moiseevn96@gmail.com")
    include(CPack)
endif()
