#include "grandeint.h"

void soma(){
    numero* num1, *num2;
    numero* num3;
    num1 = leGrandeInt();
    num2 = leGrandeInt();
    if(sinalGrandeInt(num1) == sinalGrandeInt(num2)){
        num3 = somaGrandeInt(num1,num2);
        num3->ultimoElemento->proximoElemento->elemento = sinalGrandeInt(num2);
    } else {
        int maiorNum = maior(num1,num2);
        if(maiorNum != MAIOR_MENOR)
            num3 = subtracaoGrandeInt(num1, num2);
        else
            num3 = subtracaoGrandeInt(num2, num1);
        if(maior(num1,num2) == MAIOR_MAIOR){
            num3->ultimoElemento->proximoElemento->elemento = sinalGrandeInt(num1);
        }  else {
            num3->ultimoElemento->proximoElemento->elemento = sinalGrandeInt(num2);
        }
    }
    imprimeNumero(num3);
    destroiNumero(num1);
    destroiNumero(num2);
    destroiNumero(num3);
}

void multiplicacao(){
    numero* num1, *num2;
    numero* num3;
    num1 = leGrandeInt();
    num2 = leGrandeInt();
    num3 = multiplicacaoGrandeInt(num1,num2);
    imprimeNumero(num3);
    destroiNumero(num1);
    destroiNumero(num2);
    destroiNumero(num3);
}

void divide(){
    numero* num1, *num2;
    numero* num3;
    num1 = leGrandeInt();
    num2 = leGrandeInt();
    num3 = divisaoGrandeInt(num1,num2);
    if(vazioNumero(num3)) printf("nan\n");
    else imprimeNumero(num3);
    destroiNumero(num1);
    destroiNumero(num2);
    destroiNumero(num3);
}

void godel(){
    char eq[10];
    scanf("%s",eq);
    numero* num = geraGodel(eq);
    imprimeNumero(num);
    destroiNumero(num);
}

numero* leGrandeInt(){
    char c;
    numero* num = criarNumero();
    iniciaNumero(num);
    num->ultimoElemento->proximoElemento->elemento = 1;
    while(scanf("%c",&c) && c != '\n'){
        if(c == '-')
            num->ultimoElemento->proximoElemento->elemento = -1;
        else
            inserirElementoFim(num,c-48); // 48 = posição do 0 na tabela ascii
    }
    return num;
}

int sinalGrandeInt(numero* num){
    return num->ultimoElemento->proximoElemento->elemento;
}

numero* somaGrandeInt(numero* num1, numero* num2){
    numero* num = criarNumero();
    iniciaNumero(num);
    listaEncadeada* n1 = num1->ultimoElemento;
    listaEncadeada* n2 = num2->ultimoElemento;
    int valor = 0;
    while(n1 != num1->ultimoElemento->proximoElemento|| n2 != num2->ultimoElemento->proximoElemento){
        if(n1 != num1->ultimoElemento->proximoElemento){
            valor += n1->elemento;
            n1 = n1->anteriorElemento;
        }
        if(n2 != num2->ultimoElemento->proximoElemento){
            valor += n2->elemento;
            n2 = n2->anteriorElemento;
        }
        if(valor >= 10){
            inserirElementoInicio(num, valor - 10);
            valor = 1;
        } else {
            inserirElementoInicio(num,valor);
            valor = 0;
        }
    }
    if(valor != 0)
        inserirElementoInicio(num,valor);
    return num;
}

numero* subtracaoGrandeInt(numero* num1, numero* num2){
    numero* num = criarNumero();
    iniciaNumero(num);
    listaEncadeada* n1 = num1->ultimoElemento;
    listaEncadeada* n2 = num2->ultimoElemento;
    int valor = 0;
    while(n1 != num1->ultimoElemento->proximoElemento|| n2 != num2->ultimoElemento->proximoElemento){
        if(n1 != num1->ultimoElemento->proximoElemento){
            valor += n1->elemento;
            n1 = n1->anteriorElemento;
        }
        if(n2 != num2->ultimoElemento->proximoElemento){
            valor -= n2->elemento;
            n2 = n2->anteriorElemento;
        }
        if(valor < 0){
            inserirElementoInicio(num, valor + 10);
            valor = -1;
        } else {
            inserirElementoInicio(num,valor);
            valor = 0;
        }
    }
    if(valor != 0)
        inserirElementoInicio(num,1);
    return num;
}

numero* multiplicacaoGrandeInt(numero* num1, numero* num2){
    numero* num = criarNumero();
    iniciaNumero(num);
    numero* nt; // linha da multiplicação
    numero* aux = criarNumero();
    iniciaNumero(aux);
    listaEncadeada* temp; // corre em nt
    listaEncadeada* n2;
    listaEncadeada* n1 = num1->ultimoElemento;
    numero* numeroSomado;
    int valor = 0;
    while(n1 != num1->ultimoElemento->proximoElemento){ // para cada elemento de n1
        n2 = num2->ultimoElemento;
        nt = copiaNumero(aux); // copia o numero de zeros (potencia de 10 da linha) do aux
        temp = nt->ultimoElemento->proximoElemento->proximoElemento; // posiciona no inicio de nt
        while(n2 != num2->ultimoElemento->proximoElemento){
            valor = 0;
            valor += n1->elemento * n2->elemento;
            // havia um elemento na posição anterior?
            if(temp->anteriorElemento == nt->ultimoElemento->proximoElemento){ // cria o elemento
                inserirElementoInicio(nt,valor);
                if(valor >= 10) // vai um
                    checagemMaiorDez(nt,temp->anteriorElemento);
            }else{ // soma ao existente
                temp->anteriorElemento->elemento += valor;
                if(temp->anteriorElemento->elemento >= 10) // vai um
                    checagemMaiorDez(nt,temp->anteriorElemento);
            }
            n2 = n2->anteriorElemento;
            temp = temp->anteriorElemento;
        }
        n1 = n1->anteriorElemento;
        numeroSomado = somaGrandeInt(num,nt); // gera a soma das linhas anteriores com a nova
        destroiNumero(num);
        destroiNumero(nt);
        num = numeroSomado;
        inserirElementoFim(aux,0); // adiciona um zero ao final (proxima linha*10)
    }
    // regra de sinais
    num->ultimoElemento->proximoElemento->elemento = num1->ultimoElemento->proximoElemento->elemento * num2->ultimoElemento->proximoElemento->elemento;
    destroiNumero(aux);
    return num;
}

void checagemMaiorDez(numero* num, listaEncadeada* inicio){
    listaEncadeada* checagem = inicio;
    int valor;
    while(checagem->elemento/10 > 0){ // enquanto puder houver maior que dez a partir do inicio
        valor = checagem->elemento/10;
        // arruma-se o valor
        checagem->elemento = checagem->elemento%10;
        // vai um
        if(checagem->anteriorElemento != num->ultimoElemento->proximoElemento)
            checagem->anteriorElemento->elemento += valor;
        else
            inserirElementoInicio(num, valor);
        checagem = checagem->anteriorElemento;
    }
}

numero* geraGodel(char* equacao){
    numero* godel = criarNumero();
    iniciaNumero(godel);
    inserirElementoInicio(godel,1);
    numero* godelAux;
    char c;
    int i = 0;
    int cont = 0;
    numero* primos[10];
    for(i = 0; i < 10; i++){
        primos[i] = criarNumero();
        iniciaNumero(primos[i]);
    }
    // lista com os 10 números primos que serem elevados ao caractere
    inserirElementoFim(primos[0],2);
    inserirElementoFim(primos[1],3);
    inserirElementoFim(primos[2],5);
    inserirElementoFim(primos[3],7);
    inserirElementoFim(primos[4],1);
    inserirElementoFim(primos[4],1);
    inserirElementoFim(primos[5],1);
    inserirElementoFim(primos[5],3);
    inserirElementoFim(primos[6],1);
    inserirElementoFim(primos[6],7);
    inserirElementoFim(primos[7],1);
    inserirElementoFim(primos[7],9);
    inserirElementoFim(primos[8],2);
    inserirElementoFim(primos[8],3);
    inserirElementoFim(primos[9],2);
    inserirElementoFim(primos[9],9);
    int elevado = 0;
    for(i = 0; i < 10 && equacao[i] != '\0'; i++){
        c = equacao[i];
        switch(c){
            case '0':
                elevado = 10;
                break;
            case '+':
                elevado = 11;
                break;
            case '-':
                elevado = 12;
                break;
            case '*':
                elevado = 13;
                break;
            case '/':
                elevado = 14;
                break;
            case '=':
                elevado = 15;
                break;
            case '(':
                elevado = 16;
                break;
            case ')':
                elevado = 17;
                break;
            default:
                elevado = c - 48;
                break;
        }
        for(cont = 0; cont < elevado; cont++){
            godelAux = multiplicacaoGrandeInt(godel,primos[i]);
            destroiNumero(godel);
            godel = godelAux;
        }
    }
    for(i = 0; i < 10; i++)
        destroiNumero(primos[i]);
    return godel;
}

// num1 > num2?
int maior(numero* num1, numero* num2){
    int retorno = MAIOR_IGUAL;
    listaEncadeada* inicio1 = num1->ultimoElemento->proximoElemento->proximoElemento;
    listaEncadeada* inicio2 = num2->ultimoElemento->proximoElemento->proximoElemento;
    listaEncadeada* n1 = num1->ultimoElemento;
    listaEncadeada* n2 = num2->ultimoElemento;
    // pula os zeros
    int parar = 0;
    while(inicio1 != num1->ultimoElemento && !parar){
        if(inicio1->elemento == 0)
            inicio1 = inicio1->proximoElemento;
        else
            parar = 1;
    }
    parar = 0;
    while(inicio2 != num2->ultimoElemento && !parar){
        if(inicio2->elemento == 0)
            inicio2 = inicio2->proximoElemento;
        else
            parar = 1;
    }
    // corre até o final das listas
    while(n1 != inicio1 && n2 != inicio2){
        n1 = n1->anteriorElemento;
        n2 = n2->anteriorElemento;
    }
    if(n1 == inicio1 && n2 == inicio2){ // num1 e num2 chegaram ao fim
        n1 = inicio1;
        n2 = inicio2;
        while(n1 != num1->ultimoElemento->proximoElemento && retorno == -1){ // verifica qual possui o algorismo maior
            if(n1->elemento > n2->elemento)
                retorno = MAIOR_MAIOR;
            else if (n1->elemento < n2->elemento)
                retorno = MAIOR_MENOR;
            n1 = n1->proximoElemento;
            n2 = n2->proximoElemento;
        }
    } else if(n2 != inicio2){ // num1 chegou ao fim, num2 > num1
        retorno = MAIOR_MENOR;
    } else { // num2 chegou ao fim, num1 > num2
        retorno = MAIOR_MAIOR;
    }
    return retorno;
}

int zeroNumero(struct numero* num){
    int zero = 1;
    listaEncadeada* n = num->ultimoElemento->proximoElemento->proximoElemento;
    while(n != num->ultimoElemento->proximoElemento && zero){ // enquanto tiver um zero no inicio do numero
        if(n->elemento != 0)
            zero = 0;
        n = n->proximoElemento;
    }
    return zero;
}

numero* divisaoGrandeInt(numero* num1, numero* num2){
    numero* quociente = criarNumero();
    iniciaNumero(quociente);
    if(!zeroNumero(num2)){ // impossivel dividir por zero
        if(maior(num1, num2) != MAIOR_MENOR){ // divisão diferente de zero
            listaEncadeada* n1 = num1->ultimoElemento->proximoElemento->proximoElemento;
            listaEncadeada* n2 = num2->ultimoElemento->proximoElemento->proximoElemento;
            numero* divisor = copiaNumero(num2);
            numero* resto = copiaNumero(num1);
            numero* aux;
            numero* valorUnidade = criarNumero();
            iniciaNumero(valorUnidade);
            inserirElementoFim(valorUnidade,1);
            n2 = num2->ultimoElemento->proximoElemento->proximoElemento;
            while(n2 != num2->ultimoElemento->proximoElemento || n1 != num1->ultimoElemento->proximoElemento){
                if(n2 != num2->ultimoElemento->proximoElemento)
                    n2 = n2->proximoElemento;
                else {
                    inserirElementoFim(divisor,0);
                    if(maior(divisor,num1) == MAIOR_MAIOR)
                        removeElementoFim(divisor);
                }
                n1 = n1->proximoElemento;
            }
            while(maior(divisor,num2) == MAIOR_MAIOR){
                inserirElementoFim(quociente,0);
                while(maior(resto,divisor) == MAIOR_MAIOR){
                    aux = subtracaoGrandeInt(resto,divisor);
                    destroiNumero(resto);
                    resto = aux;
                    aux = somaGrandeInt(quociente,valorUnidade);
                    destroiNumero(quociente);
                    quociente = aux;
                }
                if(maior(resto,divisor) == MAIOR_IGUAL){
                    aux = subtracaoGrandeInt(resto,divisor);
                    destroiNumero(resto);
                    resto = aux;
                    aux = somaGrandeInt(quociente,valorUnidade);
                    destroiNumero(quociente);
                    quociente = aux;
                }
                removeElementoFim(divisor);
            }
            if(maior(divisor,num2) == MAIOR_IGUAL){
                inserirElementoFim(quociente,0);
                while(maior(resto,divisor) == MAIOR_MAIOR){
                    aux = subtracaoGrandeInt(resto,divisor);
                    destroiNumero(resto);
                    resto = aux;
                    aux = somaGrandeInt(quociente,valorUnidade);
                    destroiNumero(quociente);
                    quociente = aux;
                }
                if(maior(resto,divisor) == MAIOR_IGUAL){
                    aux = subtracaoGrandeInt(resto,divisor);
                    destroiNumero(resto);
                    resto = aux;
                    aux = somaGrandeInt(quociente,valorUnidade);
                    destroiNumero(quociente);
                    quociente = aux;
                }
            }
            destroiNumero(divisor);
            destroiNumero(resto);
            destroiNumero(valorUnidade);
            quociente->ultimoElemento->proximoElemento->elemento = num1->ultimoElemento->proximoElemento->elemento * num2->ultimoElemento->proximoElemento->elemento;
        } else  // em inteiros, se divisor > dividendo, quociente = 0
            inserirElementoFim(quociente,0);
    }
    return quociente;
}

void imprimeNumero(numero* num){
    listaEncadeada* n = num->ultimoElemento->proximoElemento->proximoElemento;
    int parar = 0;
    while(n != num->ultimoElemento && !parar){
        if(n->elemento == 0)
            n = n->proximoElemento;
        else
            parar = 1;
    }
    if(sinalGrandeInt(num) < 0 && !zeroNumero(num)) printf("-");
    while(n != num->ultimoElemento->proximoElemento){
        printf("%d",n->elemento);
        n = n->proximoElemento;
    }
    printf("\n");
}
