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

for %%f in (BasicTest.vm PointerTest.vm SimpleAdd.vm StackTest.vm StaticTest.vm) do (
    echo Translating %%f...
    ..\%VM_TRANSLATOR_OUT% %%f
    if %errorlevel% neq 0 (
        echo Translation failed for %%f
    ) else (
        echo Translation completed for %%f
    )
)

cd ..

echo.
echo All translations completed.
del %VM_TRANSLATOR_OUT%
pause