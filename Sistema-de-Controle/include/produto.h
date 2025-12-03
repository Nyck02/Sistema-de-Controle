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
void InicializarProdutos(); 
void CadastrarProduto(); 
void ListarProdutos();
void SalvarProdutosCSV();
void CarregarProdutosCSV();

// Funções extras
void ConsultarProduto();
void EditarProduto();
void RemoverProduto();
int VerificarIDProduto(int idParaVerificar);

#endif