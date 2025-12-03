#include "produto.h"
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "interface.h"


// Vetor Estático
static Produto listaProdutos[MAX_PRODUTOS];
static int totalProdutos = 0;

// Funcoes

int VerificarIDProduto(int idParaVerificar) {
    for (int i = 0; i < totalProdutos; i++) {
        if (listaProdutos[i].id == idParaVerificar) {
            return 1; // Encontrou! O ID já existe.
        }
    }
    return 0; // Não encontrou ninguém igual.
}

void InicializarProdutos() {
    totalProdutos = 0;
    CarregarProdutosCSV(); 
}

void CadastrarProduto() {
    if (totalProdutos >= MAX_PRODUTOS) {
        clear(); mvprintw(10, 10, "Erro: Cheio!"); getch(); return;
    }

    char bufferID[10], bufferDesc[50], bufferPreco[20], bufferEstoque[10];

    echo(); curs_set(1); clear(); box(stdscr, 0, 0);
    mvprintw(LINES/2, 2, "--- NOVO PRODUTO ---");

    
    mvprintw(LINES/4, 4, "ID: "); 
    lerString(4, 10, 5, bufferID);
    int id = atoi(bufferID);

    VerificarIDProduto(id);

    if (VerificarIDProduto(id) == 1) {
        mvprintw(LINES/6, 5, "ERRO: ID %d ja existe! Cadastro cancelado.", id);
        getch(); 
        return; 
    }

    mvprintw(6, 4, "Desc: "); 
    lerString(6, 10, 40, bufferDesc);

    mvprintw(8, 4, "Preco: "); 
    lerString(8, 12, 10, bufferPreco);
    float preco = atof(bufferPreco);

    mvprintw(10, 4, "Estoque: "); 
    lerString(10, 14, 5, bufferEstoque);
    int estoque = atoi(bufferEstoque);

    noecho(); curs_set(0);


    mvprintw(13, 4, "Deseja salvar? [S/N]");
    int confirmacao = getch(); 

    if (confirmacao == 's' || confirmacao == 'S') {
        
        listaProdutos[totalProdutos].id = id;
        strcpy(listaProdutos[totalProdutos].descricao, bufferDesc);
        listaProdutos[totalProdutos].preco = preco;
        listaProdutos[totalProdutos].estoque = estoque;
        totalProdutos++;

        SalvarProdutosCSV();

        mvprintw(16, 4, "SUCESSO! Salvo.");
    } else {
        mvprintw(14, 4, "Cancelado.");
    }
    
    mvprintw(18, 4, "Fim. Pressione para sair.");
    getch();
}

void ListarProdutos() {
    clear();
    box(stdscr, 0, 0);
    mvprintw(2, 2, "--- LISTA DE PRODUTOS ---");
    
    // Cabeçalho alinhado
    attron(A_BOLD);
    mvprintw(4, 4, "ID    Descricao            Preco      Estoque");
    attroff(A_BOLD);

    if (totalProdutos == 0) {
        mvprintw(6, 4, "Nenhum produto cadastrado.");
    } else {
        // Mostra os produtos na tela
        for (int i = 0; i < totalProdutos; i++) {
            mvprintw(6 + i, 4, "%-5d %-20s R$ %-8.2f %d", 
                listaProdutos[i].id, 
                listaProdutos[i].descricao, 
                listaProdutos[i].preco, 
                listaProdutos[i].estoque
            );
        }
    }
    mvprintw(LINES - 2, 4, "Pressione qualquer tecla para voltar...");
    getch();
}

void SalvarProdutosCSV() {
    
    FILE *file = fopen("data/Produtos.csv", "w"); 
    
    if (file == NULL) {
        mvprintw(LINES-1, 0, "Erro ao salvar arquivo! Pressione algo.");
        getch();
        return;
    }

    //  cabeçalho
    
    fprintf(file, "ID,Descricao,Preco,Estoque\n");

    // percorrer todos os produtos 
    for (int i = 0; i < totalProdutos; i++) {
        
        
        // ID (int), Descricao (string), Preco (float), Estoque (int)
        
        fprintf(file, "%d,%s,%.2f,%d\n",
                listaProdutos[i].id,
                listaProdutos[i].descricao,
                listaProdutos[i].preco,
                listaProdutos[i].estoque);
    }
    fclose(file);
}

void CarregarProdutosCSV() {
    
    FILE *file = fopen("data/Produtos.csv", "r"); 

    
    if (file == NULL) {
        return; 
    }

    char linha[256]; // Um buffer

    fgets(linha, sizeof(linha), file);

    totalProdutos = 0;

    while (fgets(linha, sizeof(linha), file) != NULL && totalProdutos < MAX_PRODUTOS) {
        
        Produto p; // Variável temporária

        // Variáveis da struct: id, descricao, preco, estoque
        
        int lidos = sscanf(linha, "%d,%[^,],%f,%d", 
                           &p.id,   // Onde guardar o ID
                            p.descricao,   // Onde guardar a Descrição
                           &p.preco,   // Onde guardar o Preço
                           &p.estoque);  // Onde guardar o Estoque
                           

        // Se le exatamente 4 campos, salva no vetor oficial
        if (lidos == 4) {
            listaProdutos[totalProdutos] = p;
            totalProdutos++; // Incrementa para o próximo
        }
    }
    fclose(file);
}

void ConsultarProduto() {
    char bufferID[10];
    int idBusca;
    int posicao = -1; 

    
    clear();
    box(stdscr, 0, 0);
    mvprintw(2, 2, "--- CONSULTAR PRODUTO ---");

    mvprintw(4, 4, "Digite o ID para buscar: ");
    lerString(4, 29, 5, bufferID);
    idBusca = atoi(bufferID);

    for (int i = 0; i < totalProdutos; i++) {
        if (listaProdutos[i].id == idBusca) {
            posicao = i;
            break;
        }
    }

    
    if (posicao == -1) {
        
        attron(A_BOLD);
        mvprintw(6, 4, "ERRO: Produto ID %d nao encontrado.", idBusca);
        attroff(A_BOLD);
    } else {
        
        attron(A_REVERSE);
        mvprintw(6, 4, " DETALHES DO PRODUTO ");
        attroff(A_REVERSE);

        mvprintw(8, 6,  "ID:        %d", listaProdutos[posicao].id);
        mvprintw(9, 6,  "Descricao: %s", listaProdutos[posicao].descricao);
        mvprintw(10, 6, "Preco:     R$ %.2f", listaProdutos[posicao].preco);
        
        
        mvprintw(11, 6, "Estoque:   %d", listaProdutos[posicao].estoque);
        
        if (listaProdutos[posicao].estoque < 5) {
            attron(A_BOLD); 
            printw(" (Alerta: estoque baixo, menos de 5 produtos)");
            attroff(A_BOLD);
        }
    }

    mvprintw(14, 4, "Pressione qualquer tecla para voltar...");
    getch();
}

void EditarProduto() {
    char bufferID[10];
    int idBusca;
    int posicao = -1;

    
    clear();
    box(stdscr, 0, 0);
    mvprintw(2, 2, "--- EDITAR PRODUTO ---");

    
    mvprintw(4, 4, "Digite o ID para editar: ");
    lerString(4, 29, 5, bufferID);
    idBusca = atoi(bufferID);

    for (int i = 0; i < totalProdutos; i++) {
        if (listaProdutos[i].id == idBusca) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        mvprintw(6, 4, "ERRO: Produto nao encontrado.");
        getch();
        return;
    }

    char bufferDesc[50];
    char bufferPreco[20];
    char bufferEstoque[10];

    mvprintw(6, 4, "Produto encontrado: %s", listaProdutos[posicao].descricao);
    mvprintw(7, 4, "Pressione ENTER para manter o valor atual.");

 
    mvprintw(9, 4, "Nova Descricao (Atual: %s): ", listaProdutos[posicao].descricao);
    lerString(9, 35, 40, bufferDesc);
    
  
    if (strlen(bufferDesc) > 0) {
        strcpy(listaProdutos[posicao].descricao, bufferDesc);
    }

  
    mvprintw(11, 4, "Novo Preco (Atual: %.2f): ", listaProdutos[posicao].preco);
    lerString(11, 35, 10, bufferPreco);
    
    if (strlen(bufferPreco) > 0) {
        listaProdutos[posicao].preco = atof(bufferPreco);
    }


    mvprintw(13, 4, "Novo Estoque (Atual: %d): ", listaProdutos[posicao].estoque);
    lerString(13, 35, 5, bufferEstoque);

    if (strlen(bufferEstoque) > 0) {
        listaProdutos[posicao].estoque = atoi(bufferEstoque);
    }
    
    SalvarProdutosCSV(); 
    
    mvprintw(16, 4, "SUCESSO! Dados atualizados.");
    getch();
}
void RemoverProduto() {
    
    
    char bufferID[10];
    int posicao_do_alvo = -1; 

    
    clear();
    box(stdscr, 0, 0);
    mvprintw(2, 2, "--- REMOVER PRODUTO ---");
    
    mvprintw(4, 4, "Digite o ID para excluir: "); 
    lerString(4, 30, 5, bufferID);
    int idExc = atoi(bufferID);

    for (int i = 0; i < totalProdutos; i++) {
        if (listaProdutos[i].id == idExc) {
            posicao_do_alvo = i; // guardar o endereço 
            break; 
        }
    }

    
    if (posicao_do_alvo == -1) {
        attron(A_BOLD);
        mvprintw(6, 4, "ERRO: ID %d nao encontrado!", idExc);
        attroff(A_BOLD);
        getch(); 
        return; 
    }
    
    
    mvprintw(6, 4, "Encontrado: %s", listaProdutos[posicao_do_alvo].descricao);
    mvprintw(7, 4, "Tem certeza que deseja excluir? [S/N]");
    int confirmacao = getch();

    if (confirmacao == 's' || confirmacao == 'S') {
        
        for (int j = posicao_do_alvo; j < totalProdutos - 1; j++) {
            listaProdutos[j] = listaProdutos[j+1];
        }

        
        totalProdutos--; 
        
        refresh();
        
        SalvarProdutosCSV();
        
        mvprintw(11, 4, "Produto removido com SUCESSO.");
        return;
    } else {
        mvprintw(9, 4, "Operacao cancelada.");
    }
    getch();
}
