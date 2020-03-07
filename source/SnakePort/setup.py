import os, sys

from distutils.core import setup, Extension
from distutils import sysconfig

cpp_args = ['-std=c++11', '-stdlib=libc++', '-mmacosx-version-min=10.7']

sfc_module = Extension(
    'SnakePort', 
    sources = ['module.cpp'],
    libraries = ['Snake.lib'],
    library_dirs = ['/../Release'],
    include_dirs = ['pybind11/include, /../../Snake/Snake'],
    language = 'c++',
    extra_compile_args = cpp_args,
    )

setup(
    name = 'SnakePort',
    version = '1.0',
    description = 'Python package Snake C++(PyBind11)',
    ext_modules = [sfc_module],
)