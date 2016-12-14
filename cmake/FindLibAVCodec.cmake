
set(LIBAVCODEC_OLD FALSE)
set(LIBAVCODEC_NEW FALSE)
find_path(LIBAVCODEC_INCLUDE_DIR_NEW libavcodec/avcodec.h)
if (NOT LIBAVCODEC_INCLUDE_DIR_NEW)
	find_path(LIBAVCODEC_INCLUDE_DIR_OLD ffmpeg/avcodec.h)
	if (LIBAVCODEC_INCLUDE_DIR_OLD)
		set(LIBAVCODEC_INCLUDE_DIRS ${LIBAVCODEC_INCLUDE_DIR_OLD})
		set(LIBAVCODEC_OLD TRUE)
	endif (LIBAVCODEC_INCLUDE_DIR_OLD)
else (NOT LIBAVCODEC_INCLUDE_DIR_NEW)
	set(LIBAVCODEC_INCLUDE_DIRS ${LIBAVCODEC_INCLUDE_DIR_NEW})
	set(LIBAVCODEC_NEW TRUE)
endif (NOT LIBAVCODEC_INCLUDE_DIR_NEW)

if (LIBAVCODEC_OLD OR LIBAVCODEC_NEW)
	find_library(LIBAVCODEC_LIB_AVCODEC avcodec)

	if (LIBAVCODEC_LIB_AVCODEC)
		set(LIBAVCODEC_LIBRARIES ${LIBAVCODEC_LIB_AVCODEC})
		find_library(LIBAVCODEC_LIB_AVUTIL avutil)
		find_library(LIBAVCODEC_LIB_SWSCALE swscale)
		find_library(LIBAVCODEC_LIB_AVCORE avcore)
		find_library(LIBAVCODEC_LIB_AVFILTER avfilter)
		if (LIBAVCODEC_LIB_AVUTIL)
			set(LIBAVCODEC_LIBRARIES ${LIBAVCODEC_LIBRARIES} ${LIBAVCODEC_LIB_AVUTIL})
		endif (LIBAVCODEC_LIB_AVUTIL)
		if (LIBAVCODEC_LIB_SWSCALE)
			set(LIBAVCODEC_LIBRARIES ${LIBAVCODEC_LIBRARIES} ${LIBAVCODEC_LIB_SWSCALE})
		endif (LIBAVCODEC_LIB_SWSCALE)
		if (LIBAVCODEC_LIB_AVCORE)
			set(LIBAVCODEC_LIBRARIES ${LIBAVCODEC_LIBRARIES} ${LIBAVCODEC_LIB_AVCORE})
		endif (LIBAVCODEC_LIB_AVCORE)
	endif (LIBAVCODEC_LIB_AVCODEC)
endif (LIBAVCODEC_OLD OR LIBAVCODEC_NEW)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(LibAVCodec DEFAULT_MSG LIBAVCODEC_INCLUDE_DIRS LIBAVCODEC_LIBRARIES)

