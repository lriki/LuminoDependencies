cmake_minimum_required (VERSION 3.0.0)
project (LuminoDependencies)

#------------------------------------------------------------------------------
# Options
#------------------------------------------------------------------------------

# Unicode char set.
option(LN_USE_UNICODE_CHAR_SET "Use unicode char set." ON)

# MSVC Runtime library.
option(LN_MSVC_STATIC_RUNTIME "static runtime (/MT, /MTd) or DLL runtime (/MD, /MDd) or to link either." ON)

# Architecture.
option(LN_BUILD_X64 "Architecture." OFF)

#------------------------------------------------------------------------------
# Apply options
#------------------------------------------------------------------------------
set(LN_STATIC_LIB_POSTFIX "_static")
set(LN_LIB_OUTPUT_ROOT_DIR "${CMAKE_SOURCE_DIR}/Dependencies/")
set(LN_LIB_OUTPUT_LOCAL_DIR "lib/")

if (WIN32)
	# MSVC version
	if (MSVC_VERSION EQUAL 1400)
		set(LN_TARGET_ENV "MSVC80")
	elseif (MSVC_VERSION EQUAL 1500)
		set(LN_TARGET_ENV "MSVC90")
	elseif (MSVC_VERSION EQUAL 1600)
		set(LN_TARGET_ENV "MSVC100")
	elseif (MSVC_VERSION EQUAL 1700)
		set(LN_TARGET_ENV "MSVC110")
	elseif (MSVC_VERSION EQUAL 1800)
		set(LN_TARGET_ENV "MSVC120")
	elseif (MSVC_VERSION EQUAL 1900)
		set(LN_TARGET_ENV "MSVC140")
	endif()
	set(LN_LIB_OUTPUT_LOCAL_DIR "${LN_LIB_OUTPUT_LOCAL_DIR}${LN_TARGET_ENV}")

	# Architecture.
	# http://stackoverflow.com/questions/5334095/cmake-multiarchitecture-compilation
	if (${CMAKE_EXE_LINKER_FLAGS} MATCHES "/machine:x64")	# /machine:x64
		set(LN_ARCH "x64")
	else()
		set(LN_ARCH "x86")
	endif()
	set(LN_LIB_OUTPUT_LOCAL_DIR "${LN_LIB_OUTPUT_LOCAL_DIR}_${LN_ARCH}")

	# Runtime library
	if (LN_MSVC_STATIC_RUNTIME)
		foreach (flag CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE)
			if (${flag} MATCHES "/MD")
				string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
			endif()
			if (${flag} MATCHES "/MDd")
				string(REGEX REPLACE "/MDd" "/MTd" ${flag} "${${flag}}")
			endif()
		endforeach()
	endif()
	if (LN_MSVC_STATIC_RUNTIME)
		set(LN_LIB_OUTPUT_LOCAL_DIR "${LN_LIB_OUTPUT_LOCAL_DIR}_MT/")
	else()
		set(LN_LIB_OUTPUT_LOCAL_DIR "${LN_LIB_OUTPUT_LOCAL_DIR}_MD/")
	endif()
endif()

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
set_target_properties(effekseer_renderer_gl PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${LN_LIB_OUTPUT_DIR}")

if (MSVC)
	set_target_properties(effekseer_renderer_dx9 PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${LN_LIB_OUTPUT_DIR}")
	set_target_properties(effekseer_sound_xaudio2 PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${LN_LIB_OUTPUT_DIR}")
endif()

# copy include files
file(COPY "External/EffekseerRuntime101/src/include" DESTINATION "${LN_LIB_OUTPUT_ROOT_DIR}/effekseer")

