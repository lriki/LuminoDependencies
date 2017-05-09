cmake_minimum_required (VERSION 3.0.0)
project (giflib)

set(LN_SOURCES_giflib
	quantize.c
	dgif_lib.c
	egif_lib.c
	gif_err.c
	gif_font.c
	gif_hash.c
	gif_hash.h
	gif_lib.h
	gif_lib_private.h
	gifalloc.c
	openbsd-reallocarray.c
)

# create project
add_library(${PROJECT_NAME} STATIC ${LN_SOURCES_giflib})

# copy include files
file(COPY "." DESTINATION "${LN_LIB_OUTPUT_ROOT_DIR}/${PROJECT_NAME}/include")
