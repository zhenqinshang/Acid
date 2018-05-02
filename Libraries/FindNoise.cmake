set(FASTNOISE_INCLUDES "${PROJECT_SOURCE_DIR}/Libraries/noise/include")
set(FASTNOISE_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory(${PROJECT_SOURCE_DIR}/Libraries/noise)
set(FASTNOISE_LIBRARY "fastnoise")

set(LIBRARIES_INCLUDES ${LIBRARIES_INCLUDES} ${FASTNOISE_INCLUDES})
set(LIBRARIES_LINKS ${LIBRARIES_LINKS} "${FASTNOISE_LIBRARY}")

if(NOT FASTNOISE_LIBRARY)
	message(FATAL_ERROR "FastNoise library not found!")
endif()
