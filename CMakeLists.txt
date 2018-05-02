cmake_minimum_required(VERSION 3.9)
project(macd_6122)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#QT setup

#Base QT directory
set(CMAKE_PREFIX_PATH /usr/local/opt/qt5)

#Build output path of your QT Creator project
if (WIN32)
    set(QT_BIN "${PROJECT_SOURCE_DIR}/QtBinDebug-Win64")
endif (WIN32)
if (UNIX)
    set(QT_BIN "${PROJECT_SOURCE_DIR}/QtBinDebug-MacOS")
endif (UNIX)
add_custom_target(qtMakeFile COMMAND make -C ${QT_BIN})

#Qt5 paths
#Qt5 library path
set(QT5_LIB_DIR ${CMAKE_PREFIX_PATH}/lib/cmake)
#Qt5 individual libraries
set(QT5_CORE ${QT_LIB_DIR}/Qt5Core)
set(QT5_WIDGETS ${QT_LIB_DIR}/Qt5Widgets)
set(QT5_GUI ${QT_LIB_DIR}/Qt5Gui)
set(QT5_Charts ${QT_LIB_DIR}/Qt5Charts)

#Libraries to link to. The :: is for convenience
set(QT_LIBRARIES Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Charts)
#Libraries required. Probably the same as above minus the '::'. find_package() will be called on these
set(QT_LIBRARIES_REQUIRED Qt5Core Qt5Widgets Qt5Gui Qt5Charts)

#find packages
foreach(QT_LIBRARIES_REQUIRED ${QT_LIBRARIES_REQUIRED})
    find_package( ${QT_LIBRARIES_REQUIRED} REQUIRED )
endforeach()

include_directories(${QT_BIN})

set(SOURCE_FILES main.cpp common.h macdchart.h macdchart.cpp)

add_executable(macd_6122 ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})