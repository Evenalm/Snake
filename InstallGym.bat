setlocal enableextensions
setlocal EnableDelayedExpansion

::Admin set current working directory
cd /d "%~dp0"

:: Find default PythonFolder
set count=1
for /F "tokens=* USEBACKQ" %%F in (`where python`) do (
  set var!count!=%%F
  set /a count=!count!+1
)

:: Copy SnakePort to global Python folder
:: robocopy %CD%\gym-snake "%var1:~0,-11%" SnakePort.pyd

:: Install gym
call cd gym-snake
call python -m pip install --user -e .
call cd ..

endlocal