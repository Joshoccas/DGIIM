cmake_minimum_required(VERSION 3.13)
project(p03_pilas_colas)

set(CMAKE_CXX_STANDARD 14)

set(BASE_FOLDER estudiante)

include_directories(${BASE_FOLDER}/include)
add_library(maxstack ${BASE_FOLDER}/src/maxstack.cpp)
add_library(maxqueue ${BASE_FOLDER}/src/maxqueue.cpp)

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/pila_max.cpp)
    add_executable(pila_max ${BASE_FOLDER}/src/pila_max.cpp)
    target_link_libraries(pila_max maxstack)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/cola_max.cpp)
    add_executable(cola_max ${BASE_FOLDER}/src/cola_max.cpp)
    target_link_libraries(cola_max maxqueue)
endif()

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
