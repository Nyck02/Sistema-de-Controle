#include <stdio.h>
#include <ncurses.h>
#include "pedido.h"
#include "produto.h"
#include "cliente.h" 
#include <stdlib.h>
#include <string.h>



// Vetor de pedidos mantido em memória
Pedido listaPedidos[MAX_PEDIDOS];
int qtdPedidos = 0;

// Função para analisar/buscar um cliente por ID
static Cliente* analisarCliente(int id) {
    // Esta função deve consultar a lista de clientes
    // Por enquanto, retorna NULL como placeholder
    return NULL;
}

// Função para analisar/buscar um produto por ID
static Produto* analisarProduto(int id) {
    // Esta função deve consultar a lista de produtos
    // Por enquanto, retorna NULL como placeholder
    return NULL;
}

// Procura um pedido pelo ID e retorna a posição dele
 int encontrarPedidoPorId(int id) {
    for (int i = 0; i < qtdPedidos; i++) {
        if (listaPedidos[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Gera um ID novo que não esteja sendo usado
 int gerarNovoIdPedido() {
    int id = 1;
    while (encontrarPedidoPorId(id) != -1) {
        id++;
    }
    return id;
}
// Cadastrar um novo pedido
void inserirPedido() {
    clear();
    box(stdscr, 0, 0);
    if (qtdPedidos >= MAX_PEDIDOS) {
        mvprintw(0, 0, "Limite de pedidos atingido. Pressione qualquer tecla...");
        getch();
        return;
    }

    Pedido novo;
    novo.id = gerarNovoIdPedido();
    novo.qtdItens = 0;
    novo.total = 0;

    echo();

    mvprintw(0, 0, "--- Novo Pedido (ID %d) ---", novo.id);
    mvprintw(2, 0, "ID do cliente: ");
    scanw("%d", &novo.clienteId);

    // Verifica se o cliente existe
    if (analisarCliente(novo.clienteId) == NULL) {
        mvprintw(4, 0, "Cliente nao encontrado. Pressione qualquer tecla...");
        getch();
        return;
    }

    mvprintw(3, 0, "Data (dd/mm/aaaa): ");
    getstr(novo.data);

    mvprintw(5, 0, "--- Adicionar Itens ---");

    char continuar = 's';
    int linha = 7;

    do {
        if (novo.qtdItens >= MAX_ITENS_POR_PEDIDO) {
            mvprintw(linha, 0, "Limite de itens atingido.");
            getch();
            break;
        }

        int prodId, qtd;

        mvprintw(linha, 0, "ID do produto: ");
        scanw("%d", &prodId);

        Produto *p = analisarProduto(prodId);

        if (p == NULL) {
            mvprintw(linha + 1, 0, "Produto nao encontrado.");
        } 
        else if (p->estoque <= 0) {
            mvprintw(linha + 1, 0, "Produto sem estoque.");
        } 
        else {
            mvprintw(linha + 1, 0, "Produto: %s | Preco: %.2f | Estoque: %d",
                     p->descricao, p->preco, p->estoque);

            mvprintw(linha + 2, 0, "Quantidade: ");
            scanw("%d", &qtd);

            if (qtd <= 0) {
                mvprintw(linha + 3, 0, "Quantidade invalida.");
            } 
            else if (qtd > p->estoque) {
                mvprintw(linha + 3, 0, "Estoque insuficiente.");
            } 
            else {
                int idx = novo.qtdItens;

                novo.itens[idx].pedidoId   = novo.id;
                novo.itens[idx].produtoId  = p->id;
                novo.itens[idx].quantidade = qtd;
                novo.itens[idx].subtotal   = qtd * p->preco;

                novo.total += novo.itens[idx].subtotal;
                novo.qtdItens++;

                p->estoque -= qtd; // Atualiza estoque

                mvprintw(linha + 3, 0, "Item adicionado! Subtotal: %.2f", novo.itens[idx].subtotal);
            }
        }

        mvprintw(linha + 5, 0, "Adicionar outro item? (s/n): ");
        scanw(" %c", &continuar);

        // Limpa a área dos itens
        for (int i = 0; i < 6; i++) {
            move(linha + i, 0);
            clrtoeol();
        }

    } while (continuar == 's' || continuar == 'S');

    noecho();

    if (novo.qtdItens > 0) {
        listaPedidos[qtdPedidos] = novo;
        qtdPedidos++;
        mvprintw(linha, 0, "Pedido salvo! Total: %.2f", novo.total);
    } else {
        mvprintw(linha, 0, "Nenhum item adicionado. Cancelado.");
    }

    getch();
}

// Mostra todos os pedidos cadastrados
void listarPedidos() {
    clear();
    box(stdscr, 0, 0);
    if (qtdPedidos == 0) {
        mvprintw(0, 0, "Nenhum pedido cadastrado.");
        getch();
        return;
    }

    mvprintw(0, 0, "--- Lista de Pedidos ---");

    for (int i = 0; i < qtdPedidos; i++) {
        mvprintw(i + 2, 0,
                 "ID: %d | Cliente: %d | Data: %s | Total: %.2f | Itens: %d",
                 listaPedidos[i].id,
                 listaPedidos[i].clienteId,
                 listaPedidos[i].data,
                 listaPedidos[i].total,
                 listaPedidos[i].qtdItens);
    }

    mvprintw(qtdPedidos + 3, 0, "Pressione qualquer tecla...");
    getch();
}

// Consulta um pedido pelo ID
void consultarPedido() {
    clear();
    echo();
    box(stdscr, 0, 0);
    int id;
    mvprintw(0, 0, "ID do pedido: ");
    scanw("%d", &id);

    noecho();

    int pos = encontrarPedidoPorId(id);

    if (pos == -1) {
        mvprintw(2, 0, "Pedido nao encontrado.");
        getch();
        return;
    }

    Pedido p = listaPedidos[pos];

    mvprintw(2, 0, "--- Pedido %d ---", p.id);
    mvprintw(3, 0, "Cliente: %d", p.clienteId);
    mvprintw(4, 0, "Data: %s", p.data);
    mvprintw(5, 0, "Total: %.2f", p.total);
    mvprintw(6, 0, "Itens: %d", p.qtdItens);

    if (p.qtdItens > 0) {
        mvprintw(8, 0, "--- Itens ---");
        for (int i = 0; i < p.qtdItens; i++) {
            mvprintw(9 + i, 2,
                     "Produto %d | Qtd: %d | Subtotal: %.2f",
                     p.itens[i].produtoId,
                     p.itens[i].quantidade,
                     p.itens[i].subtotal);
        }
    }

    mvprintw(p.qtdItens + 11, 0, "Pressione qualquer tecla...");
    getch();
}

// Remove um pedido
void removerPedido() {
    clear();
    echo();
    box(stdscr, 0, 0);
    int id;
    mvprintw(0, 0, "ID do pedido para remover: ");
    scanw("%d", &id);

    noecho();

    int pos = encontrarPedidoPorId(id);

    if (pos == -1) {
        mvprintw(2, 0, "Pedido nao encontrado.");
        getch();
        return;
    }

    mvprintw(2, 0, "Remover pedido %d? (s/n): ", id);
    char c = getch();

    if (c != 's' && c != 'S') {
        mvprintw(4, 0, "Cancelado.");
        getch();
        return;
    }

    // Move os pedidos da frente pra trás
    for (int i = pos; i < qtdPedidos - 1; i++) {
        listaPedidos[i] = listaPedidos[i + 1];
    }

    qtdPedidos--;

    mvprintw(4, 0, "Pedido removido.");
    getch();
}

// Salvar pedidos e itens em CSV
void salvarPedidosCSV() {
    FILE *fp = fopen("data/Pedidos.csv", "w");
    FILE *fi = fopen("data/ItensPedido.csv", "w");

    if (!fp || !fi) {
        mvprintw(0, 0, "Erro ao salvar arquivos.");
        getch();
        return;
    }

    fprintf(fp, "id,clienteId,data,total\n");
    fprintf(fi, "pedidoId,produtoId,quantidade,subtotal\n");

    for (int i = 0; i < qtdPedidos; i++) {
        Pedido p = listaPedidos[i];

        fprintf(fp, "%d,%d,%s,%.2f\n",
                p.id, p.clienteId, p.data, p.total);

        for (int j = 0; j < p.qtdItens; j++) {
            ItemPedido it = p.itens[j];

            fprintf(fi, "%d,%d,%d,%.2f\n",
                    it.pedidoId, it.produtoId, it.quantidade, it.subtotal);
        }
    }

    fclose(fp);
    fclose(fi);

    mvprintw(0, 0, "Dados salvos.");
    getch();
}

// Carregar pedidos e itens dos arquivos CSV
void carregarPedidosCSV() {
    char linha[512];
    qtdPedidos = 0;

    FILE *fp = fopen("data/Pedidos.csv", "r");
    if (!fp) return;

    fgets(linha, sizeof(linha), fp); // pula cabeçalho

    while (fgets(linha, sizeof(linha), fp) && qtdPedidos < MAX_PEDIDOS) {
        Pedido p;
        sscanf(linha, "%d,%d,%[^,],%lf",
               &p.id, &p.clienteId, p.data, &p.total);

        p.qtdItens = 0;

        listaPedidos[qtdPedidos] = p;
        qtdPedidos++;
    }
    fclose(fp);

    FILE *fi = fopen("data/ItensPedido.csv", "r");
    if (!fi) return;

    fgets(linha, sizeof(linha), fi);

    while (fgets(linha, sizeof(linha), fi)) {
        ItemPedido it;
        sscanf(linha, "%d,%d,%d,%lf",
               &it.pedidoId, &it.produtoId, &it.quantidade, &it.subtotal);

        int idx = encontrarPedidoPorId(it.pedidoId);

        if (idx != -1) {
            Pedido *p = &listaPedidos[idx];

            if (p->qtdItens < MAX_ITENS_POR_PEDIDO) {
                p->itens[p->qtdItens] = it;
                p->qtdItens++;
            }
        }
    }

    fclose(fi);
}

// Função para analisar os pedidos carregados
void analisarPedido(int id) {
    clear();
    box(stdscr, 0, 0);
    // Procura o pedido
    int pos = encontrarPedidoPorId(id);

    if (pos == -1) {
        mvprintw(2, 0, "Pedido não encontrado.");
        getch();
        return;
    }

    Pedido p = listaPedidos[pos];

    mvprintw(2, 0, "--- ANALISE DO PEDIDO ---");
    mvprintw(3, 0, "ID do pedido: %d", p.id);
    mvprintw(4, 0, "Cliente: %d", p.clienteId);
    mvprintw(5, 0, "Data: %s", p.data);
    mvprintw(6, 0, "Total: R$ %.2f", p.total);
    mvprintw(7, 0, "Itens: %d", p.qtdItens);

    // Exibe itens
    if (p.qtdItens > 0) {
        mvprintw(9, 0, "--- Itens ---");
        for (int i = 0; i < p.qtdItens; i++) {
            mvprintw(10 + i, 2,
                "Produto %d | Qtd: %d | Subtotal: R$ %.2f",
                p.itens[i].produtoId,
                p.itens[i].quantidade,
                p.itens[i].subtotal
            );
        }
    } else {
        mvprintw(9, 0, "Nenhum item neste pedido.");
    }

    mvprintw(p.qtdItens + 12, 0, "Pressione qualquer tecla...");
    getch();
}

