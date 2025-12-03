#ifndef PEDIDO_H
#define PEDIDO_H

// Quantidades máximas
#define MAX_PEDIDOS 1000
#define MAX_ITENS_POR_PEDIDO 50

// Estrutura de Item do Pedido
typedef struct {
    int pedidoId;      // ID do pedido
    int produtoId;     // ID do produto
    int quantidade;    // Quantidade comprada
    double subtotal;   // subtotal = quantidade * preço
} ItemPedido;

// Estrutura de Pedido
typedef struct {
    int id;                           // ID do pedido
    int clienteId;                    // ID do cliente
    char data[11];                    // dd/mm/aaaa
    double total;                     // soma dos itens
    int qtdItens;                     // itens cadastrados
    ItemPedido itens[MAX_ITENS_POR_PEDIDO];
} Pedido;

// Lista de pedidos (vem do pedido.c)
extern Pedido listaPedidos[MAX_PEDIDOS];
extern int totalPedidos;


// Funções do módulo Pedido
int gerarIdPedido();
<<<<<<< HEAD
int analisarPedido();
=======
void analisarPedido(int id);
>>>>>>> d8b7bdc848c7690e638373b5df9f08bb0716444b
void inserirPedido();
void removerPedido();
void consultarPedido();
void listarPedidos();
void cadastrarItemPedido(int pedidoId, int produtoId, int quantidade, double preco);
double calcularTotalPedido(Pedido *p);
void detalharPedido(Pedido *p);
void carregarPedidosCSV();
void salvarPedidosCSV();

#endif
