
project(PyGraphCodeTest LANGUAGES CXX VERSION 0.1.0)

find_package(Qt5 COMPONENTS Test REQUIRED)

# Turn on the compiler flag for gcov and lcov
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message(STATUS "Code coverage enabled")

    # Add coverage compiler flags
    set(COVERAGE_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_FLAGS}")
        
    # Add coverage linker flags
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
	set(PARENT_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})
	
else()
    message(WARNING "Coverage is not supported for this compiler.")
endif()

enable_testing()

set(TEST_HEADER
    #HardwareModelFactoryTest.h
	#calTest.h
	MainWindowManager.h
	TestSearchBarWidget.h
	
)

set(TEST_SOURCE
    #HardwareModelFactoryTest.cpp
	#calTest.cpp
	MainWindowManager.cpp
	TestSearchBarWidget.cpp
	
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

#Register the Test Project with Cmake
add_test(NAME UnitTest COMMAND ${PROJECT_NAME})


