@echo off
setlocal

set "BUILD_DIR=build"

if not exist "%BUILD_DIR%" (
    echo Creating build directory...
    mkdir "%BUILD_DIR%"
)

echo Configuring project with MinGW...
cd "%BUILD_DIR%"
cmake -G "MinGW Makefiles" ..

if %ERRORLEVEL% neq 0 (
    echo [ERROR] CMake configuration failed.
    goto :end
)

echo Building project...
cmake --build .

if %ERRORLEVEL% neq 0 (
    echo [ERROR] Build failed.
    goto :end
)

echo [SUCCESS] Build completed successfully.
echo Output: %BUILD_DIR%\libShaderInjector.dll

:end
cd ..
pause
endlocal
