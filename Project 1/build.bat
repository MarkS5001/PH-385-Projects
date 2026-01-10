@echo off
echo Compiling...
cl Magnus.cpp PingPong.cpp /EHsc /Fe:Magnus.exe

if %errorlevel% neq 0 (
    echo Compilation failed!
    exit /b %errorlevel%
)

echo Cleaning up intermediate files...
del *.obj

echo Done! Run with ./Magnus.exe

::Compile with this:
::cd "C:/Users/markb/OneDrive/College/BYUI/26 8 Winter/PH 385/PH-385-Projects/Project 1/"
::.\build.bat