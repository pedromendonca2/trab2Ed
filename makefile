# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic

# Nomes dos executáveis
TARGET1 = compacta
TARGET2 = descompacta

# Arquivos fonte
SRCS_COMMON = arvoreBinariaBusca.c lista.c
SRCS_MAIN = compactador.c
SRCS_MAIN2 = descompactador.c

# Objetos intermediários
OBJS_COMMON = $(SRCS_COMMON:.c=.o)
OBJS_MAIN = $(SRCS_MAIN:.c=.o)
OBJS_MAIN2 = $(SRCS_MAIN2:.c=.o)

# Alvos
all: $(TARGET1) $(TARGET2)

# Compilação do executável principal
$(TARGET1): $(OBJS_COMMON) $(OBJS_MAIN)
	$(CC) $(CFLAGS) $^ -o $@

# Compilação do executável secundário
$(TARGET2): $(OBJS_COMMON) $(OBJS_MAIN2)
	$(CC) $(CFLAGS) $^ -o $@

# Regras para arquivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza de arquivos objeto e executáveis
clean:
	rm -f *.o $(TARGET1) $(TARGET2)
