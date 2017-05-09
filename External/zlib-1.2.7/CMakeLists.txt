cmake_minimum_required (VERSION 3.0.0)
project (zlib)

set(LN_SOURCES_zlib
	inftrees.c
	trees.c
	uncompr.c
	zutil.c
	adler32.c
	compress.c
	crc32.c
	deflate.c
	gzclose.c
	gzlib.c
	gzread.c
	gzwrite.c
	infback.c
	inffast.c
	inflate.c
)

# create project
add_library(${PROJECT_NAME} STATIC ${LN_SOURCES_zlib})

# copy include files
file(COPY "." DESTINATION "${LN_LIB_OUTPUT_ROOT_DIR}/${PROJECT_NAME}/include")
