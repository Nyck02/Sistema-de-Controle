// Includes de bibliotecas padrão
#include <ncurses.h> // Para a interface com o usuário 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include pedido.h 
#include cliente.h
#include produto.h 

// --- ARMAZENAMENTO EM MEMÓRIA ---
// "static" faz com que estas variáveis sejam visíveis apenas DENTRO deste arquivo.
static Pedido listaPedidos[MAX_PEDIDOS];
static int qtdPedidos = 0; // Quantidade atual de pedidos cadastrados

// --- FUNÇÕES DE SIMULAÇÃO (STUBS) ---
// Estas funções simulam os outros módulos (Cliente e Produto)
// para que você possa compilar e testar o módulo Pedido isoladamente.
// Elas devem ser REMOVIDAS quando você integrar os módulos.

// Implementações temporárias até integrar com os módulos reais
static Cliente* analisarCliente(int id) {
    // Simula a busca de um cliente.
    // No projeto real, esta função viria de "cliente.c"
    if (id > 0) {
        static Cliente c; // 'static' para o ponteiro ser válido
        c.IDcadastro = id;
        strcpy(c.nome, "Cliente Ficticio");
        c.ativo = 1;
        return &c;
    }
    return NULL; // Cliente não encontrado
}

static Produto* analisarProduto(int id) {
    // Simula a busca de um produto.
    // No projeto real, esta função viria de "produto.c"
    if (id > 0) {
        static Produto p; // 'static' para o ponteiro ser válido
        p.id = id;
        strcpy(p.descricao, "Produto Ficticio");
        p.preco = 10.50; // Preço de exemplo
        p.estoque = 50;  // Estoque de exemplo
        return &p;
    }
    return NULL; // Produto não encontrado
}

// --- FUNÇÕES AUXILIARES INTERNAS ---

/**
 * @brief Encontra o ÍNDICE de um pedido na 'listaPedidos' usando o ID.
 * @param id O ID do pedido a ser buscado.
 * @return O índice (posição) no vetor, ou -1 se não for encontrado.
 */
static int encontrarPedidoPorId(int id) {
    for (int i = 0; i < qtdPedidos; i++) {
        if (listaPedidos[i].id == id) {
            return i; // Retorna o índice
        }
    }
    return -1; // Pedido não encontrado
}

/**
 * @brief Gera um novo ID único para um pedido.
 * (Sua função original estava correta).
 */
static int gerarNovoIdPedido() {
    int id = 1;
    // Enquanto o ID já existir, incrementa
    while (encontrarPedidoPorId(id) != -1) {
        id++;
    }
    return id;
}


// --- FUNÇÕES PRINCIPAIS DO MÓDULO (REESCRITAS) ---

/**
 * @brief Processa o caso de uso "Cadastrar Pedido".
 * Esta função agora valida o cliente e inclui o loop para cadastrar itens.
 */
void inserirPedido() {
    clear(); // Limpa a tela (ncurses)
    
    if (qtdPedidos >= MAX_PEDIDOS) {
        mvprintw(0, 0, "Erro: Limite máximo de pedidos atingido. Pressione qualquer tecla...");
        getch(); // Espera o usuário pressionar uma tecla
        return;
    }

    Pedido novoPedido;
    novoPedido.id = gerarNovoIdPedido();
    novoPedido.qtdItens = 0;
    novoPedido.total = 0.0;
    
    echo(); // Habilita o eco do teclado para o usuário ver o que digita

    // 1. Validar Cliente (CORREÇÃO 3)
    mvprintw(0, 0, "--- Cadastro de Novo Pedido (ID: %d) ---", novoPedido.id);
    mvprintw(2, 0, "Informe o ID do cliente: ");
    scanw("%d", &novoPedido.clienteId); // scanw é o "scanf" do ncurses

    // CORREÇÃO: Chama a função 'analisarCliente' do módulo Cliente [cite: 193]
    if (analisarCliente(novoPedido.clienteId) == NULL) {
        mvprintw(4, 0, "Erro: Cliente com ID %d não encontrado. Pressione qualquer tecla...", novoPedido.clienteId);
        getch();
        return;
    }
    
    mvprintw(3, 0, "Informe a data (dd/mm/aaaa): ");
    getstr(novoPedido.data); // getstr é para ler strings no ncurses

    // 2. Loop de Inserção de Itens (CORREÇÃO 2)
    mvprintw(5, 0, "--- Inserindo Itens no Pedido ---");
    char continuar = 's';
    int linhaBase = 7;

    do {
        if (novoPedido.qtdItens >= MAX_ITENS_POR_PEDIDO) {
            mvprintw(linhaBase, 0, "Limite de itens por pedido atingido. Pressione qualquer tecla...");
            getch();
            break;
        }
        
        int prodId, qtd;
        mvprintw(linhaBase, 0, "ID do Produto: ");
        scanw("%d", &prodId);

        // Validação do Produto (chama a função do módulo Produto) [cite: 196]
        Produto* p = analisarProduto(prodId);
        if (p == NULL) {
            mvprintw(linhaBase + 1, 0, "Erro: Produto com ID %d não encontrado.", prodId);
        } else if (p->estoque <= 0) {
            mvprintw(linhaBase + 1, 0, "Erro: Produto '%s' sem estoque.", p->descricao);
        } else {
            mvprintw(linhaBase + 1, 0, "Produto: %s | Preço: R$%.2f | Estoque: %d", p->descricao, p->preco, p->estoque);
            mvprintw(linhaBase + 2, 0, "Quantidade desejada: ");
            scanw("%d", &qtd);

            if (qtd <= 0) {
                mvprintw(linhaBase + 3, 0, "Quantidade deve ser positiva.");
            } else if (qtd > p->estoque) {
                mvprintw(linhaBase + 3, 0, "Erro: Estoque insuficiente (Apenas %d disponíveis).", p->estoque);
            } else {
                // Adiciona o item
                int idx = novoPedido.qtdItens;
                novoPedido.itens[idx].pedidoId = novoPedido.id;
                novoPedido.itens[idx].produtoId = p->id;
                novoPedido.itens[idx].quantidade = qtd;
                novoPedido.itens[idx].subtotal = qtd * p->preco;

                // Atualiza o total do pedido
                novoPedido.total += novoPedido.itens[idx].subtotal;
                novoPedido.qtdItens++;
                
                // (Aqui você deveria atualizar o estoque do produto, ex: p->estoque -= qtd;)

                mvprintw(linhaBase + 3, 0, "Item adicionado! Subtotal: R$%.2f", novoPedido.itens[idx].subtotal);
            }
        }
        
        mvprintw(linhaBase + 5, 0, "Deseja adicionar outro item? (s/n): ");
        scanw(" %c", &continuar);
        
        // Limpa a área de inserção de item para o próximo
        for(int i = 0; i < 6; i++) {
            move(linhaBase + i, 0); clrtoeol(); // Limpa da linha atual até o final
        }

    } while (continuar == 's' || continuar == 'S');
    
    noecho(); // Desabilita o eco do teclado

    // Adiciona o pedido ao vetor
    if(novoPedido.qtdItens > 0) {
        listaPedidos[qtdPedidos] = novoPedido;
        qtdPedidos++;
        mvprintw(linhaBase, 0, "Pedido cadastrado com sucesso! Total: R$%.2f. Pressione qualquer tecla...", novoPedido.total);
    } else {
        mvprintw(linhaBase, 0, "Cadastro cancelado (nenhum item adicionado). Pressione qualquer tecla...");
    }
    
    getch();
}


/**
 * @brief Lista todos os pedidos cadastrados (versão ncurses).
 */
void listarPedidos() {
    clear();
    if (qtdPedidos == 0) {
        mvprintw(0, 0, "Nenhum pedido cadastrado. Pressione qualquer tecla...");
        getch();
        return;
    }

    mvprintw(0, 0, "--- LISTA DE PEDIDOS CADASTRADOS (Total: %d) ---", qtdPedidos);
    for (int i = 0; i < qtdPedidos; i++) {
        mvprintw(i + 2, 0, "ID: %d | ClienteID: %d | Data: %s | Total: R$%.2f | Itens: %d",
                 listaPedidos[i].id,
                 listaPedidos[i].clienteId,
                 listaPedidos[i].data,
                 listaPedidos[i].total,
                 listaPedidos[i].qtdItens);
    }
    mvprintw(qtdPedidos + 3, 0, "Pressione qualquer tecla para voltar...");
    getch();
}

/**
 * @brief Consulta um pedido específico pelo ID (versão ncurses).
 */
void consultarPedido() {
    clear();
    echo();
    int id;
    mvprintw(0, 0, "Informe o ID do pedido a ser consultado: ");
    scanw("%d", &id);
    noecho();

    int posicao = encontrarPedidoPorId(id);
    if (posicao == -1) {
        mvprintw(2, 0, "Pedido com ID %d não encontrado. Pressione qualquer tecla...", id);
        getch();
        return;
    }

    Pedido pedido = listaPedidos[posicao];
    mvprintw(2, 0, "--- DADOS DO PEDIDO ID: %d ---", pedido.id);
    mvprintw(3, 0, "Cliente ID: %d", pedido.clienteId);
    mvprintw(4, 0, "Data: %s", pedido.data);
    mvprintw(5, 0, "Total: R$ %.2f", pedido.total);
    mvprintw(6, 0, "Quantidade de itens: %d", pedido.qtdItens);

    if (pedido.qtdItens > 0) {
        mvprintw(8, 0, "--- Itens do Pedido ---");
        for (int i = 0; i < pedido.qtdItens; i++) {
            mvprintw(i + 9, 2, "- Produto ID: %d | Qtd: %d | Subtotal: R$ %.2f",
                     pedido.itens[i].produtoId,
                     pedido.itens[i].quantidade,
                     pedido.itens[i].subtotal);
        }
    }
    
    mvprintw(pedido.qtdItens + 10, 0, "Pressione qualquer tecla para voltar...");
    getch();
}

/**
 * @brief Remove um pedido (versão ncurses).
 */
void removerPedido() {
    clear();
    echo();
    int id;
    mvprintw(0, 0, "Informe o ID do pedido a ser removido: ");
    scanw("%d", &id);
    noecho();

    int posicao = encontrarPedidoPorId(id);
    if (posicao == -1) {
        mvprintw(2, 0, "Pedido com ID %d não encontrado. Pressione qualquer tecla...", id);
        getch();
        return;
    }
    
    mvprintw(2, 0, "Pedido %d (Cliente %d, Total R$%.2f) encontrado.", 
             listaPedidos[posicao].id, listaPedidos[posicao].clienteId, listaPedidos[posicao].total);
    mvprintw(3, 0, "Tem certeza que deseja remover? (s/n): ");
    char confirm = getch();

    if (confirm != 's' && confirm != 'S') {
        mvprintw(5, 0, "Remoção cancelada. Pressione qualquer tecla...");
        getch();
        return;
    }

    // Remover o pedido (deslocar elementos)
    // (Sua lógica original estava correta)
    for (int i = posicao; i < qtdPedidos - 1; i++) {
        listaPedidos[i] = listaPedidos[i + 1];
    }
    qtdPedidos--;

    mvprintw(5, 0, "Pedido com ID %d removido com sucesso. Pressione qualquer tecla...", id);
    getch();
}

// --- FUNÇÕES DE PERSISTÊNCIA (REESCRITAS) ---

/**
 * @brief Salva os pedidos e seus itens em arquivos CSV separados.
 * (CORREÇÃO 1)
 */
void salvarPedidosCSV() {
    // 1. Abre o arquivo principal de Pedidos
    FILE *fPedidos = fopen("data/Pedidos.csv", "w");
    // 2. Abre o arquivo de Itens
    FILE *fItens = fopen("data/ItensPedido.csv", "w");

    if (fPedidos == NULL || fItens == NULL) {
        mvprintw(0, 0, "Erro crítico: Não foi possível abrir os arquivos CSV para salvar. Pressione tecla...");
        getch();
        return;
    }
    
    // Escreve cabeçalhos (boa prática)
    fprintf(fPedidos, "id,clienteId,data,total\n");
    fprintf(fItens, "pedidoId,produtoId,quantidade,subtotal\n");

    // Loop em todos os pedidos em memória
    for (int i = 0; i < qtdPedidos; i++) {
        Pedido p = listaPedidos[i];
        
        // 3. Salva os dados do Pedido principal em "Pedidos.csv"
        fprintf(fPedidos, "%d,%d,%s,%.2f\n", 
                p.id, p.clienteId, p.data, p.total);
        
        // 4. Loop interno para salvar os itens daquele pedido
        for (int j = 0; j < p.qtdItens; j++) {
            ItemPedido item = p.itens[j];
            
            // 5. Salva os dados do Item em "ItensPedido.csv"
            fprintf(fItens, "%d,%d,%d,%.2f\n",
                    item.pedidoId, item.produtoId, item.quantidade, item.subtotal);
        }
    }

    fclose(fPedidos);
    fclose(fItens);

    // mvprintw(0, 0, "Dados de pedidos e itens salvos com sucesso. Pressione tecla...");
    // getch();
}

/**
 * @brief Carrega os pedidos e seus itens dos arquivos CSV.
 * (CORREÇÃO 1)
 */
void carregarPedidosCSV() {
    char linha[512];
    qtdPedidos = 0; // Reseta o contador da memória

    // 1. Abre e carrega os Pedidos principais
    FILE *fPedidos = fopen("data/Pedidos.csv", "r");
    if (fPedidos == NULL) {
        // mvprintw(0, 0, "Arquivo Pedidos.csv não encontrado. Começando do zero.");
        // getch();
        return; // Sai se não houver pedidos para carregar
    }

    // Pula a linha do cabeçalho
    fgets(linha, sizeof(linha), fPedidos);

    // Lê cada linha do arquivo de Pedidos
    while (fgets(linha, sizeof(linha), fPedidos) != NULL && qtdPedidos < MAX_PEDIDOS) {
        Pedido p;
        // Lê os dados principais
        sscanf(linha, "%d,%d,%[^,],%lf", 
               &p.id, &p.clienteId, p.data, &p.total);
        
        p.qtdItens = 0; // IMPORTANTE: Zera o contador de itens
        
        listaPedidos[qtdPedidos] = p;
        qtdPedidos++;
    }
    fclose(fPedidos);

    // 2. Abre e carrega os Itens
    FILE *fItens = fopen("data/ItensPedido.csv", "r");
    if (fItens == NULL) {
        return; // Sai se não houver itens (pode ser normal)
    }

    // Pula a linha do cabeçalho
    fgets(linha, sizeof(linha), fItens);

    // Lê cada linha do arquivo de Itens
    while (fgets(linha, sizeof(linha), fItens) != NULL) {
        ItemPedido item;
        sscanf(linha, "%d,%d,%d,%lf", 
               &item.pedidoId, &item.produtoId, &item.quantidade, &item.subtotal);
        
        // 3. Encontra o Pedido "pai" deste item
        int idxPedido = encontrarPedidoPorId(item.pedidoId);
        
        if (idxPedido != -1) {
            // 4. Adiciona o item ao vetor 'itens' do pedido pai
            Pedido* pPai = &listaPedidos[idxPedido];
            
            if (pPai->qtdItens < MAX_ITENS_POR_PEDIDO) {
                int idxItem = pPai->qtdItens;
                pPai->itens[idxItem] = item;
                pPai->qtdItens++;
            }
        }
    }
    fclose(fItens);
}
