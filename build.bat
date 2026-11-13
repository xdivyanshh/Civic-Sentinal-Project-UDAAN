@echo off
echo ========================================================================
echo   Compiling CIVIC-SENTINEL Economic Engine (Project Udaan)
echo ========================================================================

set GXX="C:\Program Files (x86)\CodeBlocks\MinGW\bin\g++.exe"
if not exist %GXX% set GXX=g++

%GXX% -std=c++17 -Wall -Wextra -O2 -I"include" "src/main.cpp" -o "economic_engine.exe"

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [BUILD SUCCESSFUL] Created economic_engine.exe
    echo Running simulation...
    echo ========================================================================
    economic_engine.exe
) else (
    echo.
    echo [BUILD FAILED] Please check errors above.
)
pause
