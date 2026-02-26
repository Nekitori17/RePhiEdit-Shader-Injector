@echo off
setlocal EnableDelayedExpansion

set "BUILD_DIR=build"
set "BUILD_TYPE=Release"
set "GENERATOR=MSVC"
set "DO_CLEAN=0"

for %%a in (%*) do (
    if /I "%%a"=="mingw" (
        set "GENERATOR=MinGW"
    )
    if /I "%%a"=="msvc" (
        set "GENERATOR=MSVC"
    )
    if /I "%%a"=="debug" (
        set "BUILD_TYPE=Debug"
    )
    if /I "%%a"=="release" (
        set "BUILD_TYPE=Release"
    )
    if /I "%%a"=="clean" (
        set "DO_CLEAN=1"
    )
)

echo ==========================================
echo  BUILD SETTINGS
echo ==========================================
echo  Generator  : !GENERATOR!
echo  Config     : !BUILD_TYPE!
echo  Clean Build: !DO_CLEAN!
echo ==========================================

if "!DO_CLEAN!"=="1" (
  if exist "%BUILD_DIR%" (
    echo [INFO] Cleaning build directory...
    rmdir /s /q "%BUILD_DIR%"
  )
)

if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)

echo [INFO] Configuring project...

if "!GENERATOR!"=="MinGW" (
  cmake -S . -B "%BUILD_DIR%" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=!BUILD_TYPE!
) else (
  cmake -S . -B "%BUILD_DIR%" -A Win32
)

if %ERRORLEVEL% neq 0 (
  echo [ERROR] CMake configuration failed!
  goto :fail
)

echo [INFO] Building project (%BUILD_TYPE%)...

cmake --build "%BUILD_DIR%" --config !BUILD_TYPE!

if %ERRORLEVEL% neq 0 (
  echo [ERROR] Build failed!
  goto :fail
)

echo.
echo ==========================================
echo [SUCCESS] Build completed successfully!
echo Output: %CD%\%BUILD_DIR%\!BUILD_TYPE!\zlib1.dll (MSVC)
echo     OR: %CD%\%BUILD_DIR%\zlib1.dll (MinGW)
echo ==========================================
goto :end

:fail
echo.
echo [FAIL] Build stopped due to errors.
pause
exit /b 1

:end
pause
exit /b 0
endlocal