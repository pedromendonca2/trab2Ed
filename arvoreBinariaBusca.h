#ifndef arvoreBinariaBusca_h
#define arvoreBinariaBusca_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arv tArvore;

tArvore *abb_cria(void);

void abb_imprime(tArvore *a);

tArvore *abb_busca(tArvore *r, int v);

tArvore *abb_insere(tArvore *a, char letra, int peso);

tArvore *abb_retira(tArvore *r, char letra, int peso);

char retornaLetra(tArvore* r);

int retornaPeso(tArvore* r);

void liberaArvore(tArvore* r);

#endif