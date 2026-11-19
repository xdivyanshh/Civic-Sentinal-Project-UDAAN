@echo off
chcp 65001 >nul
echo Running Inter-Portal Live Communication Bridge Demo...
if exist "bin\civicsentinel\Main.class" (
    java -cp bin civicsentinel.Main --bridge
) else (
    call build.bat
    java -cp bin civicsentinel.Main --bridge
)
pause
