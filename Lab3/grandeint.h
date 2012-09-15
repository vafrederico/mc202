#ifndef __GRANDEINT_DEFINED
#define __GRANDEINT_DEFINED
#include "lista.h"
#define MAIOR_IGUAL -1
#define MAIOR_MAIOR 1
#define MAIOR_MENOR 0
/*  Fun��o que faz a obtem dos numeros e a soma deles */
void soma();
/*  Fun��o que faz a obtem dos numeros e a multiplica��o deles */
void multiplicacao();
/*  Fun��o que faz a obtem dos numeros e a divis�o deles */
void divide();
/*  Fun��o que faz a obtem da equa��o e a convers�o para n�mero de godel */
void godel();
/*  Retorna -1 caso o n�mero seja negativo, retorna 1 caso positivo */
int sinalGrandeInt(numero* num);
/*  Retorna num1 + num2 */
numero* somaGrandeInt(numero* num1, numero* num2);
/*  Retorna num1 - num2 */
numero* subtracaoGrandeInt(numero* num1, numero* num2);
/*  Retorna num1 * num2 */
numero* multiplicacaoGrandeInt(numero* num1, numero* num2);
/*  Checa se os algarismo dos numeros est� maior que 10 e arruma caso estejam */
void checagemMaiorDez(numero* num, listaEncadeada* inicio);
/*  Gera o n�mero de godel a partir da equa��o */
numero* geraGodel(char* equacao);
/*  Retorna 1 se |num1| > |num2|, 0 se |num1| < |num2| e -1 se |num1| == |num2| */
int maior(numero* num1, numero* num2);
/*  Retorna num1/num2 */
numero* divisaoGrandeInt(numero* num1, numero* num2);
/*  Retorna 1 se o n�mero � zero, 0 caso contr�rio */
int zeroNumero(struct numero* num);
/*  Faz a leitura da entrada e coloca em um TAD n�mero */
numero* leGrandeInt();
/* Imprime a lista */
void imprimeNumero(struct numero* n);
#endif
