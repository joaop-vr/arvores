# Nome do compilador
CC = exec

# Opções de compilação
CFLAGS = -Wall -Wextra -std=c11

# Nome do executável
TARGET = arvore_binaria

# Arquivos fontes
SRC = arvore_binaria.c

# Regras principais
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Limpeza dos arquivos gerados
clean:
	rm -f $(TARGET)
