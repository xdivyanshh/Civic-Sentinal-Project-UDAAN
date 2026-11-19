@echo off
chcp 65001 >nul
echo Running Economic & Welfare Engine (0/1 Knapsack & Fenwick Tree)...
if exist "bin\civicsentinel\Main.class" (
    java -cp bin civicsentinel.Main --economic
) else (
    call build.bat
    java -cp bin civicsentinel.Main --economic
)
pause
