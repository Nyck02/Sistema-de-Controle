#ifndef PRODUTO_H
#define PRODUTO_H
#define MAX_PRODUTO 100 //para o caso de chegar no limite o estoque

typedef struct {
    int id; // Um número de identificação único para cada produto.
    char descricao[100]; //A descrição do produto.
    double preco; // O preço unitário do produto.
    int estoque; // A quantidade disponível do produto em estoque.
} Produto;

typedef struct{
    Produto lista[MAX_PRODUTOS];
    int contador; //para controlar a quantidade de produtos no vetor 
} ListaProdutos

int AnalisarProduto(int codigo);
void CadastrarProduto( int codigo);
void ListarProdutos();
void ConsultarProdutos(int codigo);
void RemoverProduto();


//As funções de salvar ou carregar produto no CSV

#endif