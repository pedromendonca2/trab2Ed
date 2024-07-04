#ifndef arvoreBinariaBusca_h
#define arvoreBinariaBusca_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arv tArvore;

typedef struct{
    int peso;
} tLetra;

tArvore *abb_cria(void);

void abb_imprime(tArvore *a);

tArvore *abb_busca(tArvore *r, int v);

tArvore *abb_insere(tArvore *a, tLetra* l);

tArvore *abb_retira(tArvore *r, tLetra* l);

void liberaArvore(tArvore* r);

#endif