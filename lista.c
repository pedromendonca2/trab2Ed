#include "lista.h"

struct celula{
    tArvore* arv;
    tCelula* prox;
};

struct lista{
    tCelula* primeiro;
    tCelula* ultimo;
};

// tCelula* liberaCelula(tCelula* cel){

//     tCelula* prox = cel->prox;
//     liberaArvore(cel->arv);
//     free(cel);

//     return prox;
// }

tLista* inicializaLista(){
    tLista* lista = malloc(sizeof(tLista));
    lista->primeiro = NULL;
    lista->ultimo = NULL;

    return lista;
}

void encontraLugarNaLista(tArvore* arv, tLista* lista){
    tCelula* aux = lista->primeiro;
    tCelula* novo = malloc(sizeof(tCelula));

    while(retornaPeso(arv) < retornaPeso(aux->arv)){
        aux = aux->prox;
    }

    novo->arv = arv;
    novo->prox = aux->prox;
    aux->prox = novo;
}

void insereCelulaNaLista(tArvore* arv, tLista* lista){

    if(lista->ultimo == NULL){
        tCelula* novo = malloc(sizeof(tCelula));
        lista->primeiro = lista->ultimo = novo;
        ////////////////////////////////////
        lista->ultimo->arv = arv;
        lista->ultimo->prox = NULL;
    } else if(retornaPeso(arv) >= retornaPeso(lista->ultimo->arv)){
        tCelula* novo = malloc(sizeof(tCelula));
        lista->ultimo->prox = novo;
        lista->ultimo = lista->ultimo->prox;
        ///////////////////////////////////
        lista->ultimo->arv = arv;
        lista->ultimo->prox = NULL;
    } else{
        encontraLugarNaLista(arv, lista);
    }
}

void retiraItem(tLista* lista, tArvore* arv){
    tCelula* ant = NULL;
    tCelula* p = lista->primeiro;

    while(p != NULL && p->arv != arv){
        ant = p;
        p = p->prox;
    }

    if(p == NULL) return;

    if(p == lista->primeiro && p == lista->ultimo){
        lista->primeiro = lista->ultimo = NULL;
        //liberaCelula(p);
        return; 
    }

    if(p == lista->ultimo){
        lista->ultimo = ant; 
        ant->prox = NULL; 
        //liberaCelula(p);
        return;
    }

    if(p == lista->primeiro){
        lista->primeiro = p->prox;    
    } else{
        ant->prox = p->prox;
    } 

    //liberaCelula(p);
}

void imprimeLista(tLista* lista){
    tCelula* aux;
    aux = lista->primeiro;

    while(aux != NULL){
        printf("Letra: %c ; peso: %d\n", retornaLetra(aux->arv), retornaPeso(aux->arv));
        aux = aux->prox;
    }
}

int listaUnica(tLista* l){
    if(l->primeiro == l->ultimo) return 1;
    return 0;
}

tArvore* retornaPrimeiraArv(tLista* l){
    return l->primeiro->arv;
}

tArvore* retornaSegundaArv(tLista *l){
    return l->primeiro->prox->arv;
}

void liberaLista(tLista* lista){
    tCelula *cel = lista->primeiro;
    tCelula* prox = NULL;

    while(cel != NULL){
        prox = cel->prox;
        liberaArvore(cel->arv);
        free(cel);
        cel = prox;
    }

    free(lista);
}