#include "main.h"

/*
IMPLEMENTE SUAS FUNÇÕES AQUI


*/
typedef struct lista_encadeada lista_encadeada;
typedef struct conjunto conjunto;

// Inicia a lista ordenada de um conjunto c
void inicia_lista(conjunto* c){

    c->lista = (lista_encadeada*) MALLOC(sizeof(lista_encadeada));
	c->lista->proximo_elemento = NULL;
    c->lista->elemento = -1;
}

struct conjunto* criar_conjunto(){

	conjunto* temp;
	temp = (conjunto*) MALLOC(sizeof(conjunto));
	temp->lista = NULL;
	return temp;

}

struct conjunto* diferenca( struct conjunto* c1, struct conjunto* c2 ){

    conjunto* c = criar_conjunto();
    inicia_lista(c);

    // Roda C1, se houver em c1 e não em c2, adiciona ao conjunto c
    lista_encadeada* temp = c1->lista->proximo_elemento;
    while(temp != NULL){

        // Elemento não existe em c2?
        if(!pertinencia(c2,temp->elemento)){

            inserir_elemento(c,temp->elemento);

        }

        temp = temp->proximo_elemento;

    }

    return c;

}

int subconjunto( struct conjunto* c1, struct conjunto* c2 ){

    lista_encadeada* temp = c1->lista->proximo_elemento;
    lista_encadeada* temp1 = c2->lista->proximo_elemento;

    while(temp != NULL && temp1 != NULL){

        // Elemento são diferentes?
        if(temp->elemento != temp1->elemento){

            // O elemento de c2 é maior que de c1, se sim, não há igualdade
            if(temp1->elemento > temp->elemento)
                return 0;

            else // Move c2;
                temp1 = temp1->proximo_elemento;

        } else {

            temp = temp->proximo_elemento;
            temp1 = temp1->proximo_elemento;

        }

    }

    // Se o c1 não terminou, havia elementos não presentes em c2
    if(temp != NULL)
        return 0;

    return 1;

}

struct conjunto* uniao( struct conjunto* c1, struct conjunto* c2 ){

    conjunto* c = criar_conjunto();
    inicia_lista(c);

    lista_encadeada* temp = c1->lista->proximo_elemento;
    lista_encadeada* temp1 = c2->lista->proximo_elemento;

    lista_encadeada* e = c->lista;

    while(temp != NULL || temp1 != NULL){

        e->proximo_elemento = (lista_encadeada*) MALLOC(sizeof(lista_encadeada));
        e->proximo_elemento->proximo_elemento = NULL;

        if(temp == NULL){

            e->proximo_elemento->elemento = temp1->elemento;
            temp1 = temp1->proximo_elemento;

        } else if(temp1 == NULL){

            e->proximo_elemento->elemento = temp->elemento;
            temp = temp->proximo_elemento;

        } else if(temp->elemento > temp1->elemento){

            e->proximo_elemento->elemento = temp1->elemento;

            temp1 = temp1->proximo_elemento;

        } else if(temp->elemento < temp1->elemento) {

            e->proximo_elemento->elemento = temp->elemento;

            temp = temp->proximo_elemento;

        } else {

            e->proximo_elemento->elemento = temp->elemento;
            temp = temp->proximo_elemento;
            temp1 = temp1->proximo_elemento;

        }

        e = e->proximo_elemento;

    }

    return c;

}

int igualdade( struct conjunto* c1, struct conjunto* c2 ){

    lista_encadeada* temp = c1->lista;
    lista_encadeada* temp1 = c2->lista;

    // Enquanto houver um próximo elemento nas duas listas
    while(temp->proximo_elemento != NULL && temp1->proximo_elemento != NULL){

        // Elemento são diferntes?
        if(temp->elemento != temp1->elemento){

            return 0;

        }

        // Move ambas as listas
        temp = temp->proximo_elemento;
        temp1 = temp1->proximo_elemento;

    }

    // Se uma delas não chegou ao final
    if(temp1->proximo_elemento || temp->proximo_elemento)
        return 0;

    // São iguais
    return 1;


}

int cardinalidade( struct conjunto* c ){

    // Pula o nó cabeça
    lista_encadeada* temp = c->lista->proximo_elemento;

    int cont = 0;

    // Enquanto houver um elemento
    while(temp != NULL){

        // Soma
        cont++;

        temp = temp->proximo_elemento;

    }

    return cont;

}

struct conjunto* intersecao( struct conjunto* c1, struct conjunto* c2 ){

    conjunto* c = criar_conjunto();
    inicia_lista(c);

    lista_encadeada* temp = c1->lista->proximo_elemento;
    lista_encadeada* temp1 = c2->lista->proximo_elemento;
    lista_encadeada* e = c->lista;
    while(temp != NULL && temp1 != NULL){

        // Elemento são iguais?
        if(temp->elemento == temp1->elemento){

            e->proximo_elemento = (lista_encadeada*) MALLOC(sizeof(lista_encadeada));
            e->proximo_elemento->proximo_elemento = NULL;

            e->proximo_elemento->elemento = temp1->elemento;

            e = e->proximo_elemento;

            temp = temp->proximo_elemento;
            temp1 = temp1->proximo_elemento;

        } else if(temp->elemento > temp1->elemento) {

            temp1 = temp1->proximo_elemento;

        } else {

            temp = temp->proximo_elemento;

        }

    }

    return c;

}

int pertinencia( struct conjunto* c, int e ){

    lista_encadeada* temp = c->lista;

    // Enquanto houver um próximo elemento
    while(temp->proximo_elemento != NULL){

        // Caso ache o elemento
       if(temp->proximo_elemento->elemento == e) return 1;

        temp = temp->proximo_elemento;

    }

    // Não achou
    return 0;

}

void deletar_conjunto( struct conjunto* c ){

    lista_encadeada* temp = c->lista;
    lista_encadeada* proximo;

    // Enquanto temp for um ponteiro válido
    while(temp != NULL){

        // Salva o próximo elemento
       proximo = temp->proximo_elemento;

       //printf("Removendo %d\n",temp->elemento);

       // Libera o ponteiro
       FREE(temp);

       // Move para o próximo
       temp = proximo;

    }

    // Libera o conjunto
    FREE(c);

}

void remover_elemento( struct conjunto* c, int e ){

    lista_encadeada* temp = c->lista;

    // Enquanto houver um próximo elemento
    while(temp->proximo_elemento != NULL){

        // Caso ache o elemento
       if(temp->proximo_elemento->elemento == e){

           // Salva o ponteiro a remover
           lista_encadeada* listaRemover = temp->proximo_elemento;

            // "Religa" a lista
            temp->proximo_elemento = temp->proximo_elemento->proximo_elemento;

            // Libera o ponteiro
            FREE(listaRemover);
            return;

        }

        temp = temp->proximo_elemento;
    }

}

void inserir_elemento( struct conjunto* c, int e ){

	lista_encadeada* temp = c->lista;
	lista_encadeada* temp1 = (lista_encadeada*)MALLOC(sizeof(lista_encadeada));
	temp1->elemento = e;

	// Enquanto houver proximo elemento
    while(temp->proximo_elemento != NULL){

        // Sai caso já exista o elemento
        if(temp->proximo_elemento->elemento == e){

             FREE(temp1);
             return;

        }

        // Se o elemento for menor que o próximo deve adicioná-lo e sair
        if(e < temp->proximo_elemento->elemento){
            temp1->proximo_elemento = temp->proximo_elemento;
            temp->proximo_elemento = temp1;
            return;
        }

        temp = temp->proximo_elemento;

    }

    // Caso tenha rodado até o fim da lista, adicionar no final
   temp->proximo_elemento = temp1;
   temp1->proximo_elemento=NULL;

}

int main(){
	struct conjunto* C[10];
	int i;
	for( i = 0; i < 10; ++i )
		C[i] = criar_conjunto(); //cria os 10 conjuntos vazios
		//ou:
		//C[i] = NULL
    for( i = 0; i < 10; ++i )
		inicia_lista(C[i]);
    conjunto* c;
	char op;
	int c1,c2,c3;
	while( 1 ){
        scanf("%c", &op);
		switch( op ){
			case 'A':
                scanf("%d %d", &c1, &c2);
                inserir_elemento(C[c1-1],c2);
				break;
			case 'R':
                scanf("%d %d", &c1, &c2);
                remover_elemento(C[c1-1],c2);
				break;
			case 'L':
                scanf("%d", &c1);
                listar_elementos(C[c1-1]);
				break;
			case 'F':
                scanf("%d", &c1);
                deletar_conjunto(C[c1-1]);
                C[c1-1] = criar_conjunto();
                inicia_lista(C[c1-1]);
				break;
			case 'I':
                scanf("%d %d %d", &c1, &c2, &c3);
                c = intersecao(C[c1-1],C[c2-1]);
                deletar_conjunto(C[c3-1]);
                C[c3-1] = c;
                break;
			case 'U':
                scanf("%d %d %d", &c1, &c2, &c3);
                c = uniao(C[c1-1],C[c2-1]);
                deletar_conjunto(C[c3-1]);
                C[c3-1] = c;
				break;
			case 'P':
                scanf("%d %d", &c1, &c2);
                if(pertinencia(C[c1-1],c2))
                    printf("S\n");
                else
                    printf("N\n");
				break;
			case 'D':
                scanf("%d %d %d", &c1, &c2, &c3);
                c = diferenca(C[c1-1],C[c2-1]);
                deletar_conjunto(C[c3-1]);
                C[c3-1] = c;
				break;
			case 'C':
                scanf("%d %d", &c1, &c2);
                if(subconjunto(C[c1-1],C[c2-1]))
                    printf("S\n");
                else
                    printf("N\n");
				break;
			case '=':
                scanf("%d %d", &c1, &c2);
                if(igualdade(C[c1-1],C[c2-1]))
                    printf("S\n");
                else
                    printf("N\n");
				break;
            case '#':
				scanf("%d", &c1 );
				printf("%d\n", cardinalidade( C[c1-1]) );
				break;
			case 'X':
                for( i = 0; i < 10; ++i )
                    deletar_conjunto(C[i]);
				bapply(bprint); //não modifique esta linha
				return 0;
		}

	}

}
