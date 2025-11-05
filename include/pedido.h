#ifndef PEDIDO_H
#define PEDIDO_H

// Definições de tamanho máximo para as estruturas
#define MAX_PEDIDOS 1000          // Número máximo de pedidos que podem ser armazenados
#define MAX_ITENS_POR_PEDIDO 50   // Número máximo de itens por pedido

/**
 * @struct ItemPedido
 * @brief Representa um item específico dentro de um pedido.
 */
typedef struct {
    int pedidoId;      // ID do pedido ao qual este item pertence
    int produtoId;     // ID do produto comprado neste item
    int quantidade;    // Quantidade deste produto no pedido
    double subtotal;   // Valor total deste item (quantidade * preço do produto)
} ItemPedido;

/**
 * @struct Pedido
 * @brief Representa uma ordem de compra feita por um cliente.
 */
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

#endif // PEDIDO_H

#ifndef PEDIDO_H
#define PEDIDO_H

// Definições de tamanho máximo para as estruturas
#define MAX_PEDIDOS 1000          // Número máximo de pedidos que podem ser armazenados
#define MAX_ITENS_POR_PEDIDO 50   // Número máximo de itens por pedido

/**
 * @struct ItemPedido
 * @brief Representa um item específico dentro de um pedido.
 * 
 * Esta struct é associativa e conecta o Pedido ao Produto.
 * Cada ItemPedido representa uma quantidade específica de um produto em um pedido.
 */
typedef struct {
    int pedidoId;      // ID do pedido ao qual este item pertence
    int produtoId;     // ID do produto comprado neste item
    int quantidade;    // Quantidade deste produto no pedido
    double subtotal;   // Valor total deste item (quantidade * preço do produto)
} ItemPedido;

/**
 * @struct Pedido
 * @brief Representa uma ordem de compra feita por um cliente.
 * 
 * Um pedido é composto por um ou mais itens (ItemPedido) e está ligado a um cliente.
 */
typedef struct {
    int id;                        // ID único do pedido (chave primária)
    int clienteId;                 // ID do cliente que fez o pedido (chave estrangeira para Cliente)
    char data[11];                 // Data do pedido no formato "dd/mm/aaaa" (10 caracteres + '\0')
    double total;                  // Valor total do pedido (soma dos subtotais de todos os itens)
    int qtdItens;                  // Quantidade atual de itens neste pedido
    ItemPedido itens[MAX_ITENS_POR_PEDIDO]; // Vetor de itens associados ao pedido
} Pedido;

// Declarações das funções (conforme cronograma e diagrama modular)
void inserirPedido();             // Cadastrar um novo pedido
void listarPedidos();             // Listar todos os pedidos cadastrados
void consultarPedido();           // Consultar um pedido pelo ID
void removerPedido();             // Remover um pedido e seus itens
void carregarPedidosCSV();        // Carregar pedidos do arquivo Pedidos.csv
void salvarPedidosCSV();          // Salvar pedidos no arquivo Pedidos.csv

#endif