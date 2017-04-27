import os
import subprocess
from subprocess import Popen

targets = [
	# DirName, 					VSTarget,			Unicode,	StaticRuntime,	X64,	Platform
	["build_msvc120x86_MT",		"Visual Studio 12",	"OFF",		"ON",			"OFF",	"Win32"],
	["build_msvc120x86u_MT",	"Visual Studio 12",	"ON",		"ON",			"OFF",	"Win32"],
	["build_msvc120x86_MD",		"Visual Studio 12",	"OFF",		"OFF",			"OFF",	"Win32"],
	["build_msvc120x86u_MD",	"Visual Studio 12",	"ON",		"OFF",			"OFF",	"Win32"],
	["build_msvc140x86_MT",		"Visual Studio 14",	"OFF",		"ON",			"OFF",	"Win32"],
	["build_msvc140x86u_MT",	"Visual Studio 14",	"ON",		"ON",			"OFF",	"Win32"],
	["build_msvc140x86_MD",		"Visual Studio 14",	"OFF",		"OFF",			"OFF",	"Win32"],
	["build_msvc150x86u_MD",	"Visual Studio 14",	"ON",		"OFF",			"OFF",	"Win32"],
	["build_msvc150x86_MT",		"Visual Studio 15",	"OFF",		"ON",			"OFF",	"Win32"],
	["build_msvc150x86u_MT",	"Visual Studio 15",	"ON",		"ON",			"OFF",	"Win32"],
	["build_msvc150x86_MD",		"Visual Studio 15",	"OFF",		"OFF",			"OFF",	"Win32"],
	["build_msvc150x86u_MD",	"Visual Studio 15",	"ON",		"OFF",			"OFF",	"Win32"]
	]

if not os.path.exists("build"):
	os.mkdir("build")
os.chdir("build")

for t in targets:
	if not os.path.exists(t[0]):
		os.mkdir(t[0])
	os.chdir(t[0])

	args = "cmake -G\"{0}\" -DLN_USE_UNICODE_CHAR_SET={1} -DLN_MSVC_STATIC_RUNTIME={2} -DLN_BUILD_X64={3} ../..".format(t[1], t[2], t[3], t[4])
	
	proc = Popen(args)
	proc.communicate()
	#print stdout_data
	#print stderr_data
	if proc.returncode == 0:
		proc = Popen("msbuild LuminoDependencies.sln /t:Build /p:Configuration=\"Debug\" /p:Platform=\"{0}\" /m".format(t[5]));
		proc.communicate()
		proc = Popen("msbuild LuminoDependencies.sln /t:Build /p:Configuration=\"Release\" /p:Platform=\"{0}\" /m".format(t[5]));
		proc.communicate()


	os.chdir("../")
