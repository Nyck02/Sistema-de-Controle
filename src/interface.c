#include <stdio.h> 
#include <ncurses.h> 
#include <stdlib.h>
#include "cliente.h"

extern ListaC listaClientesGlobal; // definida no main

// Protótipo das funções, para chamar as funções 
void MostrarMenuCliente();
void MostrarMenuProduto(); 
void MostrarMenuPedido(); 
// Protótipos das funções do menu de Produto
void Cadastrar(); 
void Listar();
void Consultar();
void Editar();
void Remover();

//Prototipo das funcoes, menu cliente
void CadastrarCliente();
void ListaCliente();
void ConsultaCliente();
void EditarCliente();
void RemoverCliente();


void Cadastrar() {
    //Chamar uma função especial com opção de cadastro como: "Modelo, Ano de fabricação, Marca, etc"
clear();
mvprintw(4, 4, "Função Cadastrar... Pressione algo para voltar."); 
    getch();
}

void Listar(){
    //Apenas exibir todos os produtos cadastrados
    //E se tiver um produto igual (ex: 4 Notebook Lenovo)
    //Seguirá alguma ordem? Do maior codigo até o menor, ou por categoria? Poderia ter algum filtro ou ferramenta de pesquisa? 
clear();
mvprintw(4, 4, "Função Listar... Pressione algo para voltar."); 
    getch();
}

void Consultar(){
    //Exibir a listagem e é possível selecionar o produto e abrir os dados
clear();
mvprintw(4, 4, "Função Consultar... Pressione algo para voltar."); 
    getch();
}

void Editar() {
    //Agora exibe, consulta e tem como editar tudo (Preço, Cadastro, quantidade do estoque, etc)
clear();
    mvprintw(4, 4, "Função Editar ... Pressione algo para voltar."); 
    getch();
}

void Remover() {
    //Exibe, consulta e remove 
clear();
mvprintw(4, 4, "Função Remover... Pressione algo para voltar."); 
    getch();
}

void MostrarMenuPrincipal(){ 

    int selecao_atual = 0;
    int total_opcoes = 3;
    int c; //tecla selecionada
    int i; 
    
    char *opcoes[] ={ 
        "Cliente",
        "Produto",
        "Pedido"
    };

    do{
        clear();

        mvprintw(2,3, "---MENU PRINCIPAL---");
        mvprintw(10, 3, "Pressione ESC para sair.");

        //Loop para exibir as opções 
        for(i=0; i<total_opcoes;i++){

            //Fazendo a seta > 
            //se a opção for igual a seleção, indica que o usuario está com o cursor(seta) em cima da opção
            if(i == selecao_atual){
                attron(A_REVERSE); //destaca a opção
                mvprintw(4 + i, 4, "> %s", opcoes[i]);
                attroff(A_REVERSE); //tira o destaque 
            } 
            
            else {
                //deixar tudo normal
                mvprintw(4 + i, 4, "%s", opcoes[i]);
            }
        }

        c=getch(); 
    

        //Movimentos 

        switch(c) { 
            case KEY_UP: // pressionando a tecla cima, movimenta para cima 
            selecao_atual = (selecao_atual == 0) ? total_opcoes -1 : selecao_atual -1;
            break;
            case KEY_DOWN: //pressioando a tecla baixo, movimenta para baixo
            selecao_atual = (selecao_atual == total_opcoes -1) ? 0 : selecao_atual +1;
            break; 
            case 10: 
            break; 
            //função ENTER 
            case 27:
            return;
            //função ESC

            //dar uma olhada nas outras funções como ESC para adicionar 
        } 
    }
    while (c != 10 ); 
        if( c== 10){
            //chamando a função selecionada
            switch(selecao_atual){ 
            case 0: MostrarMenuCliente (); break;
            case 1: MostrarMenuProduto (); break;
            case 2: MostrarMenuPedido (); break; 
        
            }
        
            MostrarMenuPrincipal();
            
        }
    
}

void MostrarMenuProduto() { 
    
    //variaveis 
    int i,c; 
    int total_opcoes = 5;
    int selecao_atual = 0;


    //vetor de opcoes 

    char *opcoes[] ={

        "Cadastrar",
        "Listar",
        "Consultar",
        "Editar",
        "Remover"

    };

    //estrutura de opções 

    do{
        clear();

        mvprintw(2, 3, "    MODULO PRODUTOS   ");

        for(i=0;i<total_opcoes;i++){
            
            if(i == selecao_atual) {

                attron(A_REVERSE);
                mvprintw(4 + i, 4, " > %s", opcoes[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(4 + i, 4, " %s", opcoes[i]);
            }

        }

        c=getch(); //Capiturei a tecla clicada
    
        //Movimentos, igual do Menu Principal 
        switch(c) { 

            case KEY_UP: // pressionando a tecla cima, movimenta para cima 
            selecao_atual = (selecao_atual == 0) ? total_opcoes -1 : selecao_atual -1;
            break;
            case KEY_DOWN: //pressioando a tecla baixo, movimenta para baixo
            selecao_atual = (selecao_atual == total_opcoes -1) ? 0 : selecao_atual +1;
            break; 
            case 10: 
            break; 
            return; //retornar menu principal
            case 27:
            return;
            //função ESC

        } 
    }

    while(c != 10);
        
        //tecla ENTER

        if( c== 10){
        clear();
        refresh();

        //chamando a função selecionada
            switch(selecao_atual){ 
                case 0: Cadastrar(); break;
                case 1: Listar(); break;
                case 2: Consultar(); break;
                case 3: Editar(); break;
                case 4: Remover(); break; 
                //voltar ao menu de  inicio
            }
        MostrarMenuProduto();
        }
    
} 


int main() {
    
    initscr();
    keypad(stdscr, TRUE);

    MostrarMenuPrincipal();
    endwin();
    return 0;
    
}

void inputText(int y, int x, char *buffer, int max) {
    mvprintw(y, x, "");
    echo();
    getnstr(buffer, max -1);
    noecho();
}

void MostrarMenuCliente (){
    int selecao=0;
    int tecla;
    int total_opcoes=5;

    char *opcoes[]={
        "Cadastrar Cliente",
        "Listar Clientes",
        "Consultar Cliente",
        "Editar Cliente",
        "Remover Cliente"
    };

    do {
        clear();
        mvprintw(2,3, "--- MENU CLIENTE ---");
        mvprintw(10,3, "Pressione ESC para voltar");

        for(int i=0; i<total_opcoes;i++){
            if(i==selecao){
                attron(A_REVERSE);
                mvprintw(4+i,4,"> %s", opcoes[i]);
                attroff(A_REVERSE);

            } else {
                mvprintw(4+i,4, "%s", opcoes[i]);
            }
        }

        tecla=getch();

        switch(tecla){
            case KEY_UP:
                selecao =(selecao==0)? total_opcoes -1: selecao-1;
                break;

            case KEY_DOWN:
                selecao=(selecao==total_opcoes-1)? 0: selecao+1;
                break;

            case 27: //tecla ESC
                return;

            case 10: //tecla ENTER
                clear();

                if(selecao==0){//selecao de cadastro
                    Cliente c;
                    memset(&c, 0, sizeof(c));
                    c.ativo = 1;
                    c.IDcadastro = listaClientesGlobal.totalClientes + 1;

                    mvprintw(2,2, "Nome: ");
                    inputText(2,10, c.nome, 100);

                    mvprintw(3,2, "CPF/CNPJ: ");
                    inputText(3,14, c.ID, 20);

                    if(!analisarCliente(c.ID)){
                        mvprintw(5,2, "Documento Invalido");
                    } else {
                        addClienteLista(&listaClientesGlobal, c);
                        mvprintw(5,2, "Cliente cadastrado!");
                    }
                    getch();
                }

                else if (selecao==1){ //selecao de lista
                    mvprintw(1, 2, "Lista de Clientes:");
                    int y = 3;

                    for (int i = 0; i < listaClientesGlobal.totalClientes; i++){
                        Cliente *c = &listaClientesGlobal.clientes[i];

                        if(c->ativo){
                            mvprintw(y++,2, "%d - %s - %s",
                                     c->IDcadastro, c->nome, c->ID);
                        }
                    }
                    mvprintw(20,2, "Pressione qualquer tecla.");
                    getch();
                }

                else if (selecao==2){ //selecao de consulta
                    char doc[30];

                    mvprintw(2,2, "CPF/CNPJ: ");
                    inputText(2,14, doc, 30);

                    Cliente *c = buscarCliente(&listaClientesGlobal, doc);

                    if(c && c->ativo){
                        mvprintw(4,2, "Nome: %s", c->nome);
                        mvprintw(5,2, "ID: %s", c->ID);
                    } else {
                        mvprintw(4,2, "Nao encontrado.");
                    }
                    getch();
                }

                
                else if (selecao==3){//selecao p editar
                    char doc[30];

                    mvprintw(2,2, "CPF/CNPJ p/ editar: ");
                    inputText(2,25, doc, 30);

                    Cliente *c = buscarCliente(&listaClientesGlobal, doc);

                    if(c && c->ativo){
                        mvprintw(4,2, "Novo nome: ");
                        inputText(4,15, c->nome, 100);

                        mvprintw(6,2, "Alterado");
                    } else {
                        mvprintw(4,2, "Nao encontrado.");
                    }
                    getch();
                }

                else if (selecao==4){//selecao para reomver
                    char doc[30];

                    mvprintw(2,2, "CPF/CNPJ p/ remover: ");
                    inputText(2,26, doc, 30);

                    Cliente *c = buscarCliente(&listaClientesGlobal, doc);

                    if(c && c->ativo){
                        c->ativo = 0;
                        mvprintw(4,2, "Removido!");
                    } else {
                        mvprintw(4,2, "Nao encontrado.");
                    }
                    getch();
                }

                break;
        }

    } while(1);
}


