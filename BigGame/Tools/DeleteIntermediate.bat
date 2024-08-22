setlocal

set DIRECTORY=%~dp0

@echo off
echo Deleting intermediate

if exist "%DIRECTORY%..\Intermediate" (
    echo Removing "%DIRECTORY%..\Intermediate"
    rmdir /Q /S "%DIRECTORY%..\Intermediate"
)

for /d /r %DIRECTORY%..\Plugins %%d in (Intermediate) do (
    if exist "%%d" (
         echo Removing "%%d"
         rmdir /Q /S "%%d"
    )
)

exit /b 0
