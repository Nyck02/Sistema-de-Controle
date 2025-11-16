#ifndef CLIENTE_H
#define CLIENTE_H

#include <ncurses.h> 

//pessoa fisica ou juridica
typedef enum {
    IDfisica,
    IDjuridica
} TipoCliente;

//estrutura endereco
typedef struct {
    char estado[3];     //SIGLA
    char cidade[50];
    char cep[10];         //"74000-000"
    char logradouro[100];
    char numero[10];      //testar "S/N"
    char complemento[50]; 
} Endereco;

//estrutura cliente
typedef struct {
    int IDcadastro;     //a partir de 01
    TipoCliente tipo;   //PF ou PJ
    char nome[100];
    char ID[20];     //"111.111.111-11" ou CNPJ
    char telefone[16];      //"(99) 99999-9999"
    char email[50];
    Endereco endereco;
    int quantPedidos;   //listtagem e historico de pedidos
    int ativo;  //1- ativo; 0- removido
} Cliente;

//lista de clientes na memoria
typedef struct {
    Cliente *clientes;
    int totalClientes;
    int capacidade;
} ListaClientes;

//MENU CLIENTE 
void menuCliente();

//CONSULTA CLIENTE - codigo ou CPF/CNPJ
Cliente* buscarCliente(ListaClientes *lista, const char *termoBusca);

//documento .csv
ListaClientes* carregarClientesCSV();
void salvarClientesCSV(ListaClientes *lista);
void liberarListaClientes(ListaClientes *lista);
void inicioLista(ListaClientes *lista);
void adicionarClienteLista(ListaClientes *lista, Cliente novoCliente);


#endif