# Nome do compilador
CC = gcc

# Opções de compilação
CFLAGS = -Wall -Wextra -std=c11

# Nome do executável
TARGET = exec

# Arquivos fontes
SRC = main.c avl.c fila.c menu.c

# Arquivos objeto
OBJ = $(SRC:.c=.o)

# Regras principais
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Regras para gerar arquivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJ) $(TARGET)
