cmake_minimum_required(VERSION 3.5)

project(FaceSpyder VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia MultimediaWidgets)

set(OpenCV_DIR "C:/Program Files/opencv/build")

find_package(OpenCV CONFIG REQUIRED)

set(PROJECT_SOURCES
        main.cpp
)
set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/resources/app_icon.rc")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(FaceSpyder
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${app_icon_resource_windows}
        facerecognitionview.h facerecognitionview.cpp
        facedetectionview.h facedetectionview.cpp
        observer.h observer.cpp
        facerecognition.h facerecognition.cpp
        pch.h
        item.h item.cpp
        image.h image.cpp
        video.h video.cpp
        imagematching.h imagematching.cpp
        itemdetectedview.h itemdetectedview.cpp
        spyderwindow.h spyderwindow.cpp
        menubutton.h menubutton.cpp
        videoplayer.h videoplayer.cpp
        facedetectionworker.h facedetectionworker.cpp
        loadingwindow.h loadingwindow.cpp
        mainwindow.h mainwindow.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET FaceSpyder APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(FaceSpyder SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(FaceSpyder
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(FaceSpyder PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets ${OpenCV_LIBS})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.FaceSpyder)
endif()
set_target_properties(FaceSpyder PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/
       DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/)


include(GNUInstallDirs)
install(TARGETS FaceSpyder
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FaceSpyder)
endif()
