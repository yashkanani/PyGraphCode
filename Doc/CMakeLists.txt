cmake_minimum_required(VERSION 3.10)
project(Doc LANGUAGES CXX VERSION 0.1.0)

find_package(Doxygen)
find_package(LATEX)
             
option(BUILD_DOCUMENTATION "Create and install the HTML based PyGraphCode documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
         message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
    
    if( NOT LATEX_FOUND OR NOT LATEX_PDFLATEX_FOUND)
         message("Latex is needed to build the documentation. you can download 3rd party tool from https://miktex.org/")
    endif()

    IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/output/)
        file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/output/)
    endif()

    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/output/)

    #configure_file(${doxyfile_in} ${doxyfile} @ONLY

    message("Doxygen build started.")

    if(WIN32)
     add_custom_target(
        ${PROJECT_NAME} ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile_in}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating PyGraphCode documentation with Doxygen"
        VERBATIM )
     
     if( LATEX_FOUND AND LATEX_PDFLATEX_FOUND)
        add_custom_command(TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND make 
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/output/latex/
            COMMENT "Generating PyGraphCode  documentation PDF file"
            VERBATIM)
     endif()   
     

    endif()

    SET_TARGET_PROPERTIES (${PROJECT_NAME} PROPERTIES FOLDER Document)

endif()
