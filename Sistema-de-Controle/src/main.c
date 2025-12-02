#include <ncurses.h>
#include "interface.h"
#include "produto.h"

int main() {
    // 1. INICIALIZAÇÃO OBRIGATÓRIA (O "Motor de Partida")
    initscr();              // Liga a tela
    cbreak();               // Leitura rápida de teclas
    noecho();               // Não imprime o que digita
    curs_set(0);            // Esconde cursor
    keypad(stdscr, TRUE);   // Habilita setas

    // Inicializa o banco de dados (Importante!)
    InicializarProdutos(); 

    // 2. CHAMA O SISTEMA
    MenuPrincipal();

    // 3. DESLIGA TUDO
    endwin();
    return 0;
}