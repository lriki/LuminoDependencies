cmake_minimum_required (VERSION 3.0.0)
project (LuminoDependencies)

include(LuminoDependencies/LuminoCommon.cmake)

#------------------------------------------------------------------------------
macro(ln_add_common_property projectName)
	set(LN_LIB_OUTPUT_DIR "${LN_LIB_OUTPUT_ROOT_DIR}/${projectName}/${LN_LIB_OUTPUT_LOCAL_DIR}")
	set_target_properties(${projectName} PROPERTIES OUTPUT_NAME "${projectName}${LN_STATIC_LIB_POSTFIX}")
	set_target_properties(${projectName} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${LN_LIB_OUTPUT_DIR}")
	set_target_properties(${projectName} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${LN_LIB_OUTPUT_DIR}")
	set_target_properties(${projectName} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${LN_LIB_OUTPUT_DIR}")
	set_target_properties(${projectName} PROPERTIES PREFIX "")
endmacro()


#------------------------------------------------------------------------------
# External
#------------------------------------------------------------------------------
add_subdirectory(External/zlib-1.2.7)
ln_add_common_property(zlib)

add_subdirectory(External/bullet-2.82)
ln_add_common_property(bullet)

add_subdirectory(External/freetype-2.6)
ln_add_common_property(freetype)

add_subdirectory(External/giflib-5.1.4)
ln_add_common_property(giflib)

add_subdirectory(External/libogg-1.3.2)
ln_add_common_property(libogg)

add_subdirectory(External/libpng-1.6.12)
ln_add_common_property(libpng)

add_subdirectory(External/libvorbis-1.3.5)
ln_add_common_property(libvorbis)

#---------------------------------------
# Effekseer
if (LN_MSVC_STATIC_RUNTIME)
	set(USE_MSVC_RUNTIME_LIBRARY_DLL OFF)
else()
	set(USE_MSVC_RUNTIME_LIBRARY_DLL ON)
endif()
set(USE_INTERNAL_LOADER ON)
set(USE_GLEW_STATIC OFF)
set(USE_GLEW_DLL ON)
set(USE_OPENAL OFF)
set(USE_OPENGLES2 OFF)
set(USE_OPENGLES3 OFF)
set(USE_OPENGL3 OFF)
#mark_as_advanced(USE_OPENGLES3)

#if (LN_USE_EXTERNAL_Effekseer)
	add_subdirectory(External/EffekseerRuntime101/src)
	#link_libraries(effekseer)
	#link_libraries(effekseer_renderer_gl)
	#if (MSVC)
	#	link_libraries(effekseer_renderer_dx9)
	#	link_libraries(effekseer_sound_xaudio2)
	#endif()
#endif()

set(LN_LIB_OUTPUT_DIR "${LN_LIB_OUTPUT_ROOT_DIR}/effekseer/${LN_LIB_OUTPUT_LOCAL_DIR}")
ln_add_common_property(effekseer)
ln_add_common_property(effekseer_renderer_gl)

if (MSVC)
	ln_add_common_property(effekseer_renderer_dx9)
	ln_add_common_property(effekseer_sound_xaudio2)
endif()

# copy include files
file(COPY "External/EffekseerRuntime101/src/include" DESTINATION "${LN_LIB_OUTPUT_ROOT_DIR}/effekseer")
