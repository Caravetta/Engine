
@echo off

set CommonCompilerFlags= -fp:fast -fp:except- -Gm- -MD -GR- -Zo -Oi -W4 -wd4251 -wd4201 -wd4100 -wd4189 -wd4505 -wd4127 -FC -Ox -Ot
set DebugCompilerFlags= -fp:fast -fp:except- -Gm- -MD -GR- -Zo -Oi -W4 -wd4251 -wd4201 -wd4100 -wd4189 -wd4505 -wd4127 -FC -Zi

mkdir ..\build
mkdir ..\build\debug
mkdir ..\build\release

REM cl %CommonCompilerFlags% -Zi /EHsc /FeCore /DDEBUG_BUILD /DCORE_EXPORT /D_CRT_SECURE_NO_WARNINGS /LD ..\src\core\core.cpp user32.lib gdi32.lib opengl32.lib
REM cl %CommonCompilerFlags% -Zi /EHsc ..\src\test.cpp user32.lib gdi32.lib opengl32.lib Core.lib winmm.lib

echo.
echo ____________RELEASE___________________
echo.

pushd ..\build\release

    cl %CommonCompilerFlags% /I ..\..\libs\free_type\include\ /I ..\..\libs\Engine\include\ -Zi /EHsc /DPLATFORM_WINDOWS ..\..\src\sandbox.cpp user32.lib gdi32.lib opengl32.lib Core.lib winmm.lib
)

popd

echo.
echo _____________DEBUG____________________
echo.

pushd ..\build\debug

    cl %DebugCompilerFlags% /I ..\..\libs\free_type\include\ /I ..\..\libs\Engine\include\ -Zi /EHsc /DPLATFORM_WINDOWS /DDEBUG_BUILD ..\..\src\sandbox.cpp user32.lib gdi32.lib opengl32.lib Core.lib winmm.lib

popd
