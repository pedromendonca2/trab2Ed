#include "lista.h"

// Função principal para descompressão
int main(int argc, char **argv){

    if(argc < 2)
    {
        printf("Arquivo de string de texto esta faltando\n");
        exit(2);
    }

    const char *filepath = argv[1];

    FILE *file_pointer = fopen(filepath, "rb");
    if (file_pointer == NULL)
    {
        printf("Arquivo nao foi aberto corretamente\n");
        exit(1);
    }

    descompactar(filepath); // Chama a função de descompactação

    fclose(file_pointer);
    return 0;
}