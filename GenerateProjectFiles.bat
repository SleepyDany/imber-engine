@echo off

setlocal enabledelayedexpansion

echo --- Generate ImberEngine project files -----------------------------------

:: --clean : delete Build/ and regenerate whole project

for %%i in (%*) do (
    if "%%i"=="--clean" (
        echo -- Clean generation: On
        rmdir "./Build/" /s /q
    )
)

echo.
cmake -G "Visual Studio 17 2022" -B Build/ -A x64

echo.
echo --- Generate ImberEngine project files done ------------------------------

pause