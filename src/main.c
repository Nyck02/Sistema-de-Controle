#include <stdio.h>

int main() {
    printf("Projeto SCP iniciado com sucesso!\n");

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
//Se retornar 1 o codigo já existe
printf("ERRO: O código já está cadastrado no sistema, tente outro: ");
//Retornar para o menu produto
MostrarMenuProduto();

// Se não retornou 1 o codigo não existe e está liberado para cadastro
//chamando a função de cadastro
cadastro(novo_id);

//retorna botão "cadastrar" clicado

printf("O produto %d foi cadastrado com sucesso!\n", novo_produto.id); //confirmar exatamente que o produto x foi cadastrado

//Botão sair 
MostrarMenuPrincipal();


//Listamento dos produtos
ListarProdutos();

//Botão sair 
MostrarMenuPrincipal();


//Consultar um produto (apenas leitura)

printf("Digite o código do produto: "); //Não deveria ser o nome? 
scanf("%d", &codigo);
ConsultarProdutos(codigo);

//Botão sair 
MostrarMenuPrincipal();

//Remover produto 
printf("Digite o código do produto: "); 
scanf("%d", &codigo);
RemoverProduto(codigo);

//Botão sair 
MostrarMenuPrincipal();


return 0;






}

