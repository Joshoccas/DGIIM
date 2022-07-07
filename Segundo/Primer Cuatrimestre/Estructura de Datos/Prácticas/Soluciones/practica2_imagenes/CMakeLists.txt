cmake_minimum_required(VERSION 3.13)
project(practica2)

set(CMAKE_CXX_STANDARD 14)
set(BASE_FOLDER estudiante)

include_directories(${BASE_FOLDER}/include)
#add_library(imageio ${BASE_FOLDER}/src/imageio.cpp)
add_library(image ${BASE_FOLDER}/src/image.cpp ${BASE_FOLDER}/src/imageop.cpp ${BASE_FOLDER}/src/imageIO.cpp estudiante/src/icono.cpp estudiante/src/contraste.cpp)

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/negativo.cpp)
add_executable(negativo ${BASE_FOLDER}/src/negativo.cpp)
target_link_libraries(negativo LINK_PUBLIC image)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/subimagen.cpp)
add_executable(subimagen ${BASE_FOLDER}/src/subimagen.cpp)
target_link_libraries(subimagen LINK_PUBLIC image)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/zoom.cpp)
add_executable(zoom ${BASE_FOLDER}/src/zoom.cpp)
target_link_libraries(zoom LINK_PUBLIC image)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/icono.cpp)
add_executable(icono ${BASE_FOLDER}/src/icono.cpp)
target_link_libraries(icono LINK_PUBLIC image)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/contraste.cpp)
add_executable(contraste ${BASE_FOLDER}/src/contraste.cpp estudiante/src/contraste.cpp)
target_link_libraries(contraste LINK_PUBLIC image)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/barajar.cpp)
add_executable(barajar ${BASE_FOLDER}/src/barajar.cpp estudiante/src/barajar.cpp)
target_link_libraries(barajar LINK_PUBLIC image)
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
