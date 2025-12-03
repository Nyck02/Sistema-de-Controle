#include <ncurses.h>
#include "interface.h"
#include "produto.h"

int main() {
    // Partida
    initscr();              // Liga a tela
    cbreak();               // Leitura rapida de teclas
    noecho();               // Não imprime o que digita
    curs_set(0);            // Esconde cursor
    keypad(stdscr, TRUE);   // Habilita setas

    // Inicializa
    InicializarProdutos(); 

    MenuPrincipal();

    endwin();
    return 0;
}