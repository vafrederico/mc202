#include <stdio.h>
#include <stdlib.h>

struct no
{
	
	int elem;
	struct no* dir;
	struct no* esq;

};
typedef struct no no;

struct arvore
{
	
	no* raiz;

};
typedef struct arvore arvore;

no* g;
no** noPai; no** noAvo; no** noBisavo;

void troca(no** n);
void removeElem(no** n, int elem, arvore* a);
void adicionaElem(no** n, int elem, arvore* a);
arvore* criaArvore();
void imprimeArv(no* n);
void rotacionaDir(no** pai, no* filho);
void rotacionaEsq(no** pai, no* filho);
void afunilamento(no** n, no** pai, no** avo, arvore* a);