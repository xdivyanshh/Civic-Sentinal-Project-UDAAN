@echo off
chcp 65001 >nul
echo Starting Civic-Sentinel Ground-Level Field & Admin Portal...
if exist "bin\civicsentinel\AdminPortalMain.class" (
    java -cp bin civicsentinel.AdminPortalMain %*
) else (
    call build.bat
    java -cp bin civicsentinel.AdminPortalMain %*
)
