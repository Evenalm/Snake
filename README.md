# Snake
Playing Snake with C++ and a Python port for UI.

<img src="images/RunningApplication.PNG" width="600">

## Prerequisites
* [pybind11](https://pybind11.readthedocs.io/en/stable/) ([github](https://github.com/pybind/pybind11))
* [arcade](https://arcade.academy/#) (pip install)
* [googletest](https://github.com/google/googletest) (Integrated in VS)
* [Visual Studio 2019(VS)](https://visualstudio.microsoft.com/) ([Download page](https://visualstudio.microsoft.com/vs/))
* VS needs the package: Python native development tools, get it from VS installer.
* [pyinstaller](https://www.pyinstaller.org/) (pip install)
* [Python 32bit interpeter](https://www.python.org/downloads/)

Python environments and packages can be installed directly in VS. Very helpfull guide for combining C++ and Python in VS: [Create a C++ extension for Python](https://docs.microsoft.com/en-us/visualstudio/python/working-with-c-cpp-python-in-visual-studio?view=vs-2019)

## Installing
1. Download from personal Github [Evenalm](https://github.com/Evenalm/Snake/)

1. Set project configuration:
	1. Snake.sln -> set to Debug x86
	1. SnakeUnitTest.sln -> set to Release x86
	1. PythonSnake.sln -> set to Release x86

1. Set Python envoronmet variables:
	1. In System Properties -> advanced -> Environment Variables... -> Path -> Edit -> Add a varable to
		1. Python folder
		1. Python\include folder
		1. Python\libs folder
		1. Python\Scripts folder
		
### Running scripts
The devenv and python install directory is set by VS, if VS was installed in default directory and python w/ packages was installed using it then the path variables do not change. If a costum installation was used then these variables have to be set.

1. Change Python 32bit interpeter for PythonSnake solution:
   1. in PythonSnake.sln -> PythonGui -> Python Environments -> Right click -> Add environments...
   1. in PythonSnake.sln -> SnakePort -> properties -> configuration properties -> C/C++ 
      -> General -> Additional Include Directories: Change location of python include folder path to yours
   1. in PythonSnake.sln -> SnakePort -> properties -> configuration properties -> Linker 
      -> General -> Additional Library Directories: Change location of python libs folder path to yours
      
1. Change development directory:
   1. Find the folder with your devenv(follow VS shortcut or search for devenv).
   1. In BuildAll.bat replace folder path VSDEVDIR with your path
   1. In CleanAll.bat replace folder path VSDEVDIR with your path

## Run and build
Run batch script BuildAll.bat

1. Main game: Run batch script PlayGame.bat or go to executables and start SnakeUI
2. Unit tests: Executable found under Release folder
3. Debug with console scripts are in DebugConsoleScripts folder

## Authors

* **Even Elshaug Almås** - *Author* - [Evenalm](https://github.com/Evenalm)
