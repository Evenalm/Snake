::Remove all object files leaving only log files
setlocal enableextensions
setlocal EnableDelayedExpansion

::Admin set current working directory
cd /d "%~dp0"

:: Remove all target solution folders
call RMDIR /S /Q "%CD%\SnakeUnitTest\Release"
call RMDIR /S /Q "%CD%\SnakePort\Release"
call RMDIR /S /Q "%CD%\Snake\Debug"
call RMDIR /S /Q "%CD%\Snake\Release"