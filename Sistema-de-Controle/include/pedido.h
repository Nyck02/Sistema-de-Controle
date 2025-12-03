#ifndef PEDIDO_H
#define PEDIDO_H

#define MAX_PEDIDOS 1000          
#define MAX_ITENS_POR_PEDIDO 50   

//ItemPedido
typedef struct {
    int pedidoId;      // ID do pedido ao qual este item pertence
    int produtoId;     // ID do produto comprado neste item
    int quantidade;    // Quantidade deste produto no pedido
    double subtotal;   // Valor total deste item (quantidade * preço do produto)
} ItemPedido;

//Pedido
typedef struct {
    int id;                        // ID único do pedido (chave primária)
    int clienteId;                 // ID do cliente que fez o pedido (chave estrangeira para Cliente)
    char data[11];                 // Data do pedido no formato "dd/mm/aaaa"
    double total;                  // Valor total do pedido
    int qtdItens;                  // Quantidade atual de itens neste pedido
    ItemPedido itens[MAX_ITENS_POR_PEDIDO]; // Vetor de itens associados ao pedido
} Pedido;

//funções relacionadas a pedidos
void inserirPedido();           //Cadastra um novo pedido
void listarPedidos();           //Lista todos os pedidos cadastrados
void consultarPedido();          //Consulta um pedido pelo ID
void removerPedido();            //Remove um pedido e seus itens
void carregarPedidosCSV();       //Carrega pedidos do arquivo Pedidos.csv
void salvarPedidosCSV();         // Salva pedidos no arquivo
void analisarPedido();           //Analisa um pedido
void cadastrarItemPedido(int pedidoId, int produtoId, int quantidade, double preco);    //Cadastra um item no pedido

#endif
