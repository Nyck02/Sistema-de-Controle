#include <stdio.h> 
#include <ncurses.h> 
#include <stdlib.h>
#include "produto.h"
#include "interface.h"

void MostrarMenuProduto();
void MostrarMenuCliente();
void MostrarMenuPedido();
void ListarProdutos(); 

void lerString(int y, int x, int tamanhoMax, char *destino) {
    echo();          
    curs_set(1);     
    
    
    mvprintw(y, x, "[");
    for(int i=0; i<tamanhoMax; i++) printw("_");
    printw("]");
    
    move(y, x + 1); 
    getnstr(destino, tamanhoMax); 
    
    noecho();        
    curs_set(0);     
}

void MenuPrincipal(){
    
    
    int selecao_atual = 0;
    int total_opcoes = 4;
    int c; //tecla selecionada
    int i; 
    
    keypad(stdscr, TRUE); // para teclas especiais 
    char *opcoes[] ={ 

        "Cliente",
        "Produto",
        "Pedido",
        "Sair"

    };

    do{
        clear();

        mvprintw(2,3, "---MENU PRINCIPAL---");

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

        //dar uma olhada nas outras funções como ESC para adicionar 
        } 
    }
        while (c != 10 && c != 13);

        if( c== 10 || c == 13){
            clear();
            refresh();

            //chamando a função selecionada
            switch(selecao_atual){ 
                case 0: MostrarMenuCliente (); break;
                case 1: MostrarMenuProduto (); break;
                case 2: MostrarMenuPedido (); break; 
                case 3: return;
            
                }
                
            }
        

    
}

void MostrarMenuProduto() {

    //variaveis 
    int i,c; 
    initscr(); //para iniciar a tela e o PDCurses 
    keypad(stdscr, TRUE); // para teclas especiais 
    int total_opcoes = 6;
    int selecao_atual = 0;


    //vetor de opcoes 

    char *opcoes[] ={

        "Cadastrar",
        "Listar",
        "Consultar",
        "Editar",
        "Remover",
        "Voltar"

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
        } 
        
    }   
    
    while (c != 10 && c != 13);

        if( c== 10 || c == 13){
                clear();
                refresh();

                //chamando a função selecionada
                    switch(selecao_atual){ 
                    case 0: CadastrarProduto(); break;
                    case 1: ListarProdutos(); break;
                    case 2: mvprintw(LINES-2, 2, "Em breve..."); getch(); break;
                    case 3: mvprintw(LINES-2, 2, "Em breve..."); getch(); break;
                    case 4: RemoverProduto(); break; 
                    case 5: break; //voltar ao menu de  inicio
                    }
                }
        
    
}

void MostrarMenuCliente() {
    clear();
    mvprintw(10, 10, "Menu Clientes (Em Breve)... Pressione algo.");
    getch();
}

void MostrarMenuPedido() {
    clear();
    mvprintw(10, 10, "Menu Pedidos (Em Breve)... Pressione algo.");
    getch();
}


