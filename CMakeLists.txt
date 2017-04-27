cmake_minimum_required (VERSION 3.0.0)
project (LuminoDependencies)

include(LuminoDependencies/LuminoCommon.cmake)

#------------------------------------------------------------------------------
# External
#------------------------------------------------------------------------------
add_subdirectory(External/zlib-1.2.7)
add_subdirectory(External/bullet-2.82)
add_subdirectory(External/freetype-2.6)
add_subdirectory(External/giflib-5.1.4)
add_subdirectory(External/libogg-1.3.2)
add_subdirectory(External/libpng-1.6.12)
add_subdirectory(External/libvorbis-1.3.5)

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
set_target_properties(effekseer PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${LN_LIB_OUTPUT_DIR}")
set_target_properties(effekseer PROPERTIES PREFIX "")
set_target_properties(effekseer_renderer_gl PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${LN_LIB_OUTPUT_DIR}")
set_target_properties(effekseer_renderer_gl PROPERTIES PREFIX "")

if (MSVC)
	set_target_properties(effekseer_renderer_dx9 PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${LN_LIB_OUTPUT_DIR}")
	set_target_properties(effekseer_sound_xaudio2 PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${LN_LIB_OUTPUT_DIR}")
endif()

# copy include files
file(COPY "External/EffekseerRuntime101/src/include" DESTINATION "${LN_LIB_OUTPUT_ROOT_DIR}/effekseer")
