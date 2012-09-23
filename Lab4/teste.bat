@echo off
set exe=principal
set testeFolder=Testes\arq

for %%A in (01 02 03) DO (
echo *************************
echo *************************
echo **                     **
echo **       Teste %%A       **
echo **                     **
echo *************************
echo *************************
echo Entrada: 
TYPE %testeFolder%%%A\arq%%A.in
echo ============================================================
%exe% < %testeFolder%%%A\arq%%A.in > %testeFolder%%%A\arq%%A_saida.res
TYPE %testeFolder%%%A\arq%%A_saida.res
FC /N %testeFolder%%%A\arq%%A_saida.res %testeFolder%%%A\arq%%A.res
pause
cls
)