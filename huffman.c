#include "lista.h"

#define MAX_CHAR 256
#define BUFFER_SIZE 1024 // Tamanho do buffer para leitura com fread

int main(int argc, char **argv){
    if(argc < 2)
    {
        printf("Arquivo de string de texto esta faltando\n");
        exit(2);
    }
    unsigned char buffer[BUFFER_SIZE];
    int V[MAX_CHAR] = {0}; //Inicializa todas as posicoes do vetor com zero
    unsigned char filepath[2048];
    strcpy(filepath, argv[1]);
    FILE *file_pointer = fopen(filepath, "rb");
    if (file_pointer == NULL)
    {
        printf("Arquivo nao foi aberto corretamente\n");
        exit(1);
    }

    /* le caracter por caracter */
    size_t bytesRead;
    while((bytesRead = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, file_pointer)) > 0){ //Enquanto le um char (um byte) ele continua
        for(size_t i=0; i<bytesRead; i++){ 
            V[buffer[i]]++; //Incrementa o vetor de acordo com a letra lida correspondende ao codigo ASCII que eh seu indice
        }
    }

    /* Ordena a lista de caracteres de modo crescente*/
    tLista* lista = inicializaLista();
    int numLeaves = 0;

    for (int i=0; i<MAX_CHAR; i++){ //Cria arvores com um soh noh nas posicoes do vetor que representam uma letra do texto
        if(V[i] != 0){
            //printf("letra e peso: %c e %d\n", i, V[i]);
            tArvore* arv = abb_cria();
            arv = abb_insere(arv, i, V[i], NULL, NULL);
            insereCelulaNaLista(arv, lista);
            numLeaves++;
        }
    }
    fclose(file_pointer);

    tArvore *huffman = retornaHuffman(lista);
    char **caminhos = allocaCaminhosParaLetra(alturaDaArvore(huffman)+1);//falta liberar isso aqui
    fazOsCaminhos(caminhos, alturaDaArvore(huffman) + 1, "", huffman);
    arquivoBinarioEmString(caminhos, filepath);
    compactado(huffman);
    liberaCaminhos(caminhos);
    liberaLista(lista);
    liberaArvore(huffman);
    return 0;
}