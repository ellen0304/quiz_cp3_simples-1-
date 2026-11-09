@echo off
gcc -Wall -Wextra -Iinclude src/main.c src/funcoes.c -o quiz.exe

if errorlevel 1 (
    echo.
    echo Erro na compilacao!
    pause
    exit /b 1
)

echo.
echo Compilacao concluida com sucesso!
echo.
quiz.exe
pause