#include "lista.h"
void iniciaNumero(numero* n){
    n->ultimoElemento = (listaEncadeada*) MALLOC(sizeof(listaEncadeada));
	n->ultimoElemento->proximoElemento = n->ultimoElemento;
	n->ultimoElemento->anteriorElemento = n->ultimoElemento;
    n->ultimoElemento->elemento = 1;
}
struct numero* criarNumero(){
	numero* temp;
	temp = (numero*) MALLOC(sizeof(numero));
	temp->ultimoElemento = NULL;
	return temp;
}
void destroiNumero(struct numero* n ){
    listaEncadeada* temp = n->ultimoElemento->proximoElemento;
    listaEncadeada* proximo;
    while(temp != n->ultimoElemento){
       proximo = temp->proximoElemento;
       FREE(temp);
       temp = proximo;
    }
    FREE(n->ultimoElemento);
    FREE(n);
}
void inserirElementoFim( struct numero* n, int e ){
	listaEncadeada* temp = n->ultimoElemento;
	listaEncadeada* temp1 = (listaEncadeada*)MALLOC(sizeof(listaEncadeada));
	temp1->elemento = e;
    temp->proximoElemento->anteriorElemento = temp1;
    temp1->proximoElemento = temp->proximoElemento;
    temp1->anteriorElemento = temp;
    temp->proximoElemento = temp1;
    n->ultimoElemento = temp1;
}

void inserirElementoInicio( struct numero* n, int e ){
	listaEncadeada* temp = n->ultimoElemento->proximoElemento;
	listaEncadeada* temp1 = (listaEncadeada*)MALLOC(sizeof(listaEncadeada));
	temp1->elemento = e;
    if(temp->anteriorElemento == temp){
        temp->anteriorElemento = temp1;
        n->ultimoElemento = temp1;
    }
    temp1->proximoElemento = temp->proximoElemento;
    temp->proximoElemento = temp1;
    temp1->anteriorElemento = temp;
    temp1->proximoElemento->anteriorElemento = temp1;
}

numero* copiaNumero(numero* num){
    numero* temp = criarNumero();
    iniciaNumero(temp);
    listaEncadeada* n = num->ultimoElemento;
    while(n != num->ultimoElemento->proximoElemento){
        inserirElementoInicio(temp, n->elemento);
        n = n->anteriorElemento;
    }
    return temp;
}

void removeElementoFim( struct numero* n){
	listaEncadeada* temp = n->ultimoElemento;
    temp->anteriorElemento->proximoElemento = temp->proximoElemento;
    n->ultimoElemento->proximoElemento->anteriorElemento = temp->anteriorElemento;
    n->ultimoElemento = temp->anteriorElemento;
	FREE(temp);
}

int vazioNumero(struct numero* n){
    return (n->ultimoElemento->proximoElemento == n->ultimoElemento);
}
