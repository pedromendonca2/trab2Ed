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
    unsigned char letra; // Caractere
    char* binario; // Representação binária do caractere
};

tLista* inicializaLista(){
    tLista* lista = malloc(sizeof(tLista));
    lista->primeiro = NULL;
    lista->ultimo = NULL;

    return lista;
}


// Função para criar a tabela de códigos (tabela de mapeamento de caracteres)
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

// Ordena lista para que sua ordem necessariamente seja do caracter de menor para o de maior peso
void encontraLugarNaLista(tArvore* arv, tLista* lista){
    tCelula* aux = lista->primeiro;
    tCelula* novo = malloc(sizeof(tCelula));

    if(retornaPeso(arv) <= retornaPeso(aux->arv)){
        novo->arv = arv;
        novo->prox = aux;
        lista->primeiro = novo;
    } else{
        while(aux->prox != NULL && retornaPeso(arv) > retornaPeso(aux->prox->arv)){
            aux = aux->prox;
        }
        novo->arv = arv;
        novo->prox = aux->prox;
        aux->prox = novo;
    }
}

// Insere uma nova célula na lista de forma ordenada
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
    } else{ // Caso de o peso do caracter em questao for menor do que o antecedente
        encontraLugarNaLista(arv, lista);
    }
}

void retiraItem(tLista* lista, tArvore* arv){
    tCelula* ant = NULL;
    tCelula* p = lista->primeiro;

    while(p != NULL && p->arv != arv){ // Procura a célula a ser removida
        ant = p;
        p = p->prox;
    }

    if(p == NULL) return;

    if(p == lista->primeiro && p == lista->ultimo){ // Se for o único elemento
        lista->primeiro = lista->ultimo = NULL;
        free(p);
        return; 
    }

    if(p == lista->ultimo){ // Se for o último elemento
        lista->ultimo = ant; 
        ant->prox = NULL; 
        free(p);
        return;
    }

    if(p == lista->primeiro){ // Se for o primeiro elemento
        lista->primeiro = p->prox;    
    } else{ // Se estiver no meio
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
void arquivoBinarioEmString(char **registroDeCaminhos, const char *filepath)
{
    FILE *arquivo_texto = fopen(filepath, "r");
    if(arquivo_texto == NULL)
    {
        printf("arquivo texto nao abriu\n");
        exit(1);
    }
    FILE *arquivo_binario_string = fopen("stringbinario.txt", "w"); // Abre o arquivo onde a string binária será escrita
    if(arquivo_binario_string == NULL)
    {
        printf("Arquivo texto em binario abriu\n");
        exit(0);
    }
    unsigned char c;
    while(fscanf(arquivo_texto,"%c", &c) == 1)
    {
        fprintf(arquivo_binario_string, "%s", registroDeCaminhos[c]); // Escreve a representação binária do caractere no arquivo de saída
    }
    fclose(arquivo_binario_string);
    fclose(arquivo_texto);
}

// compactar o arquivo em bytes
void compactado(tArvore* huffman, const char* nomeArquivo)
{
    // Criar uma string para o nome do arquivo de saída
    char nomeArquivoCompactado[1024];
    snprintf(nomeArquivoCompactado, sizeof(nomeArquivoCompactado), "%s.comp", nomeArquivo);

    FILE *arquivo = fopen(nomeArquivoCompactado, "wb");
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

    //Salvar o numero de bytes e de bits no ultimo byte
    FILE *arquivo3 = fopen("numero.bin", "wb");
    if(arquivo3 == NULL){
        printf("numero.bin nao foi aberto para escrita\n");
        exit(0);
    }

    //Guarda os bits em bytes
    int j = 7;
    unsigned char byte = 0, base, letra;
    long unsigned int n = 0;
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
            n++;
        }
    }
    // se algum byte em formação nao foi colocado no binario
    if(j != 7)
    {
        fwrite(&byte, sizeof(unsigned char), 1, arquivo);
    }
    fwrite(&n, sizeof(long unsigned int), 1, arquivo3);
    fwrite(&j, sizeof(int), 1, arquivo3);
    fclose(arquivo);
    fclose(arquivo2);
    fclose(arquivo3);
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

void descompactar(const char* nomeArquivo)
{
    // Criar uma string para o nome do arquivo de saída
    char nomeArquivoCompactado[1024];

    // Copiar nomeArquivo para nomeArquivoCompactado
    strncpy(nomeArquivoCompactado, nomeArquivo, sizeof(nomeArquivoCompactado) - 1);
    nomeArquivoCompactado[sizeof(nomeArquivoCompactado) - 1] = '\0'; // Garantir terminação

    // Remover ".comp" do final, se presente
    char *posicaoComp = strstr(nomeArquivoCompactado, ".comp");
    if (posicaoComp != NULL && posicaoComp == (nomeArquivoCompactado + strlen(nomeArquivoCompactado) - 5)) {
        *posicaoComp = '\0';
    }
    
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL)
    {
        printf("Arquivo de descompactacao nao abriu!\n");
        exit(1);
    }

    // Arquivo de recuperar numero de bytes e de bits no ultimo byte
    FILE *arquivo2 = fopen("numero.bin", "rb");
    if(arquivo2 == NULL)
    {
        printf("Arquivo de recuperar numero de bytes nao foi aberto");
        exit(1);
    }

    // Recuperar a árvore de Huffman do início do arquivo binário
    tArvore *arv = recuperaArvore(arquivo);
    tArvore *aux = arv;
    unsigned char byte;
    int i, numeroDeBitsNoUltimoByte;
    long unsigned int numeroDeBytes;
    fread(&numeroDeBytes, sizeof(long unsigned int), 1, arquivo2);
    fread(&numeroDeBitsNoUltimoByte, sizeof(int), 1, arquivo2);

    FILE *ARQUIVO_DE_SAIDA = fopen(nomeArquivoCompactado, "w");
    if(ARQUIVO_DE_SAIDA == NULL)
    {
        printf("Arquivo de saida nao abriu!\n");
        exit(1);
    }

    long unsigned int bytes = 0;
    int sensor=0;
    //leitura dos bytes
    while(fread(&byte, sizeof(unsigned char), 1, arquivo))
    {
        // fazer o surf pela arvore
        for(i=7 ; i>-1 ; i--)
        {
            if(bytes == numeroDeBytes && i == numeroDeBitsNoUltimoByte)
            {
                break;
                sensor = 1;
            }
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
        if(sensor == 1)
        {
            break;
        }
        bytes++;
    }

    liberaArvore(arv);
    fclose(arquivo);
    fclose(ARQUIVO_DE_SAIDA);
}

// Função para verificar se o i-ésimo bit de um byte é 1
unsigned int ehBitUm(unsigned char byte, int i)
{
    unsigned char mascara = (1 << i); // Cria uma máscara com o bit i setado para 1
    return byte & mascara; // Retorna o resultado da operação AND bit a bit entre o byte e a máscara
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