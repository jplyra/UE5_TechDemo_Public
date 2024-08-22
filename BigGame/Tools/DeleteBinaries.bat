setlocal

set DIRECTORY=%~dp0

@echo off
echo Deleting binaries

if exist "%DIRECTORY%..\Binaries\Win64" (
    echo Removing "%DIRECTORY%..\Binaries\Win64"
    rmdir /Q /S "%DIRECTORY%..\Binaries\Win64"
)

if exist "%DIRECTORY%..\Binaries\Linux" (
    echo Removing "%DIRECTORY%..\Binaries\Linux"
    rmdir /Q /S "%DIRECTORY%..\Binaries\Linux"
)

for /d /r %DIRECTORY%..\Plugins %%d in (Binaries) do (
    if exist "%%d\Win64" (
         echo Removing "%%d\Win64"
         rmdir /Q /S "%%d\Win64"
    )
    if exist "%%d\Linux" (
         echo Removing "%%d\Linux"
         rmdir /Q /S "%%d\Linux"
    )
)

exit /b 0
