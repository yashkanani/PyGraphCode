
project(PyGraphCodeTest LANGUAGES CXX VERSION 0.1.0)

find_package(Qt5 COMPONENTS Test REQUIRED)


set(TEST_HEADER
    #HardwareModelFactoryTest.h
	#calTest.h
	MainWindowManager.h
	TestSearchBarWidget.h
	TestBuilderContainer.h
)

set(TEST_SOURCE
    #HardwareModelFactoryTest.cpp
	#calTest.cpp
	MainWindowManager.cpp
	TestSearchBarWidget.cpp
	TestBuilderContainer.cpp
)

set(TEST_HELPERS
	BaseTest.cpp
	BaseTest.h
	TestManager.cpp
	TestManager.h
	main.cpp
)

# Provide acess to source file access.
include_directories(${CMAKE_SOURCE_DIR}/src)

enable_testing()

add_executable(${PROJECT_NAME} ${TEST_HEADER} ${TEST_SOURCE} ${TEST_HELPERS} ${SOURCES} ${HEADERS} ${RESOURCES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Test)
SET_TARGET_PROPERTIES (${PROJECT_NAME} PROPERTIES FOLDER test)

