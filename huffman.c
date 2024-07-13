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
        for(int i=0; i<MAX_CHAR; i++){ //Incrementa o vetor de acordo com a letra lida correspondende ao código ASCII que é seu índice
            if(i == n) V[i]++;
        }
    }

    tLista* lista = inicializaLista();

    for (int i=0; i<MAX_CHAR; i++){ //Cria arvores com um só nó nas posições do vetor que representam uma letra do texto
        if(V[i] != 0){
            tArvore* arv = abb_cria();
            arv = abb_insere(arv, i, V[i], NULL, NULL);
            insereCelulaNaLista(arv, lista);
        }
    }

    imprimeLista(lista);
    printf("\n\n");

    while(listaUnica(lista) == 0){ //Enquanto houver mais de um elemento na lista cria mais uma árvore que absorve as duas primeiras
        int peso_tr = retornaPeso(retornaPrimeiraArv(lista)) + retornaPeso(retornaSegundaArv(lista));

        tArvore* t3 = abb_cria();
        t3 = abb_insere(t3, '\0', peso_tr, retornaPrimeiraArv(lista), retornaSegundaArv(lista));
        insereCelulaNaLista(t3, lista);
        
        //Retira os dois primeiros elementos da lista
        retiraItem(lista, retornaPrimeiraArv(lista)); 
        retiraItem(lista, retornaPrimeiraArv(lista));

        imprimeLista(lista);
        printf("\n\n");
    }

    liberaLista(lista);

    fclose(file_pointer);

    return 0;
}