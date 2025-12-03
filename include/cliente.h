#ifndef CLIENTE_H
#define CLIENTE_H

#include <ncurses.h>
#include <stddef.h>

//pessoa fisica ou juridica
typedef enum{
    IDfisica,
    IDjuridica
}TipoCliente;

//estrutura endereco
typedef struct {
    char estado[4]; //sigla
    char cidade[51];
    char cep[11];   //74000-000
    char logradouro[101];
    char numero[11]; //testar s/n
    char complemento[51];

}Endereco;

//estrutura cliente
typedef struct {
    int IDcadastro; //a partir de 01
    TipoCliente tipo;
    char nome[101]; //nome ou razao social
    char ID[21]; //111.222.333.44 ou 11.222.333/001-44
    char telefone[21]; //(99) 99999-9999
    char email[50];
    Endereco endereco;
    int quantPedidos;   //listagem e historico
    int ativo; //1- ativo, 0- removido
}Cliente;

//lista clientes na memoria (vetor dinamico)
typedef struct {
    Cliente *clientes;
    int totalClientes;
    int capacidade;
}ListaC;

//interface
void menuCliente();

//lista - inicialização e alocação
void inicializarListaC(ListaC *lista);
void liberarListaC(ListaC *lista);
void addClienteLista(ListaC *lista, Cliente novoCliente);

//crud
void inserirCliente(ListaC *lista);
int removerCliente (ListaC *clientes, int IDbusca);
int editarCliente (ListaC *cliente, int IDbusca);
void listarClientes(ListaC *lista);

//busca e validação
Cliente* buscarCliente (ListaC *lista, const char *termoBusca);
int analisarCliente(const char *ID);
int validarCPF (const char *cpf);
int validarCNPJ(const char *cnpj);

//persistencia .csv
ListaC* carregarCcsv(const char *filepath);
void salvarCcsv(ListaC *lista, const char *filepath);

#endif