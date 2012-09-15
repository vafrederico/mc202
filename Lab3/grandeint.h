#ifndef __GRANDEINT_DEFINED
#define __GRANDEINT_DEFINED
#include "lista.h"
#define MAIOR_IGUAL -1
#define MAIOR_MAIOR 1
#define MAIOR_MENOR 0
/*  Função que faz a obtem dos numeros e a soma deles */
void soma();
/*  Função que faz a obtem dos numeros e a multiplicação deles */
void multiplicacao();
/*  Função que faz a obtem dos numeros e a divisão deles */
void divide();
/*  Função que faz a obtem da equação e a conversão para número de godel */
void godel();
/*  Retorna -1 caso o número seja negativo, retorna 1 caso positivo */
int sinalGrandeInt(numero* num);
/*  Retorna num1 + num2 */
numero* somaGrandeInt(numero* num1, numero* num2);
/*  Retorna num1 - num2 */
numero* subtracaoGrandeInt(numero* num1, numero* num2);
/*  Retorna num1 * num2 */
numero* multiplicacaoGrandeInt(numero* num1, numero* num2);
/*  Checa se os algarismo dos numeros está maior que 10 e arruma caso estejam */
void checagemMaiorDez(numero* num, listaEncadeada* inicio);
/*  Gera o número de godel a partir da equação */
numero* geraGodel(char* equacao);
/*  Retorna 1 se |num1| > |num2|, 0 se |num1| < |num2| e -1 se |num1| == |num2| */
int maior(numero* num1, numero* num2);
/*  Retorna num1/num2 */
numero* divisaoGrandeInt(numero* num1, numero* num2);
/*  Retorna 1 se o número é zero, 0 caso contrário */
int zeroNumero(struct numero* num);
/*  Faz a leitura da entrada e coloca em um TAD número */
numero* leGrandeInt();
/* Imprime a lista */
void imprimeNumero(struct numero* n);
#endif
