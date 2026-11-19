@echo off
chcp 65001 >nul
echo Running Automated DSA & OOP Simulation...
if exist "bin\civicsentinel\Main.class" (
    java -cp bin civicsentinel.Main --demo
) else (
    call build.bat
    java -cp bin civicsentinel.Main --demo
)
pause
