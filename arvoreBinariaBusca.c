#include "arvoreBinariaBusca.h"

struct arv
{
    char letra;
    int peso;
    tArvore *esq;
    tArvore *dir;
};

tArvore *abb_cria(void)
{
    return NULL;
}

void abb_imprime(tArvore *a)
{
    if (a != NULL)
    {
        abb_imprime(a->esq);
        printf("LETRA: %c\n", a->letra);
        abb_imprime(a->dir);
    }
}

// tArvore *abb_busca(tArvore *r, int v)
// {
//     if (r == NULL)
//         return NULL;
//     else if (retornaMatricula(r->a) > v)
//         return abb_busca(r->esq, v);
//     else if (retornaMatricula(r->a) < v)
//         return abb_busca(r->dir, v);
//     else
//         return r;
// }

tArvore *abb_insere(tArvore *a, char letra, int peso, tArvore* t1, tArvore* t2)
{
    if (a == NULL)
    {
        a = (tArvore *)malloc(sizeof(tArvore));
        a->letra = letra;
        a->peso = peso;
        a->esq = a->dir = NULL;
    }

    if(t1 != NULL && t2 != NULL){
        a->esq = t1;
        a->dir = t2;
    }

    return a;
}

char retornaLetra(tArvore* r){
    return r->letra;
}

int retornaPeso(tArvore* r){
    return r->peso;
}

void liberaArvore(tArvore* r)
{
    if(r!=NULL){
        //if(r->esq != NULL) abb_imprime(r->esq);
        //printf("\n\n");
        liberaArvore(r->esq);
        //if(r->dir != NULL) abb_imprime(r->dir);
        liberaArvore(r->dir);
        free(r);
    }
}

// tArvore *abb_retira(tArvore *r, char letra, int peso)
// {
//     if (r == NULL)
//         return NULL;
//     else if (retornaMatricula(r->a) > retornaMatricula(aluno))
//         r->esq = abb_retira(r->esq, aluno);
//     else if (retornaMatricula(r->a) < retornaMatricula(aluno))
//         r->dir = abb_retira(r->dir, aluno);

//     else
//     { /* achou o nó a remover */
//         /* nó sem filhos */
//         if (r->esq == NULL && r->dir == NULL)
//         {
//             free(r);
//             r = NULL;
//         }
//         /* nó só tem filho à direita */
//         else if (r->esq == NULL)
//         {
//             tArvore *t = r;
//             r = r->dir;
//             free(t);
//         }
//         /* só tem filho à esquerda */
//         else if (r->dir == NULL)
//         {
//             tArvore *t = r;
//             r = r->esq;
//             free(t);
//         }
//         /* nó tem os dois filhos */
//         else
//         {
//             tArvore *f = r->esq;
//             while (f->dir != NULL)
//             {
//                 f = f->dir;
//             }
//             r->a = f->a; /* troca as informações */
//             f->a = aluno;
//             r->esq = abb_retira(r->esq, aluno);
//         }
//     }
//     return r;
// }