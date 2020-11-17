cmake_minimum_required (VERSION 2.8.11)
project (CoolPropTest)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED 1)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)

FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Gui)

set(COOLPROP_STATIC_LIBRARY true)
add_subdirectory ("${CMAKE_SOURCE_DIR}/CoolPropsLibrarys/CoolProp" CoolProp)


add_executable (${PROJECT_NAME}
    main.cpp)
target_link_libraries (${PROJECT_NAME}
    Qt5::Widgets
    Qt5::Gui
    CoolProp)
