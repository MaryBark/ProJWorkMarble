cmake_minimum_required(VERSION 3.5)

project(ForMarbleQtWidgets VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# указываем в нашем проекте где лежат дополнительные .cmake файлы
LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" "${PROJECT_SOURCE_DIR}/import/cmake")

# выполняем поиск marble-библиотеки, см. выше файл FindMarble.cmake
find_package(Marble)
if (Marble_FOUND)
  message( STATUS "Marble includes: ${Marble_INCLUDE_DIR}")
  message( STATUS "Marble libraries: ${Marble_LIBRARIES}")
else()
  message(WARNING "Not found Marble!")
endif()




find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ForMarbleQtWidgets
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ForMarbleQtWidgets APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ForMarbleQtWidgets SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ForMarbleQtWidgets
            ${PROJECT_SOURCES}
        )
    endif()
endif()




# настраиваем includes
include_directories("${Marble_INCLUDE_DIR}")  # заголовочные файлы marble-библиотеки
# создаём приложение
add_executable(my_application main.cpp)
# подключаем к приложению библиотеку marble
target_link_libraries(my_application ${Marble_LIBRARIES})





target_link_libraries(ForMarbleQtWidgets PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(ForMarbleQtWidgets PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ForMarbleQtWidgets)
endif()
