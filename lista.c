#include "lista.h"
#include <string.h>

/*
-----------------------------------------------
-----------------------------------------------
CODIGOS DE MANIPULACAO DE ESTRUTURAS DE DADOS
-----------------------------------------------
-----------------------------------------------
*/


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

// gera a tabela de caminhos ateh o caracter
char **allocaCaminhosParaLetra(int altura_da_arvore)
{
    char **registroDeCaminhos = (char**)malloc(sizeof(char*)* 256);
    int i;
    for(i =0 ; i<256 ; i++){
        registroDeCaminhos[i] = calloc(altura_da_arvore, sizeof(char));
    }
    return registroDeCaminhos;
}

//faz os caminhos ateh o caracter
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

// gera o binario em formato de string ex: "10010100"
void arquivoBinarioEmString(char **registroDeCaminhos, unsigned char *filepath)
{
    FILE *arquivo_texto = fopen(filepath, "r");
    if(arquivo_texto == NULL)
    {
        printf("arquivo texto nao abriu\n");
        exit(1);
    }
    FILE *arquivo_binario_string = fopen("stringbinario.txt", "w");
    if(arquivo_binario_string == NULL)
    {
        printf("Arquivo texto em binario abriu\n");
        exit(0);
    }
    unsigned char c;
    while(fscanf(arquivo_texto,"%c", &c) == 1)
    {
        fprintf(arquivo_binario_string, "%s", registroDeCaminhos[c]);
    }
    fclose(arquivo_binario_string);
    fclose(arquivo_texto);
}

// compactar o arquivo em bytes
void compactado(tArvore* huffman)
{
    FILE *arquivo = fopen("compactado.bin.comp", "wb");
    if(arquivo == NULL)
    {
        printf("Arquivo compactado.bin não abriu para escrita\n");
        exit(1);
    }

    //Salvar a árvore de Huffman no início do arquivo binário
    armazenaArvore(huffman, arquivo);

    FILE *arquivo2 = fopen("stringbinario.txt", "r");
    if(arquivo2 == NULL){
        printf("stringbinario.txt nao foi aberto para conversao em binario\n");
        exit(0);
    }
    int i = 0, j = 7;
    unsigned char byte = 0, base, letra;
    while(fscanf(arquivo2, "%c", &letra) == 1)
    {
        base = 1;
        if(letra == '1'){
            base = base << j;
            byte = byte | base;
        }
        j--;
        // byte feito
        if(j<0)
        {
            fwrite(&byte, sizeof(unsigned char), 1, arquivo);
            byte = 0;
            j = 7;
        }
    }
    // se algum byte em formação nao foi colocado no binario
    if(j != 7)
    {
        fwrite(&byte, sizeof(unsigned char), 1, arquivo);
    }
    fclose(arquivo);
    fclose(arquivo2);
}

//libera caminhos para as strings
void liberaCaminhos(char **caminhos)
{
    if(caminhos == NULL) return;
    int i;
    for( i =0 ; i < 256 ; i++)
    {
        if(caminhos[i] != NULL) free(caminhos[i]);
    }
    free(caminhos);
}


/*
----------------------------
----------------------------
CODIGOS DESCOMPACTADOR
----------------------------
----------------------------
*/

void descompactar()
{
    FILE *arquivo = fopen("compactado.bin.comp", "rb");
    if(arquivo == NULL)
    {
        printf("Arquivo de descompactacao nao abriu!\n");
        exit(0);
    }

    // Recuperar a árvore de Huffman do início do arquivo binário
    tArvore *arv = recuperaArvore(arquivo);
    tArvore *aux = arv;
    unsigned char byte;
    int i;

    FILE *ARQUIVO_DE_SAIDA = fopen("saida.txt", "w");
    if(ARQUIVO_DE_SAIDA == NULL)
    {
        printf("Arquivo de saida nao abriu!\n");
        exit(1);
    }

    //leitura dos bytes
    while(fread(&byte, sizeof(unsigned char), 1, arquivo))
    {
        // fazer o surf pela arvore
        for(i=7 ; i>-1 ; i--)
        {
            if(ehBitUm(byte, i))
            {
                aux = retornaDir(aux);
            }
            else
            {
                aux = retornaEsq(aux);
            }
            //achou uma folha
            if(retornaEsq(aux) == NULL && retornaDir(aux) == NULL)
            {
                fprintf(ARQUIVO_DE_SAIDA, "%c", retornaLetra(aux));
                aux = arv;
            }
        }
    }

    liberaArvore(arv);
    fclose(arquivo);
    fclose(ARQUIVO_DE_SAIDA);
}

unsigned int ehBitUm(unsigned char byte, int i)
{
    unsigned char mascara = (1 << i);
    return byte & mascara;
}



/*
-----------------------------
-----------------------------
CODIGOS NAO UTILIZADOS
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