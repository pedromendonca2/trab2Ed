//em ordem crescente (oq menos pro que mais apareceu, um nó pra cada pra cada um)

//transformar string em vetor de char
//quicksort no vetor

#include "lista.h"

#define MAX_CHAR 256

int main(){

    unsigned char n;
    int V[256];

    for(int i=0; i<MAX_CHAR; i++){
        V[i] = 0;
    }

    FILE *file_pointer = fopen("./texto_1.txt", "r");
    if (file_pointer == NULL)
    {
        printf("Arquivo nao foi aberto corretamente\n");
        exit(1);
    }

    while(fscanf(file_pointer, "%c", &n) == 1){
        for(int i=0; i<MAX_CHAR; i++){
            if(i == n) V[i]++;
        }
    }

    tLista* lista = inicializaLista();

    for (int i=0; i<MAX_CHAR; i++)
    {
        if(V[i] != 0){
            tArvore* arv = abb_cria();
            arv = abb_insere(arv, i, V[i]);
            insereCelulaNaLista(arv, lista);
        }
    }
    
    imprimeLista(lista);

    liberaLista(lista);

    fclose(file_pointer);

    return 0;
}