project(PyGraphCode LANGUAGES CXX VERSION 0.1.0)

# Hide the seprate console window.
if(WIN32)
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES} main.cpp)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
SET_TARGET_PROPERTIES (${PROJECT_NAME} PROPERTIES FOLDER src)