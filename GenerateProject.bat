@echo off

echo --- Generate ImberEngine project files -----------------------------------
call "Engine/ThirdParty/premake/premake5.exe" vs2022
echo --- Generate ImberEngine project files done ------------------------------

pause