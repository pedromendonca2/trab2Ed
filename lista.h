#ifndef lista_h
#define lista_h

typedef struct celula tCelula;
typedef struct lista tTipoLista;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tCelula* liberaCelula(tCelula* cel);

tTipoLista* inicializaLista();

void insereCelulaNaLista(char letra, int peso, tTipoLista* lista);

void retiraItem(tTipoLista* lista, int v);

void imprimeLista(tTipoLista* lista);

void liberaLista(tTipoLista* lista);

#endif
