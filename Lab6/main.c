#include <stdlib.h>
#include <stdio.h>
#include <string.h> // REMOVER

#define MAXCLIENTES 130

typedef struct {

	int dinheiro;
	char nome[50];

} tCliente;

typedef struct{

	tCliente min;
	tCliente max;

} tHeap;

tHeap heap[65];

int tam = 0;

void imprime(){

	int i;
	for( i = 0; i < tam; i= i+2 )
		printf("i: %d, min: %d, max: %d\n", i/2, heap[i/2].min.dinheiro, heap[i/2].max.dinheiro);

}
void sobe(int pos, int max){
	
	if(pos < 0)
		return;

//	printf("sobe: pos: %d, min: %d. max: %d, ? : %d\n",pos,heap[pos].min.dinheiro, heap[pos].max.dinheiro, max);
	int posPai = (pos - 1)/2;
	tHeap pai = heap[posPai];
	tHeap atual = heap[pos];
	tCliente temp;
	if(max == -1){
	
		if(pai.min.dinheiro > atual.min.dinheiro){

			temp = pai.min;

			heap[posPai].min = atual.min;

			heap[pos].min = temp;

			sobe(posPai, 0);
		}

		else if(pai.max.dinheiro < atual.min.dinheiro){

			temp = pai.max;

			heap[posPai].max = atual.min;

			heap[pos].min = temp;

			sobe(posPai, 1);
		}


	} else if (max == 0) {

		if(pai.min.dinheiro > atual.min.dinheiro){

			temp = pai.min;

			heap[posPai].min = atual.min;

			heap[pos].min = temp;

			sobe(posPai, 0);
		}

	} else {

		if(pai.max.dinheiro < atual.max.dinheiro){

			temp = pai.max;

			heap[posPai].max = atual.max;

			heap[pos].max = temp;

			sobe(posPai, 1);

		}

	}

}

void desce (int pos, int max)
{


	tCliente temp;

	/*printf("desce %d-------",pos);
	imprime();
	if(heap[pos].max.dinheiro != 0)
		printf( " heap[pos].min.dinheiro  %d  heap[pos].max.dinheiro %d\n", heap[pos].min.dinheiro, heap[pos].max.dinheiro );*/
	if(heap[pos].max.dinheiro != 0 && heap[pos].min.dinheiro > heap[pos].max.dinheiro){ // inverte max e min caso necessario

		temp = heap[pos].min;

		heap[pos].min = heap[pos].max;

		heap[pos].max = temp;

	}


	int posFilhoEsq = pos*2 + 1;
	if(posFilhoEsq*2 >= tam){ // não possui filhos
		
		return;
	}

	tCliente* filhoAlterando;
	tCliente* atual = (max == 0? &(heap[pos]).min : &(heap[pos]).max);

	int next;

	int posFilhoDir = pos*2 + 2;
	if(posFilhoDir*2 >= tam){ // possui somente filho esquerdo
		
		if (max == 0){

			filhoAlterando = &(heap[posFilhoEsq]).min;
			if( atual->dinheiro > filhoAlterando->dinheiro){

				temp = *(filhoAlterando);
				*filhoAlterando = *atual;
				*atual = temp;

			}

		} else {
			
			filhoAlterando = &(heap[posFilhoEsq]).max;
			if( atual->dinheiro < filhoAlterando->dinheiro){

				temp = *(filhoAlterando);
				*filhoAlterando = *atual;
				*atual = temp;

			}

		}

		desce(posFilhoEsq, max);

	} else {// possui dois filhos
		//printf("tam: %d, pos %d posFilhoEsq %d posFilhoDir %d \n",tam,pos,posFilhoEsq,posFilhoDir);
		if (max == 0){

			if(heap[posFilhoEsq].min.dinheiro < heap[posFilhoDir].min.dinheiro){
				filhoAlterando = &(heap[posFilhoEsq]).min;
				next = posFilhoEsq;
			}
			else {
				filhoAlterando = &(heap[posFilhoDir]).min;
				next = posFilhoDir;
			}
			if( atual->dinheiro > filhoAlterando->dinheiro){

				temp = *(filhoAlterando);
				*filhoAlterando = *atual;
				*atual = temp;

			}
			desce(next , max);

		} else {

			if(heap[posFilhoEsq].max.dinheiro == 0){
				filhoAlterando = &(heap[posFilhoEsq]).min;
				next = posFilhoEsq;
			}
			else if(heap[posFilhoDir].max.dinheiro == 0 || heap[posFilhoEsq].max.dinheiro > heap[posFilhoDir].max.dinheiro){
				filhoAlterando = &(heap[posFilhoEsq]).max;
				next = posFilhoEsq;
			}
			else {
				filhoAlterando = &(heap[posFilhoDir]).max;
				next = posFilhoDir;
			}

			if( atual->dinheiro < filhoAlterando->dinheiro){

				temp = *(filhoAlterando);
				*filhoAlterando = *atual;
				*atual = temp;

			}
			
			desce(next, max);

		}
	}

	/*printf("------------ desce --------------\n");
	imprime();*/
}

int escritorioVazio(){

	return (tam == 0);

}

int escritorioCheio(){

	return (tam == MAXCLIENTES);
	
}

/*
	Insere cliente c no heap, retorna 1 caso tenha sucesso e 0 caso o escritório esteja cheio
 */
int insereCliente(tCliente c){

	if(escritorioCheio()) // Verifica se o escritório está cheio
		return 0;

	int pos = tam/2;
	int max = -1;
	if(heap[pos].min.dinheiro == 0){
		heap[pos].min = c;
	} else {

		if(heap[pos].min.dinheiro < c.dinheiro){
			heap[pos].max = c;
			max = 1;
		}
		else{
			heap[pos].max = heap[pos].min;
			heap[pos].min = c;
			max = 0;
		}

	}

	sobe(pos,max);
	tam++;

	return 1;

}

tCliente clienteMin(){
	return heap[0].min;
}

tCliente clienteMax(){
	if(tam == 1)
		return heap[0].min;
	else
		return heap[0].max;
}

void removeClienteMin(){

	tam--;
	
	if(heap[tam/2].max.dinheiro == 0){

		heap[0].min = heap[tam/2].min;
		heap[tam/2].min.dinheiro = 0;
		
	}else {

		heap[0].min = heap[tam/2].max;
		heap[tam/2].max.dinheiro = 0;

	}
	
	//imprime();
	desce(0, 0);

}

void removeClienteMax(){

	tam--;
	
	if(heap[tam/2].max.dinheiro == 0){

		heap[0].max = heap[tam/2].min;
		heap[tam/2].min.dinheiro = 0;
		
	}else {

		heap[0].max = heap[tam/2].max;
		heap[tam/2].max.dinheiro = 0;

	}
	
	//imprime();
	desce(0, 1);
}

int main()
{
	
	char op;
	tCliente novo;

	while(scanf("%c", &op) != EOF && op != 'X'){

		if (op != '\n')
		{
			
			switch(op){

				case 'A':
					scanf(" %d", &novo.dinheiro);
					scanf(" %[^\n]",novo.nome);

					if(!insereCliente(novo)){

						printf("Escritorio cheio\n");

					}
					//imprime();
					break;

				case 'J':
					if(escritorioVazio()){
						printf("Escritorio vazio\n");
						break;
					}

					novo = clienteMin();
					removeClienteMin();
					printf ("Joao vai atender %s (%d)\n", novo.nome, novo.dinheiro);
				//	imprime();
					break;

				case 'M':
					if(escritorioVazio()){
						printf("Escritorio vazio\n");	
						break;
					}
					novo = clienteMax();
					removeClienteMax();
					printf ("Maria vai atender %s (%d)\n", novo.nome, novo.dinheiro);
//imprime();

					break;

				case '#':
					printf("Ha %d clientes\n", tam);
					break;

			}
		}
	}

	return 0;

}