@echo off
echo ========================================================================
echo   Compiling PROJECT UDAAN: Master Unified Engine
echo ========================================================================

set GXX="C:\MinGW\bin\g++.exe"
if not exist %GXX% set GXX=g++

%GXX% -std=c++14 -O2 -static -static-libgcc -static-libstdc++ -I"include" "src/main.cpp" -o "udaan_engine.exe"

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [BUILD SUCCESSFUL] Created standalone udaan_engine.exe
    echo Running unified inter-portal demonstration...
    echo ========================================================================
    udaan_engine.exe --bridge
) else (
    echo.
    echo [BUILD FAILED] Please check compiler errors above.
)
pause
