#include "datastruct.h"

arvore* criaArvore(){

	arvore* arv = (arvore*) malloc(sizeof(arvore));
	arv->raiz = NULL;
	return arv;

}

void adicionaElem(no** n, int elem, arvore* a){

	if(*n == NULL){

		*n = (no*) malloc(sizeof(no));
		(*n)->esq = NULL;
		(*n)->dir = NULL;
		(*n)->elem = elem;
		
	}
	else if(elem < (*n)->elem){

		adicionaElem(&(*n)->esq, elem, a);

	} else if(elem > (*n)->elem){

		adicionaElem(&(*n)->dir, elem, a);

	}

}

void removeElem(no** n, int elem, arvore* a){

	if(*n == NULL){
		
		return;

	}
	else if(elem < (*n)->elem){

		noBisavo = noAvo;
		noAvo = noPai;
		noPai = n;
		removeElem(&(*n)->esq, elem, a);

	} else if(elem > (*n)->elem){

		noBisavo = noAvo;
		noAvo = noPai;
		noPai = n;
		removeElem(&(*n)->dir, elem, a);

	} else {

		g = *n;
		if((*n)->dir == NULL || (*n)->esq == NULL){ // Remoção um filho

			if((*n)->dir == NULL) // Direita nula, substitui pela esquerda
				*n = g->esq;

			else // Esquerda nula, substitui pela direita
				*n = g->dir;

		} else { // Remoção dois filhos

			troca(&(g->esq)); 
		}

		free(g);

		afunilamento(noPai, noAvo, noBisavo, a);
	}


}

void troca(no** n){

	if((*n)->dir == NULL){

		g->elem = (*n)->elem;
		g = *n;
		*n = (*n)->esq;

	}

}

void rotacionaDir(no** pai, no* filho){

	(*pai)->esq = filho->dir;
	filho->dir = *pai;
	*pai =filho;

}

void rotacionaEsq(no** pai, no* filho){

	(*pai)->dir = filho->esq;
	filho->esq = *pai;
	pai = &(filho);

}

void imprimeArv(no* n){

	if(n != NULL){

		imprimeArv(n->esq);
		printf("%d\n", n->elem);
		imprimeArv(n->dir);

	}

}

void afunilamento(no** filho, no** pai, no** avo, arvore* a){

	while(*filho != a->raiz){

		if(*pai == a->raiz){

			printf("r simples:\n");
			if(*filho == (*pai)->esq){

				rotacionaDir(pai, *filho);
				filho = pai;

			} else {

				rotacionaEsq(pai, *filho);
				filho = pai;

			}

		} else if( (*filho == (*pai)->esq && (*pai) == (*avo)->esq) || (*filho == (*pai)->dir && (*pai) == (*avo)->dir)) {

			printf("r homo\n");
			if(*filho == (*pai)->esq){

				rotacionaDir(avo, *pai);
				rotacionaDir(avo, *filho);

				filho = avo;
		
			} else {

				rotacionaEsq(avo, *pai);
				rotacionaEsq(avo, *filho);
				filho = avo;

			}

		} else {

			printf("r hetero\n");
			if(*filho == (*pai)->esq){

				rotacionaDir(pai, *filho);
				rotacionaEsq(avo, *filho);
				filho = avo;

			} else {

				rotacionaEsq(pai, *filho);
				rotacionaDir(avo, *filho);
				filho = avo;
				
			}

		}

	}

}