cmake_minimum_required(VERSION 3.13.0)

project(QtSCXMLPlayground)

set(CMAKE_CONFIGURATION_TYPES "Debug;RelWithDebInfo" CACHE STRING 
    "Semicolon separated list of supported configuration types, only supports ${CMAKE_CONFIGURATION_TYPES} anything else will be ignored." FORCE)
set(BUILD_OUTPUT_DIR "${CMAKE_BINARY_DIR}/x64" CACHE STRING "Where to put your *.exe, *dll, etc." FORCE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

find_package(Qt5 COMPONENTS 
Core 
Gui 
Widgets 
Scxml
)

file(GLOB_RECURSE Headers   "include/QtSCXMLPlayground/*")
source_group("Header files" FILES ${Headers})

file(GLOB_RECURSE Sources   "src/*.h" "src/*.cpp")
source_group("Source files" FILES ${Sources})

file(GLOB_RECURSE Forms   "src/*.ui")
source_group("Forms" FILES ${Forms})

file(GLOB_RECURSE StateCharts   "src/*.scxml")
source_group("State charts" FILES ${StateCharts})
if (Qt5Scxml_FOUND)
    include("${Qt5Scxml_DIR}/Qt5ScxmlMacros.cmake")
    qt5_add_statecharts(QT_SCXML_COMPILED ${StateCharts})
    set_property(SOURCE ${QT_SCXML_COMPILED} PROPERTY SKIP_AUTOMOC ON)
else()
    message(SEND_ERROR "Can't find Qt5 scxml")
endif()

add_executable(QtSCXMLPlayground ${Headers} ${Sources} ${Forms} ${StateCharts} ${QT_SCXML_COMPILED})
set_target_properties(QtSCXMLPlayground PROPERTIES OUTPUT_NAME "QtSCXMLPlayground")

target_link_libraries(QtSCXMLPlayground
Qt5::Core
Qt5::Gui
Qt5::Widgets
Qt5::Scxml
)

target_include_directories(QtSCXMLPlayground PRIVATE
"${CMAKE_CURRENT_SOURCE_DIR}/include/QtSCXMLPlayground"
"${CMAKE_BINARY_DIR}/include"
"${CMAKE_CURRENT_BINARY_DIR}"
) 
