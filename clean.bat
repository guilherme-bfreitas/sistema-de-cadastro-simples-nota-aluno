@echo off
REM Remove executavel e arquivos temporarios
if exist notas.exe del /f /q notas.exe
if exist obj rmdir /s /q obj
if exist data\*.tmp del /f /q data\*.tmp
echo Limpeza concluida.
pause
