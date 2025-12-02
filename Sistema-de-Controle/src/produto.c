#include "produto.h"
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "interface.h"


// Vetor Estático
static Produto listaProdutos[MAX_PRODUTOS];
static int totalProdutos = 0;

// Funcoes

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
    mvprintw(2, 2, "--- NOVO PRODUTO ---");

    // Coleta
    mvprintw(4, 4, "ID: "); lerString(4, 10, 5, bufferID);
    int id = atoi(bufferID);

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
        
        // 4. Escreva a linha formatada.
        // Cuidado com a ordem: ID (int), Descricao (string), Preco (float), Estoque (int)
        // Use %.2f no preço para fixar 2 casas decimais (ex: 5.50)
        
        fprintf(file, "%d,%s,%.2f,%d\n",
                listaProdutos[i].id,
                listaProdutos[i].descricao,
                listaProdutos[i].preco,
                listaProdutos[i].estoque);
    }

    // 5. Salve e feche
    fclose(file);
}

void CarregarProdutosCSV() {
    // 1. Abra o arquivo "data/Produtos.csv" no modo de leitura "r"
    FILE *file = fopen("data/Produtos.csv", "r"); 

    // 2. Verifique se o arquivo abriu. Se for NULL, saia da função.
    if (file == NULL) {
        return; 
    }

    char linha[256]; // Um buffer

    // 3. Pule o cabeçalho (Lê a primeira linha e joga fora)
    fgets(linha, sizeof(linha), file);

    totalProdutos = 0;

    //  ler uma linha e não estourar o limite (MAX_PRODUTOS)
    while (fgets(linha, sizeof(linha), file) != NULL && totalProdutos < MAX_PRODUTOS) {
        
        Produto p; // Variável temporária

        // 5. A MÁGICA (Parsing). 
        // O sscanf lê da 'linha'. A máscara é "%d,%[^,],%f,%d"
        // Tradução da máscara: Inteiro, Texto-até-virgula, Float, Inteiro
        // Preencha com as variáveis da struct: id, descricao, preco, estoque
        
        int lidos = sscanf(linha, "%d,%[^,],%f,%d", 
                           &p.id,   // Onde guardar o ID? (precisa do &)
                            p.descricao,   // Onde guardar a Descrição? (vetor não usa &), n'ao seria melhor uma string com espacos?
                           &p.preco,   // Onde guardar o Preço?
                           &p.estoque);  // Onde guardar o Estoque?
                           //ta me parecendo uma gambiarra

        // 6. Se leu exatamente 4 campos, salva no vetor oficial
        if (lidos == 4) {
            listaProdutos[totalProdutos] = p;
            totalProdutos++; // Incrementa para o próximo
        }
    }

    // 7. Feche o arquivo para não dar leak
    fclose(file);
}

// Funções obrigatórias para bater com o produto.h
void ConsultarProduto(int id) {
    (void)id; // Truque para o compilador não reclamar de variável não usada
}

void EditarProduto(int id) {
    (void)id;
}

void RemoverProduto(int id) {
    (void)id;
}