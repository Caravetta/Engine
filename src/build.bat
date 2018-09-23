
@echo off

set CommonCompilerFlags= -fp:fast -fp:except- -Gm- -MD -GR- -Zo -Oi -W4 -wd4251 -wd4201 -wd4100 -wd4189 -wd4505 -wd4127 -FC -Zi -O2 -Ot
set DebugCompilerFlags= -fp:fast -fp:except- -Gm- -MD -GR- -Zo -Oi -W4 -wd4251 -wd4201 -wd4100 -wd4189 -wd4505 -wd4127 -FC -Zi

mkdir ..\build
mkdir ..\build\debug
mkdir ..\build\release

REM cl %CommonCompilerFlags% -Zi /EHsc /FeCore /DDEBUG_BUILD /DCORE_EXPORT /D_CRT_SECURE_NO_WARNINGS /LD ..\src\core\core.cpp user32.lib gdi32.lib opengl32.lib
REM cl %CommonCompilerFlags% -Zi /EHsc ..\src\test.cpp user32.lib gdi32.lib opengl32.lib Core.lib winmm.lib

IF "%1" == "core" (
    cl %CommonCompilerFlags% /I ..\src\libs\free_type\include\ -Zi /EHsc /FeCore /DDEBUG_BUILD /DCORE_EXPORT /D_CRT_SECURE_NO_WARNINGS /LD ..\src\core\core.cpp user32.lib gdi32.lib opengl32.lib winmm.lib ..\src\libs\free_type\freetype.lib /link /LIBPATH:..\src\libs\free_type\
) ELSE IF "%1" == "launcher" (
    cl %CommonCompilerFlags% /I ..\src\libs\free_type\include\ -Zi /DDEBUG_BUILD /EHsc ..\src\engine\launcher.cpp user32.lib gdi32.lib opengl32.lib Core.lib winmm.lib ..\src\libs\free_type\freetype.lib /link /LIBPATH:..\src\libs\free_type\
) ELSE IF "%1" == "debug" (
    cl %DebugCompilerFlags% /I ..\src\libs\free_type\include\ -Zi /EHsc /FeCore /DDEBUG_BUILD /DCORE_EXPORT /D_CRT_SECURE_NO_WARNINGS /LD ..\src\core\core.cpp user32.lib gdi32.lib opengl32.lib winmm.lib ..\src\libs\free_type\freetype.lib /link /LIBPATH:..\src\libs\free_type\
    cl %DebugCompilerFlags% /I ..\src\libs\free_type\include\ -Zi /EHsc /DDEBUG_BUILD ..\src\engine\launcher.cpp user32.lib gdi32.lib opengl32.lib Core.lib winmm.lib ..\src\libs\free_type\freetype.lib /link /LIBPATH:..\src\libs\free_type\
) ELSE (

echo.
echo ____________RELEASE___________________
echo.

pushd ..\build\release

copy ..\..\src\libs\free_type\freetype.dll .

    cl %CommonCompilerFlags% /I ..\..\src\libs\free_type\include\ -Zi /EHsc /FeCore /DCORE_EXPORT /D_CRT_SECURE_NO_WARNINGS /LD ..\..\src\core\core.cpp user32.lib gdi32.lib opengl32.lib winmm.lib ..\..\src\libs\free_type\freetype.lib /link /LIBPATH:..\..\src\libs\free_type\
    cl %CommonCompilerFlags% /I ..\..\src\libs\free_type\include\ -Zi /EHsc ..\..\src\engine\launcher.cpp user32.lib gdi32.lib opengl32.lib Core.lib winmm.lib ..\..\src\libs\free_type\freetype.lib /link /LIBPATH:..\..\src\libs\free_type\
)

popd

echo.
echo _____________DEBUG____________________
echo.

pushd ..\build\debug

copy ..\..\src\libs\free_type\freetype.dll .

    cl %DebugCompilerFlags% /I ..\..\src\libs\free_type\include\ -Zi /EHsc /FeCore /DDEBUG_BUILD /DCORE_EXPORT /D_CRT_SECURE_NO_WARNINGS /LD ..\..\src\core\core.cpp user32.lib gdi32.lib opengl32.lib winmm.lib ..\..\src\libs\free_type\freetype.lib /link /LIBPATH:..\..\src\libs\free_type\
    cl %DebugCompilerFlags% /I ..\..\src\libs\free_type\include\ -Zi /EHsc /DDEBUG_BUILD ..\..\src\engine\launcher.cpp user32.lib gdi32.lib opengl32.lib Core.lib winmm.lib ..\..\src\libs\free_type\freetype.lib /link /LIBPATH:..\..\src\libs\free_type\

popd
