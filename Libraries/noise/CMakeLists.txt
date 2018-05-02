include(CMakeSources.cmake)
project(FastNoise)

option(FASTNOISE_INSTALL "Generate installation target" ON)

add_library(fastnoise ${LIB_TYPE} ${FASTNOISE_SOURCES})

target_include_directories(fastnoise PUBLIC ${FASTNOISE_INCLUDES})

target_compile_definitions(fastnoise PUBLIC
        -DFN_COMPILE_SSE2
        )

if(WIN32 AND BUILD_SHARED_LIBS)
	set_target_properties(fastnoise PROPERTIES PREFIX "")
endif()

# Install
if (FASTNOISE_INSTALL)
	install(TARGETS fastnoise
			EXPORT fastnoiseTargets
			ARCHIVE DESTINATION "lib"
			LIBRARY DESTINATION "lib"
	)

    foreach(file ${FASTNOISE_HEADERS_})
        get_filename_component(dir ${file} DIRECTORY)
        install(FILES ${file} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/noise/${dir})
    endforeach()
endif()
