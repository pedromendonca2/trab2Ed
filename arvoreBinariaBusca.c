#include "arvoreBinariaBusca.h"

struct arv
{
    unsigned char letra;
    int peso;
    tArvore *esq, *dir ;
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
        printf("LETRA:%cPESO:%d\n", a->letra, a->peso);
        abb_imprime(a->dir);
    }
}

tArvore *abb_insere(tArvore *a, char letra, int peso, tArvore* t1, tArvore* t2)
{

    a = (tArvore *)malloc(sizeof(tArvore));
    a->letra = letra;
    a->peso = peso;
    a->esq = t1;
    a->dir = t2;

    return a;
}

unsigned char retornaLetra(tArvore* r){
    return r->letra;
}

int retornaPeso(tArvore* r){
    if(r == NULL){
        printf("Um abraco\n");
        exit(1);
    }
    return r->peso;
}

void liberaArvore(tArvore* r)
{
    if(r!=NULL){
        liberaArvore(r->esq);
        liberaArvore(r->dir);
        free(r);
    }
}

void imprimeNosFolha(tArvore *raiz, int altura){
    if(raiz == NULL) return;
    if(raiz->esq == NULL && raiz->dir == NULL){
        printf("%c %d\n", raiz->letra, altura);
    }
    else{
        imprimeNosFolha(raiz->esq, altura+1);
        imprimeNosFolha(raiz->dir, altura +1);
    }
}

int alturaDaArvore(tArvore *raiz){
    int esq, dir;
    if( raiz == NULL) return -1;
    else{
        esq = alturaDaArvore(raiz->esq) + 1;
        dir = alturaDaArvore(raiz->dir) +1;
    }
    if(dir>esq) return dir;
    return esq;
}

//armazena a arvore em binario
void armazenaArvore(tArvore *raiz, FILE *file) {
    if (raiz == NULL) {
        unsigned char flag = 0;
        fwrite(&flag, sizeof(unsigned char), 1, file);
    } else {
        unsigned char flag = 1;
        fwrite(&flag, sizeof(unsigned char), 1, file);

        unsigned char letra = retornaLetra(raiz);
        fwrite(&letra, sizeof(unsigned char), 1, file);
        
        armazenaArvore(raiz->esq, file);
        armazenaArvore(raiz->dir, file);
    }
}

tArvore *recuperaArvore(FILE *arquivo) {
    unsigned char flag;
    fread(&flag, sizeof(unsigned char), 1, arquivo);

    if (flag == 0) {
        return NULL;
    }

    unsigned char letra;
    fread(&letra, sizeof(unsigned char), 1, arquivo);

    tArvore *esq = recuperaArvore(arquivo);
    tArvore *dir = recuperaArvore(arquivo);

    return abb_insere(NULL, letra, 0, esq, dir); // Assumindo peso 0 ao reconstruir
}

tArvore *retornaEsq(tArvore *a)
{
    return a->esq;
}

tArvore *retornaDir(tArvore *a)
{
    return a->dir;
}

int ehFolha(tArvore *a)
{
    if(a->dir == NULL && a->esq == NULL) return 1;
    return 0;
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



