#include pedido.h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

// Lista global de pedidos
Pedido listaPedidos[MAX_PEDIDOS];
int qtdPedidos = 0; // Quantidade atual de pedidos cadastrados

// Função para encontrar um pedido pelo ID
int encontrarPedidoPorId(int id) {
    for (int i = 0; i < qtdPedidos; i++) {
        if (listaPedidos[i].id == id) {
            return i;
        }
    }
    return -1; // Pedido não encontrado
}

// Função para encontrar um pedido pelo clienteId
int encontrarPedidoPorClienteId(int clienteId) {
    for (int i = 0; i < qtdPedidos; i++) {
        if (listaPedidos[i].clienteId == clienteId) {
            return i;
        }
    }
    return -1; // Não encontrado
}

// Função para gerar um novo ID único para um pedido
int gerarNovoIdPedido() {
    int id = 1;
    while (encontrarPedidoPorId(id) != -1) {
        id++;
    }
    return id;
}

// Função para calcular o total do pedido com base nos itens
double calcularTotalPedido(Pedido *pedido) {
    double total = 0.0;
    for (int i = 0; i < pedido->qtdItens; i++) {
        total += pedido->itens[i].subtotal;
    }
    return total;
}

// Função para inserir um novo pedido (versão básica)
void inserirPedido() {
    if (qtdPedidos >= MAX_PEDIDOS) {
        printf("Erro: Limite máximo de pedidos atingido.\n");
        return;
    }

    Pedido novoPedido;
    novoPedido.id = gerarNovoIdPedido();
    novoPedido.qtdItens = 0;
    novoPedido.total = 0.0;

    // Simulando entrada de dados (em produção, seria via interface ncurses)
    printf("Informe o ID do cliente: ");
    scanf("%d", &novoPedido.clienteId);

    // Validar se o cliente existe (em produção, chamaria função de validação)
    if (encontrarPedidoPorClienteId(novoPedido.clienteId) == -1) {
        printf("Erro: Cliente com ID %d não encontrado.\n", novoPedido.clienteId);
        return;
    }

    // Obter data atual (simulação)
    strcpy(novoPedido.data, "15/11/2025");

    // Adicionar ao vetor
    listaPedidos[qtdPedidos] = novoPedido;
    qtdPedidos++;

    printf("Pedido cadastrado com sucesso! ID: %d\n", novoPedido.id);
}

// Função para listar todos os pedidos
void listarPedidos() {
    if (qtdPedidos == 0) {
        printf("Nenhum pedido cadastrado.\n");
        return;
    }

    printf("=== LISTA DE PEDIDOS ===\n");
    for (int i = 0; i < qtdPedidos; i++) {
        printf("ID: %d | Cliente: %d | Data: %s | Total: R$ %.2f | Itens: %d\n",
               listaPedidos[i].id,
               listaPedidos[i].clienteId,
               listaPedidos[i].data,
               listaPedidos[i].total,
               listaPedidos[i].qtdItens);
    }
}

// Função para consultar um pedido pelo ID
void consultarPedido() {
    int id;
    printf("Informe o ID do pedido a ser consultado: ");
    scanf("%d", &id);

    int posicao = encontrarPedidoPorId(id);
    if (posicao == -1) {
        printf("Pedido com ID %d não encontrado.\n", id);
        return;
    }

    Pedido pedido = listaPedidos[posicao];
    printf("=== DADOS DO PEDIDO ===\n");
    printf("ID: %d\n", pedido.id);
    printf("Cliente ID: %d\n", pedido.clienteId);
    printf("Data: %s\n", pedido.data);
    printf("Total: R$ %.2f\n", pedido.total);
    printf("Quantidade de itens: %d\n", pedido.qtdItens);

    // Listar itens do pedido
    if (pedido.qtdItens > 0) {
        printf("Itens:\n");
        for (int i = 0; i < pedido.qtdItens; i++) {
            printf("  - Produto ID: %d | Quantidade: %d | Subtotal: R$ %.2f\n",
                   pedido.itens[i].produtoId,
                   pedido.itens[i].quantidade,
                   pedido.itens[i].subtotal);
        }
    } else {
        printf("Este pedido não possui itens.\n");
    }
}

// Função para remover um pedido
void removerPedido() {
    int id;
    printf("Informe o ID do pedido a ser removido: ");
    scanf("%d", &id);

    int posicao = encontrarPedidoPorId(id);
    if (posicao == -1) {
        printf("Pedido com ID %d não encontrado.\n", id);
        return;
    }

    // Remover o pedido (deslocar elementos)
    for (int i = posicao; i < qtdPedidos - 1; i++) {
        listaPedidos[i] = listaPedidos[i + 1];
    }
    qtdPedidos--;

    printf("Pedido com ID %d removido com sucesso.\n", id);
}

// Função para carregar pedidos do arquivo CSV (versão básica)
void carregarPedidosCSV() {
    FILE *arquivo = fopen("data/Pedidos.csv", "r");
    if (arquivo == NULL) {
        printf("Arquivo Pedidos.csv não encontrado. Criando vazio...\n");
        return;
    }

    char linha[500];
    qtdPedidos = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Ignorar linhas vazias ou comentários
        if (linha[0] == '\n' || linha[0] == '#') continue;

        // Parse da linha (formato simples: id,clienteId,data,total,qtdItens,item1ProdutoId,item1Quantidade,item1Subtotal,...)
        // Este é um exemplo simplificado — em produção, você usaria parsing mais robusto
        int id, clienteId, qtdItens;
        double total;
        char data[11];

        if (sscanf(linha, "%d,%d,%[^,],%lf,%d", &id, &clienteId, data, &total, &qtdItens) != 5) {
            printf("Linha mal formatada: %s\n", linha);
            continue;
        }

        if (qtdPedidos >= MAX_PEDIDOS) break;

        Pedido pedido;
        pedido.id = id;
        pedido.clienteId = clienteId;
        strcpy(pedido.data, data);
        pedido.total = total;
        pedido.qtdItens = qtdItens;

        // Inicializar itens (em produção, ler os itens separadamente)
        for (int i = 0; i < qtdItens; i++) {
            pedido.itens[i].pedidoId = id;
            pedido.itens[i].produtoId = 0; // Preencher com valores reais
            pedido.itens[i].quantidade = 0;
            pedido.itens[i].subtotal = 0.0;
        }

        listaPedidos[qtdPedidos++] = pedido;
    }

    fclose(arquivo);
    printf("Pedidos carregados com sucesso! Total: %d\n", qtdPedidos);
}

// Função para salvar pedidos no arquivo CSV
void salvarPedidosCSV() {
    FILE *arquivo = fopen("data/Pedidos.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo Pedidos.csv\n");
        return;
    }

    for (int i = 0; i < qtdPedidos; i++) {
        Pedido pedido = listaPedidos[i];
        fprintf(arquivo, "%d,%d,%s,%.2f,%d\n", pedido.id, pedido.clienteId, pedido.data, pedido.total, pedido.qtdItens);
    }

    fclose(arquivo);
    printf("Pedidos salvos com sucesso no arquivo Pedidos.csv\n");
}
