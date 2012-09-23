@echo off
set exe=bin\Debug\Lab2
set testeFolder=Testes\arq

for %%A in (1 2 3 4 5 6 7 8 9) DO (
echo *************************
echo *************************
echo **                     **
echo **       Teste %%A       **
echo **                     **
echo *************************
echo *************************
%exe% < %testeFolder%%%A\arq%%A.in > %testeFolder%%%A\arq%%A_saida.res
TYPE %testeFolder%%%A\arq%%A_saida.res
FC /N %testeFolder%%%A\arq%%A_saida.res %testeFolder%%%A\arq%%A.res
pause
cls
)