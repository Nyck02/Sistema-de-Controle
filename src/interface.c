#include <stdio.h> 
#include <curses.h> 
#include <stdlib.h>


void MenuPrincipal(){

    initscr(); //para iniciar a tela e o PDCurses 
    keypad(stdscr, TRUE); // para teclas especiais 
    char *opções[] ={ 

        "Cliente",
        "Produto",
        "Pedido",

    }
    int total_opcoes = 3;
    int selecao_atual = 0;
    int c; //tecla selecionada
    int i; 
    int escolhaMenuPrincipal;

    do{
        clear();

        mvprintw(2,3"---MENU PRINCIPAL---");

        //Loop para exibir as opções 
        for(i=0; i<total_opcoes;i++){

            //Fazendo a seta > 
            //se a opção for igual a seleção, indica que o usuario está com o cursor(seta) em cima da opção
            if(i == seleção_atual){
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
    } while (c != 10 || selecao_atual != 4);

    if( c== 10){
        clear();
        refresh();

        //chamando a função selecionada
        switch(selecao_atual){ 
        case 0: MostrarMenuCliente (), break;
        case 1: MostrarMenuProduto (), break;
        case 2: MostrarMenuPedido (), break; 
        
        }

    }

}