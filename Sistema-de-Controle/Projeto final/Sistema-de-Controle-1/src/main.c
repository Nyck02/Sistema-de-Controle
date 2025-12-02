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
     
int codigo;

    struct produto *p;
    p = malloc(sizeof(struct produto));


Produto novo_produto;

// Cadastro do produto
printf("Digite o codigo do produto: ");
scanf ("%d", &novo_id);
//Verificação
//Chamando a função para analisar 
AnalisarProduto(novo_id);
//Se retornar 1 o codigo já existe
printf("ERRO: O código já está cadastrado no sistema, tente outro: ");
//Retornar para o menu produto
MostrarMenuProduto();

// Se não retornou 1 o codigo não existe e está liberado para cadastro
//chamando a função de cadastro
cadastro(novo_id);
//Botão "cadastrar" clicado
printf("O produto %d foi cadastrado com sucesso!\n", novo_produto.id); //confirmar exatamente que o produto x foi cadastrado
//Botão sair 
MostrarMenuPrincipal();


//Listamento dos produtos
ListarProdutos();

//Botão sair 
MostrarMenuPrincipal();


//Consultar um produto (apenas leitura)

printf("Digite o código do produto: "); //Não deveria ser o nome? 
scanf("%d", &codigo);
ConsultarProdutos(codigo);

//Botão sair 
MostrarMenuPrincipal();

//Editar produto
printf("Digite o código do produto: ");
scanf("%d", &codigo);
EditarProduto(codigo);

//Remover produto 
printf("Digite o código do produto: "); 
scanf("%d", &codigo);
RemoverProduto(codigo);

//Botão sair 
MostrarMenuPrincipal();

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
            return; // Sair do programa
    }
}

int main() {
    printf("Projeto SCP iniciado com sucesso!\n");
    return 0;
}
