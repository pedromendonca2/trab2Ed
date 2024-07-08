#ifndef lista_h
#define lista_h

typedef struct celula tCelula;
typedef struct lista tTipoLista;

#include "arvoreBinariaBusca.h"

tCelula* liberaCelula(tCelula* cel);

tTipoLista* inicializaLista();

void insereCelulaNaLista(tArvore* arv, tTipoLista* lista);

void retiraItem(tTipoLista* lista, char letra);

void imprimeLista(tTipoLista* lista);

void liberaLista(tTipoLista* lista);

#endif
