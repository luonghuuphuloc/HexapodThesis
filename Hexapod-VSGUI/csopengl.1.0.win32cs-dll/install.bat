@ if /I  "%1" == "-r"         goto uninstall
@ if /I  "%1" == "-remove"    goto uninstall
@ if /I  "%1" == "-u"         goto uninstall
@ if /I  "%1" == "-uninstall" goto uninstall
@ if NOT "%1" == ""           goto usage
@ goto install

:install
@
@ rem -- csgl-opengl.dll must be compiled with STRONG defined to be installed
@ rem -- install cgsl-opengl.dll assembly
@ rem -- 	- in Global Assembly Cache (gacutil) for runtime
@ rem -- 	- in PATH to find it at compile time (%SystemRoot%\System32)
@
gacutil.exe /i csgl-opengl.dll
copy csgl-opengl.dll %SystemRoot%\System32
copy csgl-opengl.xml %SystemRoot%\System32
@
@ rem -- install cslg-opengl-native.dll
@ rem --	- in PATH, to find it at runtime
@
copy csgl-opengl-native.dll %SystemRoot%\System32
@goto end

:uninstall
gacutil.exe /u csgl-opengl
del %SystemRoot%\System32\csgl-opengl.dll
del %SystemRoot%\System32\csgl-opengl.xml
del  %SystemRoot%\System32\csgl-opengl-native.dll
@goto end

:usage
@ echo " usage :
@ echo " - install     => install csgl
@ echo " - install -u  => uninstall csgl
@goto end

:end