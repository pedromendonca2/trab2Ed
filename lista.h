#ifndef lista_h
#define lista_h

typedef struct celula tCelula;
typedef struct lista tLista;
typedef struct tabela tTabela;

#include "arvoreBinariaBusca.h"

tLista* inicializaLista();

tTabela** criaTabela(tLista* lista, int num);

void encontraLugarNaLista(tArvore* arv, tLista* lista);

void insereCelulaNaLista(tArvore* arv, tLista* lista);

void retiraItem(tLista* lista, tArvore* arv);

void imprimeLista(tLista* lista);

int listaUnica(tLista* l);

tArvore* retornaPrimeiraArv(tLista* l);

tArvore* retornaSegundaArv(tLista *l);

char retornaLetraTab(tTabela* tab);

char* retornaBinarioTab(tTabela* tab);

void liberaTabela(tTabela** tab, int num);

void liberaLista(tLista* lista);

tCelula *retornaPrim(tLista *lista);

tArvore *removePrimeiroDaLista(tLista *lista);

tArvore *retornaHuffman(tLista *lista);

char **allocaCaminhosParaLetra(int altura_da_arvore);

void fazOsCaminhos(char **registroDeCaminhos, int alturaMaximaDaArvore, char *caminho, tArvore *raiz);

void imprimeOsCaminhos(char **registroDeCaminhos); // fazer testes

void arquivoBinarioEmString(char **registroDeCaminhos, const char *filepath);

void compactado(tArvore* huffman, const char* nomeArquivo);

void liberaCaminhos(char **caminhos);

void descompactar(const char* nomeArquivo);

unsigned int ehBitUm(unsigned char byte, int i);

#endif
