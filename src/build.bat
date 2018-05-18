@echo off

set CommonCompilerFlags= -fp:fast -fp:except- -Gm- -MD -GR- -Zo -Oi -W4 -wd4251 -wd4201 -wd4100 -wd4189 -wd4505 -wd4127 -FC -Zi -O2

mkdir ..\build
pushd ..\build
REM cl %CommonCompilerFlags% -Zi /EHsc /FeCore /DCORE_EXPORT /D_CRT_SECURE_NO_WARNINGS /LD ..\src\core\core.cpp user32.lib gdi32.lib opengl32.lib
REM cl %CommonCompilerFlags% -Zi /EHsc ..\src\test.cpp user32.lib gdi32.lib opengl32.lib Core.lib winmm.lib

cl %CommonCompilerFlags% -Zi /WX /EHsc /FeCore /DCORE_EXPORT /D_CRT_SECURE_NO_WARNINGS /LD ..\src\core\core.cpp user32.lib gdi32.lib opengl32.lib winmm.lib
cl %CommonCompilerFlags% -Zi /WX /EHsc ..\src\engine\launcher.cpp user32.lib gdi32.lib opengl32.lib Core.lib winmm.lib

popd
