cmake_minimum_required(VERSION 3.10)
project(PyGraphCode LANGUAGES CXX VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

# For IDE intellisense support
set(CMAKE_EXPORT_COMPILE_COMMANDS)

SET(CMAKE_OSX_DEPLOYMENT_TARGET 10.14)

find_package(Qt5 COMPONENTS Core Concurrent Widgets Gui OpenGL Test Network REQUIRED)
#enable_testing()

set(HEADERS
	  	
        ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindow.h
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindowUI.h
   )
set(SOURCES
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindow.cpp
	  ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindowUI.cpp	
    )

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL Qt5::Concurrent Qt5::Network)


