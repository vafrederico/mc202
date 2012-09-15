#ifndef __LISTA_DEFINED
#define __LISTA_DEFINED
#include <stdio.h>
#include <stdlib.h>
#include "balloc.h"
/*Tipos abstratos de dados (TADs)*/
struct listaEncadeada{  // no cabeca representa o sinal, 1 positvo, 0 negativo
	int elemento;
	struct listaEncadeada* proximoElemento;
	struct listaEncadeada* anteriorElemento;
};
struct numero{
	struct listaEncadeada* ultimoElemento;
};
typedef struct listaEncadeada listaEncadeada;
typedef struct numero numero;
/*Aloca memoria para um novo numero, setando sua variavel lista para NULL*/
struct numero* criarNumero();
/* Cria o no cabe�a */
void iniciaNumero(numero* n);
/*Desaloca a mem�ria alocada para o numero n*/
void destroiNumero( struct numero* n );
/*Insere o elemento no final do numero n*/
void inserirElementoFim( struct numero* n, int e );
/*Insere o elemento no inico do numero n*/
void inserirElementoInicio( struct numero* n, int e );
/* Remove o ultimo elemento */
void removeElementoFim(struct numero* n);
/* Copia a lista */
numero* copiaNumero(numero* num);
/* Retorna 1 se a lista est� vazia */
int vazioNumero(struct numero* n);
#endif
