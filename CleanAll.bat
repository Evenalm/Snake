::Remove all object files leaving only log files
setlocal enableextensions
setlocal EnableDelayedExpansion

::Admin set current working directory
cd /d "%~dp0"

:: Set VS development evenviroment directory 
set "VSDEVDIR=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\"

:: Clean all solutions
call "%VSDEVDIR%devenv.exe" /Clean Debug %CD%\Snake.sln
call "%VSDEVDIR%devenv.exe" /Clean Release %CD%\SnakeUnitTest.sln
call "%VSDEVDIR%devenv.exe" /Clean Release %CD%\PythonSnake.sln

:: Remove all target solution folders
call RMDIR /S /Q "%CD%\PythonProject\__pycache__"
call RMDIR /S /Q "%CD%\Debug"
call RMDIR /S /Q "%CD%\executable"
call RMDIR /S /Q "%CD%\Release"