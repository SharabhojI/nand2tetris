@echo off
setlocal enabledelayedexpansion

set CPP_COMPILER=g++
set JACK_ANALYZER_SRC=src\jack_analyzer.cpp src\jack_tokenizer.cpp src\compilation_engine.cpp
set JACK_ANALYZER_OUT=JackTokenizer.exe

echo Compiling Jack Analyzer...
%CPP_COMPILER% %JACK_ANALYZER_SRC% -o %JACK_ANALYZER_OUT%

if not exist %JACK_ANALYZER_OUT% (
    echo Failed to compile Jack Analyzer
    exit /b 1
)

cd test

:: Test the folders containing .jack file(s)
echo.
echo Testing folders containing .jack file^(s^)... 
for %%d in (ArrayTest ExpressionLessSquare Square) do (
    if exist "%%d" (
        echo. 
        echo Performing syntax analysis for folder %%d...
        ..\%JACK_ANALYZER_OUT% %%d
        if !errorlevel! neq 0 (
            echo Syntax analysis failed for folder %%d
            exit /b 1
        ) else (
            echo Syntax analysis completed for folder %%d
        )

        :: Compare generated XML files with expected _cmp.xml files
        echo Comparing XML output in %%d...
        for %%f in (%%d\*.xml) do (
            set "generated=%%f"
            set "base_name=%%~nf"
            
            :: Only process files that do not have _cmp in the name
            echo %%~nxf | findstr /i "_cmp.xml" >nul
            if errorlevel 1 (
                set "expected=%%~dpf!base_name!_cmp.xml"
                echo Comparing !generated! with !expected!...

                :: Check if the expected _cmp.xml file exists
                if exist "!expected!" (
                    fc "!generated!" "!expected!" >nul
                    if !errorlevel! neq 0 (
                        echo [FAILED] !generated! does not match !expected!
                    ) else (
                        echo [PASSED] !generated! matches !expected!
                    )
                ) else (
                    echo [WARNING] Expected file "!expected!" not found!
                )
            )
        )
    ) else (
        echo [WARNING] Folder %%d does not exist.
    )
)

cd ..

echo.
echo All syntax analyses and comparisons completed.
del %JACK_ANALYZER_OUT%
pause
