@echo off
set exe=main
set testeFolder=testes\arq

for %%A in (01 02 03 04) DO (
echo *************************
echo *************************
echo **                     **
echo **       Teste %%A       **
echo **                     **
echo *************************
echo *************************
%exe% < testes\arq%%A.in > testes\arq%%A_saida.res
FC /N testes\arq%%A_saida.res testes\arq%%A.res
pause
cls
)