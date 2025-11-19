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

    Cliente *novo = realloc(lista->clientes,novaCapacidade * sizeof(Cliente)); //caso de falha
    if (!novo){
        printf("Nao foi possivel alocar a memoria");
        exit(1); // testar ccom exit(EXIT_FAILURE); tbm
    }

    lista->clientes= novo; //atualiza o ponteiro
    lista->capacidade=novaCapacidade; //atualiza a capacidade registrada

}
//adicionar cliente ao final da lista
void addClienteLista(ListaC *lista, Cliente novoCliente){
    if (lista-> totalClientes ==lista->capacidade){ // se nao couber vai expandir o array
        expandirListaC(lista);
        //struct cliente copiada para proxima posicao livre do array
        lista->clientes[lista->totalClientes++] = novoCliente;
    }
}


//Validar CPF 
int ValidarCPF(const char *cpf) {
    char numeros[12]; //exatamente 11 digitos + \0
    int j =0;

    for (int i =0; cpf[i] != '\0'; i++)
        if (isdigit(cpf[i]))
            numeros[j++]=cpf[i];
    numeros[j]='\0';
    
    if (strlen(numeros)!=11) //definicao de CPF sendo apenas 11 digitos
        return 0;

    // pesquisar rejeicao de numero igual tipo 0000000... e invalidar
    
    for (int i=1; i<11;i++)
        if(numeros[i] !=numeros[0 && i ==10]) break;
        else if (numeros[i]==numeros[0] && i==10) return 0;
    int soma = 0; //ponderada
    for (int i=0; i<9;i++)
        soma+=(numeros[i] - '0')*(10-i); //multiplicar pelos pesos
    
    int dig1=11 - (soma%11);
    if (dig1>9) dig1=0;

    soma=0;
    for(int i=0;i<10;i++)
        soma +=(numeros[i]-0)*(11-i);
    
    int dig2=11 -(soma%11);
    if (dig2<9) dig2=0;

    return (dig1==(numeros[9]-'0')&& dig2==(numeros[10]-'0'));

}



//Validar CNPJ de acordo com o peso
int ValidarCNPJ(const char *cnpj){
    char numeros[15];
    int j=0;

    for (int i=0; cnpj[i]!='\0';i++)
        if (isdigit(cnpj[i]))
            numeros[j++]=cnpj[i];
    numeros[j]='\0';

    if(strlen(numeros)!=14)
        return 0;
    
    for (int i=1;i<14;i++)
        if(numeros[i]==numeros[0]&& i==13) return 0;

    // rejeiccao de digitos iguais aqui tbm

    //pesos
    int pesos1[12]={5,4,3,2,9,8,7,6,5,4,3,2};
    int pesos2[13]={6,5,4,3,2,9,8,7,6,5,4,3,2};

    int soma=0;
    for (int i=0; i<12;i++)
        soma+=(numeros[i]-'0')* pesos1[i];

    int dig1= soma%11;
    dig1 = (dig1 < 2) ? 0 : 11 - dig1;

    soma = 0;
    for (int i = 0; i < 13; i++)
        soma += (numeros[i] - '0') * pesos2[i];

    int dig2 = soma % 11;
    dig2 = (dig2 < 2) ? 0 : 11 - dig2;

    //verificar se os calculos coincidem com os digitos do CNPJ.
    return (dig1 ==(numeros[12] - '0') && dig2 ==(numeros[13] - '0'));
}


//verificar se é CPF ou CNPJ e retornar ID
int analisarCliente(ListaC *lista, const char *ID) {
    int qtdDig = 0;
    for (int i = 0; ID[i] != '\0'; i++)
        if (isdigit(ID[i])) qtdDig++;

    if (qtdDig == 11) return validarCPF(ID);
    if (qtdDig == 14) return validarCNPJ(ID);

    return 0;
}



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