#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include "cliente.h"

#define tam_lista_inicial 10
#define CLIENTES_CSV "clientes.csv"



void inicializarListaC(ListaC *lista){  //define ponteiro como null e contador 0
    lista->clientes=NULL;
    lista->totalClientes=0; 
    lista->capacidade=0;
}

void liberarListaC(ListaC *lista){
    if (lista->clientes != NULL) {
        free(lista->clientes);  //libera memoria alocada para array clientes
        lista->clientes = NULL;
    }

    lista->totalClientes=0;
    lista->capacidade=0;
}

static void expandirListaC(ListaC *lista){
    int novaCapacidade = (lista->capacidade==0) ? tam_lista_inicial : lista-> capacidade *2; //capacidade começa com 10 se estiver vazia ou dobra

    Cliente *novo = realloc(lista->clientes,novaCapacidade * sizeof(Cliente)); //caso de falha
    if (!novo){
        fprintf(stderr, "Nao foi possivel alocar a memoria");
        exit(EXIT_FAILURE); // testar ccom exit(EXIT_FAILURE); tbm
    }

    lista->clientes= novo; //atualiza o ponteiro
    lista->capacidade=novaCapacidade; //atualiza a capacidade registrada

}
//adicionar cliente ao final da lista
void addClienteLista(ListaC *lista, Cliente novoCliente){ 
    if (lista->totalClientes == lista->capacidade){ 
        expandirListaC(lista);
    }
    lista->clientes[lista->totalClientes++] = novoCliente;
}



//Validar CPF 
int validarCPF(const char *cpf) {
    int digitos[11]; 
    int j =0;

    for (int i =0; cpf[i] != '\0' && j<11; i++){
        if (isdigit((unsigned char)cpf[i])){
            digitos[j++]=cpf[i] - '0';
        }
    }
    
    if (j!=11) //definicao de CPF sendo apenas 11 digitos
        return 0;

    //  rejeicao de numero igual tipo 0000000... e invalidar
    
    int todosIguais=1;
    for (int i = 1; i< 11; i++)
        if(digitos[i]!=digitos[0]){
            todosIguais=0;
            break;
        }
    
    int soma=0;
    for(int i=0;i<9;i++)
        soma+=digitos[i]*(10-i);
        int resto =soma%11;
        int dig1=(resto>2)? 0 : 11-resto;

    soma=0;
    for (int i=0;i<9;i++)
        soma+=digitos[i]*(11-i);
        soma+=dig1*2;
        resto=soma%11;
        int dig2=(resto<2)?0:11-resto;
    
    return(dig1==digitos[9] && dig2==digitos[10]);
}

int validarCNPJ(const char *cnpj){
    int digitos[14];
    int j=0;

    for(int i=0;cnpj[i]!='\0' && j<14;i++){
        if (isdigit((unsigned char)cnpj[i])){
            digitos[j++]=cnpj[i]-'0';
        }
    }

    if(j!=14)
        return 0;
    
    int todosIguais=1;
    for(int i=1; i<14;i++)
        if (digitos[i]!=digitos[0]){
            todosIguais=0;
            break;
        }
        if (todosIguais=1)
            return 0;

            //validar de acordo com o peso
    int pesos1[12]= {5,4,3,2,9,8,7,6,5,4,3,2};
    int pesos2[13]={6,5,4,3,2,9,8,7,6,5,4,3,2};

    int soma=0;

    for(int i=0;i<12;i++)
        soma+=digitos[i]*pesos1[i];
        int resto= soma % 11;
        int dig1 = (resto<2)? 0 : 11 -resto;
    
        soma =0;
        for (int i=0; i<12; i++)
        soma+= digitos[i]*pesos2[i];
        resto = soma%11;
        int dig2= (resto<2)? 0 : 11-resto;

        return(dig1 ==digitos[12] && dig2 ==digitos[13]);
}


//verificar se é CPF ou CNPJ e retornar ID
int analisarCliente(const char *ID) {
    int qtdDig = 0;

    for (int i = 0; ID[i] != '\0'; i++)
        if (isdigit((unsigned char)ID[i]))
            qtdDig++;

    if (qtdDig == 11)
        return validarCPF(ID);

    if (qtdDig == 14)
        return validarCNPJ(ID);
    return 0;
}




//busca de cliente
Cliente* buscarCliente(ListaC *lista, const char *termoBusca) {
    if(!lista || !termoBusca) 
        return NULL;
    for (int i = 0; i< lista->totalClientes;i++){
        if (strcmp(lista->clientes[i].ID, termoBusca)==0)
            return &lista->clientes[i];

    }
    return NULL;
}

void inserirCliente(ListaC *lista) {}

int removerCliente(ListaC *lista, int id){
    for (int i=0; i< lista->totalClientes; i++){
        if (lista->clientes[i].IDcadastro==id){
            lista->clientes[i].ativo=0;
            return 1;
        }
    }
    return 0;
}

int editarCliente(ListaC *lista, int id){
    return 0; //vai implementar interface
}

void listarClientes(ListaC *lista, int id){
    for (int i=0; i< lista->totalClientes; i++){
        Cliente *c = &lista->clientes[i];
        if (c->ativo)
            printf("%d - %s - %s\n", c->IDcadastro, c->nome, c->ID);

    }
}

ListaC* carregarCcsv(const char *f){
    return NULL;
}


void salvarClientesCSV(ListaC *lista) {
    FILE *arq = fopen(CLIENTES_CSV, "w");
    if (!arq) {
        printf("Erro ao abrir %s para escrita.\n", CLIENTES_CSV);
        return;
    }

    // Cabeçalho (opcional)
    fprintf(arq, "IDcadastro;Nome;Documento;Ativo\n");

    for (int i = 0; i < lista->totalClientes; i++) {
        Cliente *c = &lista->clientes[i];
        fprintf(arq, "%d;%s;%s;%d\n",
                c->IDcadastro,
                c->nome,
                c->ID,
                c->ativo);
    }

    fclose(arq);
}

void appendClienteCSV(Cliente *c) {//vai adicionar uma linha nova sem mexer no q esta salvo
    FILE *arq = fopen(CLIENTES_CSV, "a");

    if (!arq) {
        printf("Erro ao abrir %s para adicionar.\n", CLIENTES_CSV);
        return;
    }

    fprintf(arq, "%d;%s;%s;%d\n",
            c->IDcadastro,
            c->nome,
            c->ID,
            c->ativo);

    fclose(arq);
}

void carregarClientesCSV(ListaC *lista) {
    FILE *arq = fopen(CLIENTES_CSV, "r");

    if (!arq) {
        //lista vazia
        lista->totalClientes = 0;
        return;
    }

    char linha[256];
    fgets(linha, 256, arq); // ignorar cabeçalho

    lista->totalClientes = 0;

    while (fgets(linha, 256, arq)) {
        Cliente c;
        sscanf(linha, "%d;%99[^;];%19[^;];%d",
               &c.IDcadastro,
               c.nome,
               c.ID,
               &c.ativo);

        lista->clientes[lista->totalClientes++] = c;
    }

    fclose(arq);
}

void atualizarClienteCSV(ListaC *lista) { //atualiza cadastro existente
    salvarClientesCSV(lista);
}





