#include "lista.h"
#include <string.h>

// Função principal para descompressão
int main(int argc, char **argv){

    if(argc < 2)
    {
        printf("Arquivo de entrada.comp esta faltando\n");
        exit(2);
    }

    const char *filepath = argv[1];

    FILE *file_pointer = fopen(filepath, "rb");
    if (file_pointer == NULL)
    {
        printf("Arquivo de entrada.comp nao foi aberto corretamente!\nTalvez voce tenha esquecido de compilar a entrada!\n");
        exit(1);
    }

    descompactar(filepath); // Chama a função de descompactação

    fclose(file_pointer);

    /*
    deletar os arquivos gerados anteriormente
    char comando[1024];
    sprintf(comando, "rm %s", argv[1]);
    system(comando); //remove o compilado usado para descompactar
    system("rm stringbinario.txt");
    system("rm numero.bin");
    */
    return 0;
}