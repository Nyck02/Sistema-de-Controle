#ifndef PRODUTO_H
#define PRODUTO_H

#include <ncurses.h>

#define MAX_PRODUTOS 100

// Modelo do dado
typedef struct {
    int id;
    char descricao[50];
    float preco;
    int estoque;
} Produto;

// Protótipos das funções
// Note que removemos a complexidade de "ListaProduto*"
void InicializarProdutos();
void CadastrarProduto(); 
void ListarProdutos();
void SalvarProdutosCSV();
void CarregarProdutosCSV();

// Funções extras (Stubs)
void ConsultarProduto(int id);
void EditarProduto(int id);
void RemoverProduto(int id);

#endif