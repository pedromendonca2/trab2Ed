#ifndef lista_h
#define lista_h

typedef struct celula tCelula;
typedef struct lista tLista;

#include "arvoreBinariaBusca.h"

tCelula* liberaCelula(tCelula* cel);

tLista* inicializaLista();

void insereCelulaNaLista(tArvore* arv, tLista* lista);

void retiraItem(tLista* lista, char letra);

void imprimeLista(tLista* lista);

void liberaLista(tLista* lista);

#endif
