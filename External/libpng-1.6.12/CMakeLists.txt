cmake_minimum_required (VERSION 3.0.0)
project (libpng)

set(LN_SOURCES_libpng
	pngwtran.c
	pngwutil.c
	png.c
	pngerror.c
	pngget.c
	pngmem.c
	pngpread.c
	pngread.c
	pngrio.c
	pngrtran.c
	pngrutil.c
	pngset.c
	pngtrans.c
	pngwio.c
	pngwrite.c
)

# create project
add_library(${PROJECT_NAME} STATIC ${LN_SOURCES_libpng})

# include dir
include_directories(${PROJECT_SOURCE_DIR}/../zlib-1.2.7)

# copy include files
file(COPY "." DESTINATION "${LN_LIB_OUTPUT_ROOT_DIR}/${PROJECT_NAME}/include")
