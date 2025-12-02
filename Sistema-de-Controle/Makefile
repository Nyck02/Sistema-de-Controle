#============================================================
# Makefile — Sistema de Controle de Pedidos (SCP)
# Para uso no WSL/Ubuntu (Linux)
#============================================================

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LIBS = -lncurses
BUILD_DIR = build
SRC_DIR = src
EXEC = $(BUILD_DIR)/scp

# Lista todos os arquivos .c na pasta src/
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Regra principal: compila tudo
all: dirs $(EXEC)
	@echo "=============================================="
	@echo "Compilação concluída com sucesso!"
	@echo "=============================================="

# Cria a pasta 'build' se ela não existir
dirs:
	@mkdir -p $(BUILD_DIR)

# Compila cada arquivo .c em um .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Gera o executável final a partir dos objetos
$(EXEC): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXEC) $(LIBS)

# Limpa os arquivos compilados
clean:
	@rm -rf $(BUILD_DIR)
	@echo "Limpeza concluída."

# Compila e executa o programa
run: all
	@echo "Executando o Sistema de Controle de Pedidos..."
	@./$(EXEC)

# Mostra ajuda
help:
	@echo "=============================================="
	@echo "Comandos disponíveis:"
	@echo "  make      → compila o projeto"
	@echo "  make run  → compila e executa"
	@echo "  make clean → remove arquivos compilados"
	@echo "  make help  → mostra esta ajuda"
	@echo "=============================================="

.PHONY: all clean run help dirs
