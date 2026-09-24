@echo off
REM Executa o programa notas.exe garantindo que a pasta data exista
if not exist data (
  echo Pasta data nao encontrada. Criando data e copiando exemplos...
  mkdir data
  REM Opcional criar arquivos CSV vazios se nao existirem
  if not exist datastudents.csv echo 2023001,Mariana Silvadatastudents.csv
  if not exist dataexams.csv echo AV1,Prova 1,2026-06-10dataexams.csv
  if not exist datagrades.csv echo 2023001,AV1,8.5datagrades.csv
)

if not exist notas.exe (
  echo Executavel notas.exe nao encontrado. Execute build.bat primeiro.
  pause
  exit b 1
)

REM Executa
notas.exe

pause
