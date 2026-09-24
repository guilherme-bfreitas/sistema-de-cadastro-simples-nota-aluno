@echo off
REM Build simples: compila e linka todos os fontes em um executável notas.exe
REM Ajuste o nome do executável se desejar.

REM Verifica se gcc está disponível (sem usar where)
gcc --version >nul 2>&1
if errorlevel 1 (
  echo ERRO: gcc nao encontrado no PATH. Instale MinGW ou MSYS2 e adicione gcc ao PATH.
  pause
  exit /b 1
)

REM Compila todos os .c e gera o executavel notas.exe
gcc -Iinclude src\main.c src\utils.c src\students.c src\exams.c src\grades.c -o notas.exe -std=c11 -Wall -Wextra

if errorlevel 1 (
  echo Erros de compilacao. Corrija e execute build.bat novamente.
  pause
  exit /b 1
)

echo Compilacao concluida com sucesso: notas.exe
pause
