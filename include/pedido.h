#ifndef PEDIDO_H
#define PEDIDO_H

// Definições de tamanho máximo para as estruturas
#define MAX_PEDIDOS 1000          // Número máximo de pedidos que podem ser armazenados
#define MAX_ITENS_POR_PEDIDO 50   // Número máximo de itens por pedido


typedef struct {
    int pedidoId;      // ID do pedido ao qual este item pertence
    int produtoId;     // ID do produto comprado neste item
    int quantidade;    // Quantidade deste produto no pedido
    double subtotal;   // Valor total deste item (quantidade * preço do produto)
} ItemPedido;

typedef struct {
    int id;                        // ID único do pedido (chave primária)
    int clienteId;                 // ID do cliente que fez o pedido (chave estrangeira para Cliente)
    char data[11];                 // Data do pedido no formato "dd/mm/aaaa"
    double total;                  // Valor total do pedido
    int qtdItens;                  // Quantidade atual de itens neste pedido
    ItemPedido itens[MAX_ITENS_POR_PEDIDO]; // Vetor de itens associados ao pedido
} Pedido;

// Declarações das funções relacionadas a pedidos
void inserirPedido();
void listarPedidos();
void consultarPedido();
void removerPedido();
void carregarPedidosCSV();
void salvarPedidosCSV();

#endif 