
find_package(Doxygen REQUIRED)

# set the in and out documentation dirs
set(DOXYGEN_INPUT_DIR ${CT_FRWK_PATH})
set(DOXYGEN_OUTPUT_DIR ${PROJECT_BINARY_DIR}/docs)

# see if we can generate the CHM documentation
if(CT_OS_WINDOWS)
    # if HHC is found, we can generate the CHM (compressed HTML) output
    find_program(DOXYGEN_HHC_PROGRAM
                 NAMES hhc.exe
                 PATHS "C:/Program Files/HTML Help Workshop" "C:/Program Files (x86)/HTML Help Workshop"
                 DOC "HTML Help Compiler program")
    if(DOXYGEN_HHC_PROGRAM)
        set(DOXYGEN_GENERATE_HTMLHELP YES)
    else()
        set(DOXYGEN_GENERATE_HTMLHELP NO)
    endif()
else()
    set(DOXYGEN_HHC_PROGRAM)
    set(DOXYGEN_GENERATE_HTMLHELP NO)
endif()

set(DOXYGEN_CONFIGURED_INPUT ${DOXYGEN_OUTPUT_DIR}/Doxyfile)
configure_file(${DOXYGEN_INPUT_DIR}/docs/Doxyfile ${DOXYGEN_CONFIGURED_INPUT} @ONLY)
configure_file(${DOXYGEN_INPUT_DIR}/docs/header.html ${DOXYGEN_OUTPUT_DIR}/header.html @ONLY)
configure_file(${DOXYGEN_INPUT_DIR}/docs/style.css ${DOXYGEN_OUTPUT_DIR}/html/style.css COPYONLY)

# target setup
add_custom_target(doc ALL
                  COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
                  COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED_INPUT}
                  COMMAND ${CMAKE_COMMAND} -E echo "Done."
                  WORKING_DIRECTORY ${DOXYGEN_INPUT_DIR})

# setup install rules
install(FILES ${DOXYGEN_OUTPUT_DIR}/ct.tag
        DESTINATION ${CMAKE_INSTALL_DOCDIR}
        COMPONENT doc)

install(DIRECTORY ${DOXYGEN_OUTPUT_DIR}/html
        DESTINATION ${CMAKE_INSTALL_DOCDIR}
        COMPONENT doc)

if(DOXYGEN_HHC_PROGRAM)
    install(FILES ${DOXYGEN_OUTPUT_DIR}/ct.chm
            DESTINATION ${CMAKE_INSTALL_DOCDIR}
            COMPONENT doc)
endif()
