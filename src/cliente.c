#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include "/home/tailimasx/Projeto_Final/Sistema-de-Controle/include/cliente.h"

#define tam_lista_inicial 10
#define ArqClientes "/home/tailimasx/Projeto_Final/Sistema-de-Controle/data/Clientes.csv"


//Gerenciar Lista Clientes



void iniListaC(ListaC *lista){  //define ponteiro como null e contador 0
    lista->clientes=NULL;
    lista->totalClientes=0; 
    lista->capacidade=0;
}

void liberarListaC(ListaC *lista){
    if (lista->clientes != NULL) {
        free(lista->clientes);  //libera memoria alocada para array clientes
        lista->clientes = NULL;
    }
    lista->clientes =NULL;
    lista->totalClientes=0;
    lista->capacidade=0;
}

void expandirListaC(ListaC *lista){
    int novaCapacidade = (lista->capacidade==0) ? tam_lista_inicial : lista-> capacidade *2; //capacidade começa com 10 se estiver vazia ou dobra

    Cliente *novo = realloc(lista->clientes,novaCapacidade * sizeof(Cliente));
    if (!novo){
        printf("Nao foi possivel alocar a memoria");
        exit(1);
    }

    lista->clientes= novo;
    lista->capacidade=novaCapacidade;

}

void addClienteLista(ListaC *lista, Cliente novoCliente){
    if (lista-> totalClientes ==lista->capacidade){
        expandirListaC(lista);
        lista->clientes[lista->totalClientes++] = novoCliente;
    }
}


//Validar CPF 





//Validar CNPJ de acordo com o peso




//verificar se é CPF ou CNPJ e retornar ID




//busca de cliente
Cliente* buscarCliente(ListaC *lista, const char termoBusca) {
    for (int i =0; i<lista->totalClientes; i++){
        if (strcmp(lista->clientes[i].ID, termoBusca)==0){
            return &lista->clientes[i];
        }
    }
    return NULL;
}


//inserir cliente
void inserirCliente(ListaC *lista) {
    Cliente c;
    c.IDcadastro=lista->totalClientes +1;
    c.quantPedidos=0;
    c.ativo=1;
}



//remover cliente



//listagem dos clientes

//carregar o arquivo .csv

//salvar no csv.