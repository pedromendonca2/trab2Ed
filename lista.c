#include "lista.h"

struct celula{
    tArvore* arv;
    tCelula* prox;
};

struct lista{
    tCelula* primeiro;
    tCelula* ultimo;
};

tCelula* liberaCelula(tCelula* cel){

    tCelula* prox = cel->prox;
    liberaArvore(cel->arv);
    free(cel);

    return prox;
}

tLista* inicializaLista(){
    tLista* lista = malloc(sizeof(tLista));
    lista->primeiro = NULL;
    lista->ultimo = NULL;

    return lista;
}

void insereCelulaNaLista(tArvore* arv, tLista* lista){

    tCelula* novo = malloc(sizeof(tCelula));

    if(lista->ultimo == NULL){
        lista->primeiro = lista->ultimo = novo;
        ////////////////////////////////////
        lista->ultimo->arv = arv;
        lista->ultimo->prox = NULL;
    } else if(retornaPeso(arv) >= retornaPeso(lista->ultimo->arv)){
        lista->ultimo->prox = novo;
        lista->ultimo = lista->ultimo->prox;
        ///////////////////////////////////
        lista->ultimo->arv = arv;
        lista->ultimo->prox = NULL;
    } else{
        novo->arv = arv;
        novo->prox = lista->primeiro;
        lista->primeiro = novo;
    }
}


void imprimeLista(tLista* lista){
    tCelula* aux;
    aux = lista->primeiro;

    while(aux != NULL){
        printf("Letra: %c ; peso: %d\n", retornaLetra(aux->arv), retornaPeso(aux->arv));
        aux = aux->prox;
    }
}

void liberaLista(tLista* lista){
    tCelula *cel = lista->primeiro;

    while(cel != NULL){
        cel = liberaCelula(cel);
    }

    free(lista);
}

// void retiraItem(tLista* lista, char letra){
//     tCelula* ant = NULL;
//     tCelula* p = lista->primeiro;

//     while(p != NULL && retornaPreco(p->produto) != preco){
//         ant = p;
//         p = p->prox;
//     }

//     if(p == NULL) return;

//     if(p == lista->primeiro && p == lista->ultimo){
//         lista->primeiro = lista->ultimo = NULL;
//         liberaCelula(p);
//         return; 
//     }

//     if(p == lista->ultimo){
//         lista->ultimo = ant; 
//         ant->prox = NULL; 
//         liberaCelula(p);
//         return;
//     }

//     if(p == lista->primeiro){
//         lista->primeiro = p->prox;    
//     } else{
//         ant->prox = p->prox;
//     } 

//     liberaCelula(p);
// }