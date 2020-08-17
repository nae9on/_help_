
# Build
```
g++ -IC:\Users\ahkad\opencv\gnu_build\install\include main.cpp -LC:\Users\ahkad\opencv\gnu_build\install\x64\mingw\bin -lopencv_world420 -o tutorial
```

```
tutorial belgium.jpg
```

# Using OpenCV with Eclipse (plugin CDT)

Steps:
1. Start Eclipse and create a new ``C++ Managed Build`` project
2. Select ``Empty Project``, ``MinGW GCC`` toolchain and select location as project dir (where main.cpp exists)
3. In Project->Settings->GCC C++ Compiler->Includes add Include path ``C:\Users\ahkad\opencv\gnu_build\install\include``
4. In Project->Settings->MinGW C++ Linker->Libraries add Library search path ``C:\Users\ahkad\opencv\gnu_build\install\x64\mingw\bin`` and Library name to link to ``opencv_world420``
5. Build project
6. In arguments add belgium.jpg and run



# Build using CMake
```
cd build
cmake ..
make
tutorial ..\belgium.jpg
```

Note: the path environement variable should point to ``%OPENCV_DIR%\bin`` to find ``libopencv_world420.dll``. Alternative copy the dll next to the executable.
