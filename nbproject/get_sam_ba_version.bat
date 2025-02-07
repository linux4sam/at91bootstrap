@echo off
sam-ba -v 2>NUL
set ERROR_CODE=%ERRORLEVEL%
sam-ba -u:test::: 2>NUL

if %ERRORLEVEL% equ 0 (
    echo [Succeeded] SAM-BA tool generating bootable binary image available.
) else (
        if %ERROR_CODE% equ 0 (
            echo "Please upgrade to sam-ba v3.8 or higher for better functionality.[Failed***] SAM-BA tool version not able to generate bootable binary. (exit code %ERROR_CODE%)"
            exit /b 3
        ) else (
               echo "[Failed***] SAM-BA tool is not installed or not found in your PATH. (exit code %ERRORLEVEL%)"
               exit /b 2
    )
)
