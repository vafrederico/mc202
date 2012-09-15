#include <stdio.h>
//Utilize as macros MALLOC e FREE para alocar e desalocar memória
#include "balloc.h"

// Máximo de aviões por fila
#define MAX 5

// Struct de um Comando
struct Comando{

    char op;
    struct Comando* proximo;

};
typedef struct Comando Comando;

// Struct de um Avião
struct Aviao{

    int id;
    int tempo;
    struct Aviao* proximo;

};
typedef struct Aviao Aviao;

// Struct da Fila
typedef struct {

    int avioes;
    Aviao* inicio;

} Fila;

// Verifica se a fila está vazia
int filaVazia(Fila* fila){

    // Se não houver avioes, retorna 1, caso contrario, 0;
    return (fila->avioes == 0);

}

// Inicia a lista de comandos
Comando* iniciaComandos(){

    // Aloca o nó cabeça
    Comando* comando = (Comando*) MALLOC(sizeof(Comando));
    comando->proximo = NULL;
    return comando;

}

// Adiciona o comando a lsita de comandos
void adicionaComando(Comando* comando, char op){

    // Rodar a lista de comandos até o fim
    Comando* temp = comando;
    while(temp->proximo != NULL) temp=temp->proximo;

    // Aloca o novo comando e adiciona ao fim da lista
    Comando* c = (Comando*)MALLOC(sizeof(Comando));
    c->op = op;
    c->proximo = NULL;
    temp->proximo = c;

}

// Libera a lista de comandos
void liberaComandos(Comando* comandos){

    Comando* temp1 = NULL;
    while(comandos != NULL){

        temp1 = comandos->proximo;
        FREE(comandos);
        comandos= temp1;

    }

}

// Adiciona um avião a fila de aterrissagem ou decolagem, retorna 0 caso o máximo seja atingido, 1 caso contrário
int adicionaFila(Fila* fila, int id, int tempo){

    // Máximo atingido?
    if(fila->avioes == MAX){

        return 0;

    }

    // Percorre a fila até o fim
    Aviao* temp = fila->inicio;
    while(temp->proximo != NULL) temp=temp->proximo;

    // Aloca-se o novo avião
    Aviao* aviao = (Aviao*)MALLOC(sizeof(Aviao));
    aviao->id = id;
    aviao->tempo = tempo;

    // Adiciona-se ele ao fim da fila
    aviao->proximo = NULL;
    temp->proximo = aviao;

    // Aumenta a contagem de aviões
    fila->avioes++;

    return 1;

}

// Remove um avião da fila, retorna o Aviao
Aviao* removeFila(Fila* fila){

    // Guarda o primeiro da fila
    Aviao* temp = fila->inicio->proximo;

    // Retira ele da fila
    fila->inicio->proximo = fila->inicio->proximo->proximo;

    // Reduz a contagem de aviões
    fila->avioes--;

    // Retorna o avião
    return temp;

}

// Inicia a fila de aviões, retorna a fila
Fila* iniciaFila(){

    Fila* fila = (Fila*) MALLOC(sizeof(Fila));
    fila->avioes = 0;
    fila->inicio = (Aviao*) MALLOC(sizeof(Aviao));
    fila->inicio->proximo = NULL;
    return fila;

}

// Libera a fila de aviões
void liberaFila(Fila* fila){

    if(fila == NULL)
        printf("NULL");
    Aviao* temp = fila->inicio;
    Aviao* temp1 = NULL;
    while(temp != NULL){

        temp1 = temp->proximo;
        FREE(temp);
        temp = temp1;

    }

    FREE(fila);

}

// Aterrissa o primeiro avião da fila, retorno o tempo em que foi adicionado
int aterrissa(Fila* filaAterrissagem){

    // Remove-se o primeiro avião da fila e o recebe
    Aviao* temp = removeFila(filaAterrissagem);

    // Avisa sobre aterrissagem
    printf("%d aterrissa\n",temp->id);

    // Guarda-se o tempo em que foi adicionado
    int tempo = temp->tempo;

    // libera o  avião
    FREE(temp);

    // Retorna o tempo
    return tempo;

}

// Decola o primeiro avião da fila, retorno o tempo em que foi adicionado
int decola(Fila* filaDecolagem){

    // Remove-se o primeiro avião da fila e o recebe
    Aviao* temp = removeFila(filaDecolagem);

    // Avisa sobre decolagem
    printf("%d decola\n",temp->id);

    // Guarda-se o tempo em que foi adicionado
    int tempo = temp->tempo;

    // libera o  avião
    FREE(temp);

    // Retorna o tempo
    return tempo;

}

// Executa a sequencia para uma única pista
void executaUmaPista(Comando* comandos){

    // Cria-se as filas
    Fila *filaAterrissagem = NULL, *filaDecolagem = NULL;

    // Vai para o primeiro comando
    Comando* temp = comandos->proximo;

    int id=0, tempo = 0, decolagens = 0, aterrissagens = 0, impedidos = 0, parada = 0, esperaAterrissagem = 0, esperaDecolagem = 0;

    // Inicia-se as filas
    filaAterrissagem = iniciaFila();
    filaDecolagem = iniciaFila();

    int tempoPrint = 0; // Necessario imprimir mensagem do tempo?
    int tempoLastCmd = 0; // Tempo foi o ultimo comando?


    printf("Aeroporto com uma pista\n\nTempo 0\n");

    while(temp != NULL){ // Enquanto houver comando

        switch(temp->op){

            case 'A': // Adiciona a fila de aterrissagem

                tempoLastCmd = 1;
                if(tempoPrint){ // Neceessario imprimir tempo?

                    printf("Tempo %d\n",tempo);
                    tempoPrint = 0;

                }

                if(adicionaFila(filaAterrissagem,++id,tempo)) // Conseguiu adicionar?
                    printf("%d entra na fila de aterrissagem\n",id);
                else { // Adiciona aos impedidos

                    impedidos++;
                    printf("%d impedido de aterrissar\n",id);

                }

                break;

            case 'D': // Adiciona a fila de decolagem

                tempoLastCmd = 1;
                if(tempoPrint){ // Neceessario imprimir tempo?

                    printf("Tempo %d\n",tempo);
                    tempoPrint = 0;

                }

                if(adicionaFila(filaDecolagem,++id,tempo)) // Conseguiu adicionar?
                    printf("%d entra na fila de decolagem\n",id);
                else { // Adiciona aos impedidos

                    impedidos++;
                    printf("%d impedido de decolar\n",id);

                }
                break;

            case 'T': // Passagem de tempo

                if(tempoPrint){ // Neceessario imprimir tempo?

                    printf("Tempo %d\n",tempo);
                    tempoPrint = 0;

                }

                if(!filaVazia(filaAterrissagem)){ // Existe avião para aterrissar?

                    aterrissagens++;

                    esperaAterrissagem += tempo - aterrissa(filaAterrissagem); // Aterrissa e adiciona ao tempo de espera

                }   else if(!filaVazia(filaDecolagem)){ // Existe avião para decolar?

                    decolagens++;

                    esperaDecolagem += tempo - decola(filaDecolagem); // Decola e adiciona ao tempo de espera

                }   else { // Pista parada

                    parada++;

                    printf("Pista parada\n");

                }

                tempo++;
                tempoPrint = 1;

                break;

            case 'F': // Fim

                if(tempoPrint && (!tempoLastCmd || (!filaVazia(filaAterrissagem) || !filaVazia(filaDecolagem)))){ // Neceessario imprimir tempo?

                    printf("Tempo %d\n",tempo);
                    tempoPrint = 0;

                }


                while(!filaVazia(filaAterrissagem)){ // Enquanto houver aviao para aterrissar

                    // Aterrissa e adiciona ao tempo de espera
                    aterrissagens++;
                    esperaAterrissagem += tempo - aterrissa(filaAterrissagem);

                    if(!filaVazia(filaAterrissagem) || !filaVazia(filaDecolagem)) // Se ainda houver aviões, anuncia-se a passagem de tempo
                        printf("Tempo %d\n",++tempo);

                }

                while(!filaVazia(filaDecolagem)){ // Enquanto houver aviao para aterrissar

                    // Decola e adiciona ao tempo de espera
                    decolagens++;
                    esperaDecolagem += tempo - decola(filaDecolagem);

                    if(!filaVazia(filaDecolagem)) // Se ainda houver aviões, anuncia-se a passagem de tempo
                        printf("Tempo %d\n",++tempo);

                }

        }

        // Próximo comando
        temp = temp->proximo;

    }

    // Libera as filas
    liberaFila(filaAterrissagem);
    liberaFila(filaDecolagem);

    printf("\n");
    printf("numero de decolagens = %d\n",decolagens);
    printf("numero de aterrissagens = %d\n",aterrissagens);
    printf("avioes impedidos de usar o aeroporto = %d\n",impedidos);
    printf("tempo de pista parada = %d\n",parada);
    printf("tempo medio de espera para aterrissar = %.2f\n",(float)esperaAterrissagem/aterrissagens);
    printf("tempo medio de espera para decolar = %.2f\n",(float)esperaDecolagem/decolagens);
    printf("\n");
}

// Executa a sequencia para duas pistas
void executaDuasPistas(Comando* comandos){

    // Cria-se as filas
    Fila *filaAterrissagem = NULL, *filaDecolagem = NULL;

    // Vai para o primeiro comando
    Comando* temp = comandos->proximo;

    int id=0, tempo = 0, decolagens = 0, aterrissagens = 0, impedidos = 0, parada = 0, esperaAterrissagem = 0, esperaDecolagem = 0;

    // Inicia-se as filas
    filaAterrissagem = iniciaFila();
    filaDecolagem = iniciaFila();

    int tempoPrint = 0; // Necessario imprimir mensagem do tempo?
    int tempoLastCmd = 0; // Tempo foi o ultimo comando?

    printf("Aeroporto com duas pistas\n\nTempo 0\n");

    while(temp != NULL){ // Enquanto houver comando

        switch(temp->op){

            case 'A': // Adiciona a fila de aterrissagem

                tempoLastCmd = 0;
                if(tempoPrint){ // Neceessario imprimir tempo?

                    printf("Tempo %d\n",tempo);
                    tempoPrint = 0;

                }

                if(adicionaFila(filaAterrissagem,++id,tempo)) // Conseguiu adicionar?
                    printf("%d entra na fila de aterrissagem\n",id);
                else { // Adiciona aos impedidos

                    impedidos++;
                    printf("%d impedido de aterrissar\n",id);

                }

                break;

            case 'D': // Adiciona a fila de decolagem

                tempoLastCmd = 0;
                if(tempoPrint){ // Neceessario imprimir tempo?

                    printf("Tempo %d\n",tempo);
                    tempoPrint = 0;

                }

                if(adicionaFila(filaDecolagem,++id,tempo)) // Conseguiu adicionar?
                    printf("%d entra na fila de decolagem\n",id);
                else { // Adiciona aos impedidos

                    impedidos++;
                    printf("%d impedido de decolar\n",id);

                }
                break;

            case 'T': // Passagem de tempo

                if(tempoPrint){ // Neceessario imprimir tempo?

                    printf("Tempo %d\n",tempo);
                    tempoPrint = 0;

                }

                if(!filaVazia(filaAterrissagem)){ // Existe avião para aterrissar?

                    aterrissagens++;

                    esperaAterrissagem += tempo - aterrissa(filaAterrissagem); // Aterrissa e adiciona ao tempo de espera

                } else { // Pista parada

                    parada++;

                    printf("Pista de aterrissagem parada\n");

                }


                if(!filaVazia(filaDecolagem)){ // Existe avião para decolar?

                    decolagens++;

                    esperaDecolagem += tempo - decola(filaDecolagem); // Decola e adiciona ao tempo de espera

                } else { // Pista parada

                    parada++;

                    printf("Pista de decolagem parada\n");

                }

                tempo++;
                tempoPrint = 1;
                tempoLastCmd = 1; // Tempo foi o ultimo comando

                break;

            case 'F': // Fim

                if(tempoPrint && (!tempoLastCmd || (!filaVazia(filaAterrissagem) || !filaVazia(filaDecolagem)))){ // Neceessario imprimir tempo?

                    printf("Tempo %d\n",tempo);
                    tempoPrint = 0;

                }

                while(!filaVazia(filaAterrissagem) || !filaVazia(filaDecolagem)){ // Enquanto houver aviao para aterrissar ou decolar

                    if(!filaVazia(filaAterrissagem)){ // Existe avião para aterrissar?

                        aterrissagens++;

                        esperaAterrissagem += tempo - aterrissa(filaAterrissagem); // Aterrissa e adiciona ao tempo de espera

                    } else { // Pista parada

                        parada++;

                        printf("Pista de aterrissagem parada\n");

                    }


                    if(!filaVazia(filaDecolagem)){ // Existe avião para decolar?

                        decolagens++;

                        esperaDecolagem += tempo - decola(filaDecolagem); // Decola e adiciona ao tempo de espera

                    } else { // Pista parada

                        parada++;

                        printf("Pista de decolagem parada\n");

                    }

                    if(!filaVazia(filaAterrissagem) || !filaVazia(filaDecolagem)) // Se ainda houver aviões, anuncia-se a passagem de tempo
                        printf("Tempo %d\n",++tempo);

                }

        }

        // Próximo comando
        temp = temp->proximo;

    }

    // Libera as filas
    liberaFila(filaAterrissagem);
    liberaFila(filaDecolagem);

    printf("\n");
    printf("numero de decolagens = %d\n",decolagens);
    printf("numero de aterrissagens = %d\n",aterrissagens);
    printf("avioes impedidos de usar o aeroporto = %d\n",impedidos);
    printf("tempo de pista parada = %d\n",parada);
    printf("tempo medio de espera para aterrissar = %.2f\n",(float)esperaAterrissagem/aterrissagens);
    printf("tempo medio de espera para decolar = %.2f\n",(float)esperaDecolagem/decolagens);

}

int main(){

    // Cria-se a lista de comandos
    Comando* comandos = iniciaComandos();

    char op = '\0';

    while(op != 'F'){ // Enquanto não chegar ao fim da entrada

        scanf("%c", &op); // Recebe o comando

        adicionaComando(comandos, op); // Adiciona-o a lista

    }

    executaUmaPista(comandos); // Executa a sequencia para uma pista

    executaDuasPistas(comandos); // Executa a sequencia para duas pistas

    liberaComandos(comandos); // Libera os comandos

	bapply(bprint); //não modifique esta linha

	return 0;

}
