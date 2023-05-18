cmake_minimum_required(VERSION 3.10)
project(PyGraphCode LANGUAGES CXX VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

# Hide the seprate console window.
if(WIN32)
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()

# For IDE intellisense support
set(CMAKE_EXPORT_COMPILE_COMMANDS)

# set the IOS minimum version 10.14
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Concurrent Widgets Quick Gui OpenGL Test Network QuickWidgets REQUIRED)
#enable_testing()

# Add resource files
set(RESOURCES 
   ${CMAKE_CURRENT_SOURCE_DIR}/src/resources.qrc
   ${CMAKE_CURRENT_SOURCE_DIR}/src/qml/CustomToolBarItem.qml
   ${CMAKE_CURRENT_SOURCE_DIR}/src/qml/SerachBar.qml
  
)


set(HEADERS	
      ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindow.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindowUI.h
   )
set(SOURCES
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindow.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindowUI.cpp	
    )


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL Qt5::Concurrent Qt5::Network Qt5::Quick Qt5::QuickWidgets)


