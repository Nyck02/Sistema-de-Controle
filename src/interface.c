#include <stdio.h> 
#include <ncurses.h> 
#include <stdlib.h>

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
