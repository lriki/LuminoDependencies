# このファイルは Lumino 本体の CMakeLists.txt から include されるファイルです。
# (LuminoDependencies 自体のビルドでは使われません)
# 以下の変数に、各種外部ライブラリのインクルードパスと、ビルド済みライブラリへのパスを設定します。
# - LN_DEPENDENCIES_INCLUDES
# - LN_DEPENDENCIES_LIBRARIES_DEBUG
# - LN_DEPENDENCIES_LIBRARIES_RELEASE
#
# Usage:
#   set(LN_DEPENDENCIES_ROOT_DIR "${PROJECT_SOURCE_DIR}/External/LuminoDependencies/")
#   include(External/LuminoDependencies/LuminoDependencies.cmake)
#   ...
#   target_link_libraries(<Project> ${LN_DEPENDENCIES_LIBRARIES})

include(${LN_DEPENDENCIES_ROOT_DIR}LuminoCommon.cmake)

#------------------------------------------------------------------------------
# Create include path, library path
#------------------------------------------------------------------------------
set(LN_DEPENDENCIES_INCLUDES "")

macro(ln_add_dependencis_library2 name libname)
	# http://stackoverflow.com/questions/22592624/force-find-library-to-search-again
	set(LN_DEPENDENCIES_LIBRARIES_DEBUG_LOCAL "${name}-NOTFOUND")
	set(LN_DEPENDENCIES_LIBRARIES_RELEASE_LOCAL "${name}-NOTFOUND")
	
	find_library(
		LN_DEPENDENCIES_LIBRARIES_DEBUG_LOCAL
		NAMES "${libname}d"
		PATHS "${LN_DEPENDENCIES_ROOT_DIR}${name}/${LN_LIB_OUTPUT_LOCAL_DIR}"
	)
	find_library(
		LN_DEPENDENCIES_LIBRARIES_RELEASE_LOCAL
		NAMES "${libname}"
		PATHS "${LN_DEPENDENCIES_ROOT_DIR}${name}/${LN_LIB_OUTPUT_LOCAL_DIR}"
	)
	
	list(APPEND LN_DEPENDENCIES_INCLUDES "${LN_DEPENDENCIES_ROOT_DIR}${name}/include")
	list(APPEND LN_DEPENDENCIES_LIBRARIES_DEBUG debug ${LN_DEPENDENCIES_LIBRARIES_DEBUG_LOCAL})
	list(APPEND LN_DEPENDENCIES_LIBRARIES_RELEASE optimized ${LN_DEPENDENCIES_LIBRARIES_RELEASE_LOCAL})
endmacro()

macro(ln_add_dependencis_library name)
	ln_add_dependencis_library2(${name} ${name})
endmacro()

ln_add_dependencis_library(zlib)
ln_add_dependencis_library(libpng)
ln_add_dependencis_library(libogg)
ln_add_dependencis_library(libvorbis)
ln_add_dependencis_library(bullet)
ln_add_dependencis_library(freetype)
ln_add_dependencis_library(giflib)
ln_add_dependencis_library2(effekseer Effekseer)
ln_add_dependencis_library2(effekseer_renderer_dx9 EffekseerRendererDX9)
ln_add_dependencis_library2(effekseer_renderer_gl EffekseerRendererGL)
ln_add_dependencis_library2(effekseer_sound_xaudio2 EffekseerSoundXAudio2)

set(LN_DEPENDENCIES_LIBRARIES
	${LN_DEPENDENCIES_LIBRARIES_DEBUG}
	${LN_DEPENDENCIES_LIBRARIES_RELEASE}
)

