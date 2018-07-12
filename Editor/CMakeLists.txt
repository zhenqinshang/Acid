include(CMakeSources.cmake)
#project(Editor)

set(EDITOR_INCLUDES "${PROJECT_SOURCE_DIR}/Editor/")

#if(FL_BUILD_RELEASE AND WIN32)
#	add_executable(Editor WIN32 ${EDITOR_SOURCES})
#else()
add_executable(Editor ${EDITOR_SOURCES})
#endif()

set_target_properties(Editor PROPERTIES
                      POSITION_INDEPENDENT_CODE ON
                      FOLDER "Flounder")

add_dependencies(Editor Flounder)

target_include_directories(Editor PUBLIC ${LIBRARIES_INCLUDES} "${PROJECT_SOURCE_DIR}/Sources/" ${EDITOR_INCLUDES})
target_link_libraries(Editor PRIVATE ${LIBRARIES_LINKS} Flounder)

# Install
if (FLOUNDER_INSTALL)
    install(DIRECTORY .
            DESTINATION include
            FILES_MATCHING PATTERN "*.h"
            PATTERN "Private" EXCLUDE
            )

    install(TARGETS Editor
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            )
endif ()