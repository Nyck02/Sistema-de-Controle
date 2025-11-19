#include <stdio.h> 
#include <ncurses.h> 
#include <stdlib.h>


void MenuPrincipal(){
    
    
    int selecao_atual = 0;
    int total_opcoes = 3;
    int c; //tecla selecionada
    int i; 
    initscr(); //para iniciar a tela e o PDCurses 
    keypad(stdscr, TRUE); // para teclas especiais 
    char *opções[] ={ 

        "Cliente",
        "Produto",
        "Pedido"

    }

    
   

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

    c=getch(); //opa
    

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
    } while (c != 10 || selecao_atual != 4);

    if( c== 10){
        clear();
        refresh();

        //chamando a função selecionada
        switch(selecao_atual){ 
        case 0: MostrarMenuCliente (); break;
        case 1: MostrarMenuProduto (); break;
        case 2: MostrarMenuPedido (); break; 
        
        }

    }

    }
}

void MostrarMenuProduto() {

    //variaveis 
    int i,c; 
    initscr(); //para iniciar a tela e o PDCurses 
    keypad(stdscr, TRUE); // para teclas especiais 
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

        mvprintw(2, 3 "    MODULO PRODUTOS   ");

        for(i=0;i<total_opcoes;i++){
            
            if(i == selecao_atual) {

                attron(A_REVERSE);
                mvprintw(4 + i, 4 " > %s", opcoes[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(4 + i, 4 " %s", opcoes[i]);
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
    } while(c != 10 || selecao_atual != 4);
    
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
            case 5: break; //voltar ao menu de  inicio
        }
    }

}