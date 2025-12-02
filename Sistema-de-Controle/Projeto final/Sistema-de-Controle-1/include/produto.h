#ifndef PRODUTO_H
#define PRODUTO_H
#include <ncurses> 
#define MAX_PRODUTO 100 //para o caso de chegar no limite o estoque

//Estrutura do produto
typedef struct {
    int id; // Um número de identificação único para cada produto.
    char descricao[100]; //A descrição do produto.
    double preco; // O preço unitário do produto.
    int estoque; // A quantidade disponível do produto em estoque.
} Produto;

//Estrutura do estoque 
typedef struct{
    Produto lista[MAX_PRODUTOS];
    int contador; //para controlar a quantidade de produtos no vetor 
} ListaProdutos;

//Estrutura da descrição RASCUNHO
typedef struct{

    char nome[50];
    int codigos; 
    char categoria[50];

}

//Menu produtos 
void MostrarMenuProduto();


int AnalisarProduto(ListaProduto *listaP int codigo);
void CadastrarProduto( ListaProduto *listaP, int codigo);
void ListarProdutos(ListaProduto *listaP);
void EditarProduto(ListaProduto *listaP, int codigo);
void ConsultarProdutos(ListaProduto *listaP, int codigo);
void RemoverProduto( ListaProduto *listaP, int codigo);

//Dúvida essa *lista tem que ser com o nome diferente para todos? #########
//Tem que pegar só o codigo do produto 

//As funções de salvar ou carregar produto no CSV
void salvarProdutosCSV(ListaProduto *listaP);
void carregarProdutosCSV(ListaProduto *listaP);

#endif