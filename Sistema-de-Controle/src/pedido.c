#include <stdio.h>
#include <ncurses.h>
#include "pedido.h"
#include "produto.h"
#include "cliente.h" 
#include <stdlib.h>
#include <string.h>


// --- IMPLEMENTAÇÃO (STUBS) ---
// Estas funções existem apenas para o compilador não reclamar.
// O responsável pelo módulo "Pedidos" vai preencher isso depois.

// Vetor de pedidos mantido em memória
Pedido listaPedidos[MAX_PEDIDOS];
int qtdPedidos = 0;

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

void inserirPedido() {
    clear();

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

void listarPedidos() {
    // Futura implementação
}

void consultarPedido() {
    // Futura implementação
}

void removerPedido() {
    // Futura implementação
}

void carregarPedidosCSV() {
    // Futura implementação
}

void salvarPedidosCSV() {
    // Futura implementação

}
