# Snake
Playing Snake with C++ with Python port for UI.

## Prerequisites

To run the attached executables you have to be on Windows 10.
Compiling / installing just the game reqieres external libraries, [pybind 11](https://pybind11.readthedocs.io/en/stable/) for porting and [(python)arcade](https://arcade.academy/#) for visuals / GUI.
This uses a Python 32 bit interpeter, project used Python 3.7.5. (32 bit) 

## Installing

Download from personal Github [Evenalm](https://github.com/Evenalm/Snake/)
To compile on own machine you have to make projects / compile source sepperatly.
Personally used Visual Studio 2019 projects with 
```
pyinstaller --noconfirm -w --onefile SnakeUI.py
```

## Running the programs (Only windows 10)
Run application snake.exe to start Python version. 

A console window can also be used to play, start any of the three batch scripts in the console subfolder. 
Already having a cmd window open helps, as this will not start the python GUI.

Under the folder Benchmark there is an executeble for basic unit tests and for benchmarking various aspects of the application. 

Should look like this when done correctly:
<img src="images/RunningApplication.PNG" width="500">

## Built With

* [pybind11](https://pybind11.readthedocs.io/en/stable/)
* [arcade](https://arcade.academy/#)
* [googletest](https://github.com/google/googletest)
* [Visual Studio](https://visualstudio.microsoft.com/)
* [pyinstaller](https://www.pyinstaller.org/)


## Authors

* **Even Elshaug Almås** - *Initial work* - [Evenalm](https://github.com/Evenalm)
