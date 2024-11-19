@echo off
setlocal enabledelayedexpansion

set CPP_COMPILER=g++
set VM_TRANSLATOR_SRC=src\vm_translator.cpp src\parser.cpp src\code_writer.cpp
set VM_TRANSLATOR_OUT=VMTranslator.exe

echo Compiling VM Translator...
%CPP_COMPILER% %VM_TRANSLATOR_SRC% -o %VM_TRANSLATOR_OUT%

if not exist %VM_TRANSLATOR_OUT% (
    echo Failed to compile VM Translator
    exit /b 1
)

cd test

:: Test individual .vm files
echo Testing individual .vm files...
for %%f in (BasicLoop.vm FibonacciSeries.vm SimpleFunction.vm) do (
    echo Translating %%f...
    ..\%VM_TRANSLATOR_OUT% %%f
    if !errorlevel! neq 0 (
        echo Translation failed for %%f
    ) else (
        echo Translation completed for %%f
    )
)

:: Test folders containing multiple .vm files
echo.
echo Testing folders with multiple .vm files...
for %%d in (FibonacciElement NestedCall StaticsTest) do (
    if exist "%%d" (
        echo Translating folder %%d...
        ..\%VM_TRANSLATOR_OUT% %%d
        if !errorlevel! neq 0 (
            echo Translation failed for folder %%d
        ) else (
            echo Translation completed for folder %%d
        )
    )
)

cd ..

echo.
echo All translations completed.
del %VM_TRANSLATOR_OUT%
pause