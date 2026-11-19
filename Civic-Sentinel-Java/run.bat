@echo off
chcp 65001 >nul
echo Starting CIVIC-SENTINEL: Project Udaan (Interactive Dashboard)...

where java >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [!] 'java' is not in PATH. Please install Java JRE/JDK or add to PATH.
    pause
    exit /b 1
)

if exist "bin\civicsentinel\Main.class" (
    java -cp bin civicsentinel.Main %*
) else if exist "udaan_engine.jar" (
    java -jar udaan_engine.jar %*
) else (
    echo [!] Project has not been built yet. Running build.bat first...
    call build.bat
    if exist "bin\civicsentinel\Main.class" (
        java -cp bin civicsentinel.Main %*
    )
)
