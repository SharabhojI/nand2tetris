@echo off
setlocal enabledelayedexpansion

set CPP_COMPILER=g++
set ASSEMBLER_SRC=src\assembler.cpp src\parser.cpp src\code.cpp src\symbol_table.cpp
set ASSEMBLER_OUT=HackAssembler.exe

echo Compiling assembler...
%CPP_COMPILER% %ASSEMBLER_SRC% -o %ASSEMBLER_OUT%

if not exist %ASSEMBLER_OUT% (
    echo Failed to compile assembler
    exit /b 1
)

cd test

for %%f in (Add.asm Max.asm Rect.asm Pong.asm) do (
    echo Testing %%f...
    ..\%ASSEMBLER_OUT% %%f
    if %errorlevel% neq 0 (
        echo Assembler failed for %%f
    ) else (
        fc /b %%~nf.hack %%~nf_test.hack > nul
        if %errorlevel% neq 0 (
            echo Test failed for %%f
            echo Differences found:
            fc %%~nf.hack %%~nf_test.hack
        ) else (
            echo Test passed for %%f
        )
    )
)

cd ..

echo.
echo All tests completed.
del %ASSEMBLER_OUT%
pause
