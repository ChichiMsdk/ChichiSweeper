@echo off

rmdir /s /q build
del demineur.exe
mkdir build
pushd build
::/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup
::cl /Fe"../demineur.exe" /O2 gdi32.lib kernel32.lib msvcrt.lib opengl32.lib raylib.lib shell32.lib ..\src\*.c user32.lib winmm.lib -I..\include -IC:\Lib\raylib\msvc\include /link /libpath:C:\Lib\raylib\msvc\lib /NODEFAULTLIB:libcmt
cl /DWIN32 /MD /Fe"../demineur.exe" /fsanitize=address /Zi /Od gdi32.lib kernel32.lib msvcrt.lib opengl32.lib raylib.lib shell32.lib user32.lib winmm.lib ..\src\*.c -I..\include -IC:\Lib\raylib\msvc\include /link /libpath:C:\Lib\raylib\msvc\lib /NODEFAULTLIB:libcmt
::cl /Fe"../demineur.exe" /Zi /Od gdi32.lib kernel32.lib msvcrt.lib opengl32.lib raylib.lib shell32.lib user32.lib winmm.lib ..\src\*.c -I..\include -IC:\Lib\raylib\msvc\include /link /libpath:C:\Lib\raylib\msvc\lib /NODEFAULTLIB:libcmt
popd
