@echo off
set exe=bin\Debug\Lab3
set testeFolder=Testes\arq0

for %%A in (1 2 3 4 5 6 7 8 9) DO (
echo *************************
echo *************************
echo **                     **
echo **       Teste %%A       **
echo **                     **
echo *************************
echo *************************
echo Entrada: 
TYPE %testeFolder%%%A\arq0%%A.in
echo ============================================================
%exe% < %testeFolder%%%A\arq0%%A.in > %testeFolder%%%A\arq0%%A_saida.res
TYPE %testeFolder%%%A\arq0%%A_saida.res
FC /N %testeFolder%%%A\arq0%%A_saida.res %testeFolder%%%A\arq0%%A.res
pause
cls
)