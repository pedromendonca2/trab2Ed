#include "lista.h"
#include <string.h>

struct celula{
    tArvore* arv;
    tCelula* prox;
};

struct lista{
    tCelula* primeiro;
    tCelula* ultimo;
};

struct tabela{
    unsigned char letra;
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

tCelula *retornaPrim(tLista *lista){
    return lista->primeiro;
}

tArvore *retornaArvoreDaCelula(tCelula *c){
    return c->arv;
}

/*
-----------------------------------------
-----------------------------------------
CODIGOS CODIFICADOR
-----------------------------------------
-----------------------------------------
*/

//remove primeira arvore da lista
tArvore *removePrimeiroDaLista(tLista *lista){
    tCelula *primeira;
    if(lista->primeiro != NULL){
        primeira = lista->primeiro;
        lista->primeiro = lista->primeiro->prox;
        primeira->prox = NULL;
    }
    else{
        return NULL;
    }
    if(primeira != NULL){
        tArvore *a = primeira->arv;
        free(primeira);
        return a;
    }
    else{
        return NULL;
    }
}

//faz a arvore de huffman
tArvore *retornaHuffman(tLista *lista){
    tArvore *prim, *seg, *novo;
    while(1){
        prim = removePrimeiroDaLista(lista);
        if(prim == NULL)
        {
            return novo;
        }
        seg = removePrimeiroDaLista(lista);
        if(seg == NULL)
        {
            return novo;
        }
        if(lista->primeiro == NULL)
        {
            novo = abb_insere(novo, '\0', retornaPeso(prim)+retornaPeso(seg), prim, seg);
            return novo;
        }
        novo = abb_insere(novo, '\0', retornaPeso(prim)+retornaPeso(seg), prim, seg);
        insereCelulaNaLista(novo, lista);
    }
    return novo;
}

// gera a tabela de caminhos até o caracter
char **allocaCaminhosParaLetra(int altura_da_arvore)
{
    char **registroDeCaminhos = (char**)malloc(sizeof(char*)* 256);
    int i;
    for(i =0 ; i<256 ; i++){
        registroDeCaminhos[i] = calloc(altura_da_arvore, sizeof(char));
    }
    return registroDeCaminhos;
}

//faz os caminhos até o caracter
void fazOsCaminhos(char **registroDeCaminhos, int alturaMaximaDaArvore, char *caminho, tArvore *raiz)
{
    char esq[alturaMaximaDaArvore], dir[alturaMaximaDaArvore];// strings podem ter no maximo o tamanho da altura da arvore
    // se tiver na folha, salva o caminho
    if(ehFolha(raiz))
    {
        strcpy(registroDeCaminhos[retornaLetra(raiz)], caminho);
    }
    //senao continua andando
    else
    {
        strcpy(esq, caminho);//coloca zero
        strcpy(dir, caminho);//coloca 1
        strcat(esq, "0");
        strcat(dir, "1");
        fazOsCaminhos(registroDeCaminhos, alturaMaximaDaArvore, esq, retornaEsq(raiz));
        fazOsCaminhos(registroDeCaminhos, alturaMaximaDaArvore, dir, retornaDir(raiz));
    }
}

//exibe o caminho para o caracter
void imprimeOsCaminhos(char **registroDeCaminhos)
{
    int i;
    unsigned char c;
    for(i =0 ; i<256 ; i++)
    {
        c = i;
        if(strlen(registroDeCaminhos[i]) > 0)
        {
            printf("caminho: %s caracter:%c\n", registroDeCaminhos[i], c);
        }
    }
}















/*
-----------------------------
-----------------------------
CÓDIGOS NÃO UTILIZADOS
-----------------------------
-----------------------------
*/


/*
-------------------------------
HUFFMAN DO PEDRO HENRIQUE
-------------------------------
/*
    tArvore *t3= NULL;
    while(listaUnica(lista) == 0){ //Enquanto houver mais de um elemento na lista cria mais uma arvore que absorve as duas primeiras
        int peso_tr = retornaPeso(retornaPrimeiraArv(lista)) + retornaPeso(retornaSegundaArv(lista));

        t3 = abb_cria();
        t3 = abb_insere(t3, '\0', peso_tr, retornaPrimeiraArv(lista), retornaSegundaArv(lista));
        insereCelulaNaLista(t3, lista);
        
        //Retira os dois primeiros elementos da lista
        retiraItem(lista, retornaPrimeiraArv(lista)); 
        retiraItem(lista, retornaPrimeiraArv(lista));

        //imprimeLista(lista);
        //printf("\n");
    }
*/