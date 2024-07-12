#ifndef lista_h
#define lista_h

typedef struct celula tCelula;
typedef struct lista tLista;

#include "arvoreBinariaBusca.h"

tCelula* liberaCelula(tCelula* cel);

tLista* inicializaLista();

void encontraLugarNaLista(tArvore* arv, tLista* lista);

void insereCelulaNaLista(tArvore* arv, tLista* lista);

void retiraItem(tLista* lista, tArvore* arv);

void imprimeLista(tLista* lista);

int listaUnica(tLista* l);

tArvore* retornaPrimeiraArv(tLista* l);

tArvore* retornaSegundaArv(tLista *l);

void liberaLista(tLista* lista);

#endif
