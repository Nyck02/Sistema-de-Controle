// main.c - entrada do programa
#include <stdio.h>
#include <ncurses.h>

// protótipos de menus de módulos (implementados em outros arquivos)
void mostrarMenuClientes();
void mostrarMenuProdutos();
void mostrarMenuPedidos();

// Stubs temporários para evitar erros de ligação; implementar módulos reais depois.
void mostrarMenuClientes() {
    // TODO: implementar o menu de clientes (ncurses)
}

void mostrarMenuProdutos() {
    // TODO: implementar o menu de produtos (ncurses)
}

void mostrarMenuPrincipal() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int opcao = 0;
    int selecionado = 0;
    const char *opcoes[] = {
        "1. Manter Clientes",
        "2. Manter Produtos",
        "3. Manter Pedidos",
        "4. Sair"
    };
    int total = 4;

    while (1) {
        clear();
        attron(A_BOLD);
        mvprintw(2, 10, "SISTEMA DE CONTROLE DE PEDIDOS (SCP)");
        attroff(A_BOLD);

        for (int i = 0; i < total; i++) {
            if (i == selecionado) {
                attron(A_REVERSE);
                mvprintw(5 + i, 10, "%s", opcoes[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(5 + i, 10, "%s", opcoes[i]);
            }
        }

        mvprintw(10, 10, "Use ↑/↓ para navegar e Enter para selecionar.");
        refresh();

        int tecla = getch();

        switch (tecla) {
            case KEY_UP:
                selecionado = (selecionado == 0) ? total - 1 : selecionado - 1;
                break;
            case KEY_DOWN:
                selecionado = (selecionado == total - 1) ? 0 : selecionado + 1;
                break;
            case 10: // Enter
                opcao = selecionado + 1;
                goto fim_loop;
            case 'q':
            case 'Q':
                opcao = 4;
                goto fim_loop;
        }
    }

fim_loop:
    endwin();

    switch (opcao) {
        case 1:
            mostrarMenuClientes();
            break;
        case 2:
            mostrarMenuProdutos();
            break;
        case 3:
            mostrarMenuPedidos();
            break;
        case 4:
            return; // Sai do programa
    }
}

int main() {
    mostrarMenuPrincipal();
    return 0;
}