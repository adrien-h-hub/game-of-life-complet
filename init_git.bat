@echo off
REM Git Initialization Script for Conway's Game of Life v1.1.0
REM Batch file wrapper for PowerShell script

echo ========================================
echo   Git Repository Initialization
echo ========================================
echo.
echo This will run the PowerShell initialization script.
echo.

REM Check if PowerShell is available
where powershell >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: PowerShell not found!
    echo Please ensure PowerShell is installed.
    pause
    exit /b 1
)

REM Run the PowerShell script
echo Running PowerShell script...
echo.
powershell.exe -ExecutionPolicy Bypass -File "%~dp0init_git.ps1"

pause
