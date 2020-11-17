# final-project-max-tree

This branch is to store the process of how to use CoolProps library for thermodynamic properties. The instructions were made by Dr. McBride.

1.Close QtCreator
2.Go to Python.org and download and install python 3.9.0 for windows.  It will be installed in something like c:\users\<username>\AppData\Local\Programs\Python\Python39\python.exe
3.Delete any CoolProp directory in your project source directory.
4.Clone the CoolProp repo https://github.com/CoolProp/CoolProp.git into your project directory. 
5.In the GitBash window in the new CoolProp directory type "git submodule init"  and then "git submodule update"
6.Open QtCreator
7.Open the project CMakeList.txt file.
8.Add the CoolProp lines below to the CMakeList.txt file:
9.Turn on the "COOLPROP_STATIC_LIBRARY" settings in the CMake project settings.  Make sure to hit enter after you change it.
10.Set the Python path in the CMake project setting to the python executable.  See the installation path above for where to look.  Make sure to hit enter after you set the path and then hit the apply configuration button.
11.Build your project.  This will also build CoolProps.
12.Add the CoolProps code that you want to your project.  Make sure to include the CoolProp.h file.
13.Build again.

CMakeList.txt file additions:

set(COOLPROP_STATIC_LIBRARY true)
add_subdirectory ("${CMAKE_SOURCE_DIR}/CoolProp" CoolProp)

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::Gui
    CoolProp
)
