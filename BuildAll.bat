setlocal enableextensions
setlocal EnableDelayedExpansion

::Admin set current working directory
cd /d "%~dp0"

:: Set VS development evenviroment directory 
set "VSDEVDIR=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\"

:: Compile all solutions
call "%VSDEVDIR%devenv.exe" /build Debug /projectconfig x86 %CD%\Snake.sln
call "%VSDEVDIR%devenv.exe" /build Release /projectconfig x86 %CD%\SnakeUnitTest.sln
call "%VSDEVDIR%devenv.exe" /build Release /projectconfig x86 %CD%\PythonSnake.sln

:: Copy python files (Instead of pyinstaller tree structure)
robocopy %CD%\PythonProject %CD%\Release /E

:: cd to folder to not get byproducts here
call cd Release
call pyinstaller --noconfirm -w --onefile SnakeUI.py
call cd ..

:: Copy solution
robocopy %CD%\Release\dist %CD%\dist /E

::Rename
ren dist executable

:: Copy SnakePort
robocopy %CD%\Release %CD%\gym-snake SnakePort.pyd