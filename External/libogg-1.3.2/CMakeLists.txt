cmake_minimum_required (VERSION 3.0.0)
project (libogg)

set(LN_SOURCES_libogg
	include/ogg/os_types.h
	include/ogg/config_types.h
	include/ogg/ogg.h
	src/bitwise.c
	src/framing.c
)

set(LN_LIB_OUTPUT_DIR "${LN_LIB_OUTPUT_ROOT_DIR}/${PROJECT_NAME}/${LN_LIB_OUTPUT_LOCAL_DIR}")
add_library(${PROJECT_NAME} STATIC ${LN_SOURCES_libogg})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}${LN_STATIC_LIB_POSTFIX}")
set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${LN_LIB_OUTPUT_DIR}")

# include dir
include_directories(
	${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/include
)

if (MSVC)
	add_definitions("/wd4996")		# pragma warning disable
endif()

# copy include files
file(COPY "include" DESTINATION "${LN_LIB_OUTPUT_ROOT_DIR}/${PROJECT_NAME}")
