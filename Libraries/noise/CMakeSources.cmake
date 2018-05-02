set(FASTNOISE_HEADERS_
  #      "include/FastNoise/ARM/cpu-features.h"
		"include/FastNoise/FastNoiseSIMD.h"
        "include/FastNoise/FastNoiseSIMD_internal.h"
)

set(FASTNOISE_SOURCES_
  #      "src/FastNoise/ARM/cpu-features.c"
		"src/FastNoise/FastNoiseSIMD.cpp"
		"src/FastNoise/FastNoiseSIMD_avx2.cpp"
		"src/FastNoise/FastNoiseSIMD_avx512.cpp"
		"src/FastNoise/FastNoiseSIMD_internal.cpp"
		"src/FastNoise/FastNoiseSIMD_neon.cpp"
		"src/FastNoise/FastNoiseSIMD_sse2.cpp"
		"src/FastNoise/FastNoiseSIMD_sse41.cpp"
)

source_group("Header Files" FILES ${FASTNOISE_HEADERS_})
source_group("Source Files" FILES ${FASTNOISE_SOURCES_})

set(FASTNOISE_SOURCES
	${FASTNOISE_HEADERS_}
	${FASTNOISE_SOURCES_}
)
