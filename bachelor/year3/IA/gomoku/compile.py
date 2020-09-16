#!/usr/bin/python3

import os
os.system("mkdir build")
os.system("cd build && cmake.exe . .. -G \"Visual Studio 15 2017 Win64\" && "
          "cmake.exe --build . --target "
          "pbrain-LILLE-hoffman.benoit --config release")