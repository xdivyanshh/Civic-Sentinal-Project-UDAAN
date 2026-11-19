@echo off
setlocal enabledelayedexpansion
chcp 65001 >nul
echo ========================================================================
echo   Compiling PROJECT UDAAN: Master Unified Engine (Java Version)
echo   Course: Data Structures / Java Lab (15B17CI371)
echo   Jaypee Institute of Information Technology (JIIT, Noida)
echo ========================================================================

:: Check for javac in PATH
where javac >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [!] 'javac' is not in PATH. Checking common Java installation directories...
    set JAVAC_FOUND=
    for %%P in (
        "C:\Program Files\Java\jdk*\bin\javac.exe"
        "C:\Program Files\Eclipse Adoptium\jdk*\bin\javac.exe"
        "C:\Program Files\Amazon Corretto\jdk*\bin\javac.exe"
        "C:\Program Files\Zulu\zulu*\bin\javac.exe"
        "C:\Program Files\Microsoft\jdk*\bin\javac.exe"
        "C:\Program Files (x86)\Java\jdk*\bin\javac.exe"
    ) do (
        if exist %%P (
            set JAVAC_CMD=%%P
            set JAVAC_FOUND=1
            goto :found_javac
        )
    )
    echo.
    echo [ERROR] Java Development Kit (JDK) compiler 'javac' was not found!
    echo Please install a JDK (version 8 or higher) or add javac to your PATH.
    pause
    exit /b 1
) else (
    set JAVAC_CMD=javac
)

:found_javac
echo [*] Using Java Compiler: %JAVAC_CMD%

:: Ensure bin directory exists
if not exist "bin" mkdir "bin"

echo [*] Compiling all Java source files into bin/...
%JAVAC_CMD% -encoding UTF-8 -d bin src\civicsentinel\*.java

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ========================================================================
    echo [BUILD SUCCESSFUL] All 28 Java source classes compiled cleanly into bin/
    echo ========================================================================
    echo.
    echo Packaging executable JAR 'udaan_engine.jar'...
    jar cfe udaan_engine.jar civicsentinel.Main -C bin civicsentinel
    echo [*] Generated standalone 'udaan_engine.jar'
    echo.
    echo Running unified inter-portal demonstration...
    echo ========================================================================
    java -cp bin civicsentinel.Main --bridge
) else (
    echo.
    echo [BUILD FAILED] Compilation errors occurred. Check messages above.
)

pause
