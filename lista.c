#include "lista.h"

struct celula{
    tArvore* arv;
    tCelula* prox;
};

struct lista{
    tCelula* primeiro;
    tCelula* ultimo;
};

struct tabela{
    char letra;
    char* binario;
};

tLista* inicializaLista(){
    tLista* lista = malloc(sizeof(tLista));
    lista->primeiro = NULL;
    lista->ultimo = NULL;

    return lista;
}

tTabela** criaTabela(tLista* lista, int num){
    tCelula* aux = lista->primeiro;
    tTabela** vet = malloc(num * sizeof(tTabela*));
    int i = 0;

    while(aux != NULL){
        vet[i] = malloc(sizeof(tTabela));
        vet[i]->letra = retornaLetra(aux->arv);
        vet[i]->binario = NULL;
        i++;
        aux = aux->prox;
    }

    return vet;
}

void encontraLugarNaLista(tArvore* arv, tLista* lista){
    tCelula* aux = lista->primeiro;
    tCelula* novo = malloc(sizeof(tCelula));

    // printf("letra arv: %c\n", retornaLetra(arv));
    // printf("peso arv: %d\n", retornaPeso(arv));

    if(retornaPeso(arv) <= retornaPeso(aux->arv)){
        novo->arv = arv;
        novo->prox = aux;
        lista->primeiro = novo;
    } else{
        while(aux->prox != NULL && retornaPeso(arv) > retornaPeso(aux->prox->arv)){
            aux = aux->prox;
            // if(aux == NULL){
            //     printf("Um abraco\n");
            //     exit(1);
            // }
        }
        novo->arv = arv;
        novo->prox = aux->prox;
        aux->prox = novo;
    }
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
        free(p);
        return; 
    }

    if(p == lista->ultimo){
        lista->ultimo = ant; 
        ant->prox = NULL; 
        free(p);
        return;
    }

    if(p == lista->primeiro){
        lista->primeiro = p->prox;    
    } else{
        ant->prox = p->prox;
    } 

    free(p);
}

void imprimeLista(tLista* lista){
    tCelula* aux = lista->primeiro;

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

char retornaLetraTab(tTabela* tab){
    return tab->letra;
}

char* retornaBinarioTab(tTabela* tab){
    return tab->binario;
}

void liberaTabela(tTabela** tab, int num){
    for(int i=0; i<num; i++){
        free(tab[i]);
    }
    free(tab);
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