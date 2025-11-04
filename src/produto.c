#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h" 
#include "produto.h"
#define MAX_PRODUTOS 100



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

void MostrarMenuProdutos();

int AnalisarProduto(int codigo){
// Objetivo: verificar se o codigo já está cadastrado ou não
//O que é necessário: somente o id do produto
//O que vai sair: a permissão do cadastro ou não 

//Verificação: 



//Se retornar algo, quer dizer que o código não foi cadastrado (está liberado para cadastro)


}


void CadastrarProduto( int codigo){
    //objetivo: armazenar os dados do produto
    //O que é necessário: somente o codigo
    //o que vai ser feito: 
    //o que vai sair: 
    
    
    printf("Digite a descrição do produto: ");
scanf("%s", &novo_produto.descricao); 
//Lembrar !!! Fazer estrutura de descrição com nome, validade, categoria e etc


printf("Digite o preço do produto:")
scanf(" %lf", &novo_produto.preco);


printf("Digite a quantidade do produto em estoque:");
scanf("%d", &novo_produto.qt_estoque);

//Botão "cadastrar"


}



int main(){


    int codigo;


    struct produto *p;
    p = malloc(sizeof(struct produto));




Produto novo_produto;


// Cadastro do produto


printf("Digite o codigo do produto: ");
scanf ("%d", &novo_id);


//Verificação

//Chamando a função para analisar 
AnalisarProduto(novo_id);

//Se nada retornar 
//O codigo já existe

printf("ERRO: O código já está cadastrado no sistema, tente outro: ");
//Retornar para o menu 

//retornou algo
//O codigo não existe, cadastrar novo produto

//chamando a função de cadastro

cadastro(novo_id);

//retorna botão "cadastrar" clicado

printf("O produto %d foi cadastrado com sucesso!\n", novo_produto.id); //confirmar exatamente que o produto x foi cadastrado

//retornar para menu principal


return 0;






}


