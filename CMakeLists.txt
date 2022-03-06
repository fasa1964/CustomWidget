cmake_minimum_required(VERSION 3.5)

project(CustomWidget VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES CustomWidget_de_DE.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        formcustomwidget.h
        formcustomwidget.cpp
        formcustomwidget.ui
        images.qrc
        dialoginfo.h dialoginfo.cpp dialoginfo.ui
        ${TS_FILES}
)

#if (WIN32)
#set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/resources/images.rc")
#qt_add_executable(CustomWidget main.cpp ${app_icon_resource_windows})
#endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    #set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/images.qrc")
    qt_add_executable(CustomWidget MANUAL_FINALIZATION ${PROJECT_SOURCES})

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CustomWidget APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(CustomWidget SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CustomWidget
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(CustomWidget PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(CustomWidget PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CustomWidget)
endif()
