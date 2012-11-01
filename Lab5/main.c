#include "datastruct.h"

int main(){

	arvore* a = criaArvore();

	adicionaElem(&(a->raiz), 10, a);
	adicionaElem(&(a->raiz), 3, a);
	adicionaElem(&(a->raiz), 8, a);
	adicionaElem(&(a->raiz), 5, a);
	adicionaElem(&(a->raiz), 6, a);
	adicionaElem(&(a->raiz), 4, a);
	adicionaElem(&(a->raiz), 9, a);
	adicionaElem(&(a->raiz), 2, a);
	adicionaElem(&(a->raiz), 1, a);
	adicionaElem(&(a->raiz), 11, a);
	imprimeArv(a->raiz);
	printf("-----------------------\n");

	noAvo = NULL;
	noPai = NULL;
	removeElem(&(a->raiz), 8, a);
	printf("Raiz: %d\n", a->raiz->elem);
	imprimeArv(a->raiz);
	printf("-----------------------\n");
	return 0;

}