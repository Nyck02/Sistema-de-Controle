#include <stdio.h> 
#include <stdlib.h>
#define MAX 5



//estrutura pilha
struct pilha
{
    int pilha[MAX];
    int topo;
};

struct pilha2 
{
    int pilha2[MAX];
    int topo2;
};

typedef struct pilha PILHAS;
PILHAS s;
typedef struct pilha2 PILHA2;
PILHA2 p;

//preencher a pilha 
void push() {
    int num; 
    if(s.topo == (MAX - 1)) { // verficar se tá cheia 
        printf ("Pilha está cheia");
        return;
    } else {
        printf("Digite o número: \n ");
        scanf("%d", &num);
        s.topo = s.topo +1;
        s.pilha[s.topo] = num;

    }
    return;
}

//função criar a função invertida 

void push_inverte(int valor){
    int num;
    if(p.topo2 == (MAX - 1)) {
        printf("Pilha está cheia");
        return;
    } else {
        p.topo2 = p.topo2 +1;
        p.pilha2[p.topo2] = valor;
    }
    return;
}

//função desimpilhar 

int pop() {

    int num; 
    if (s.topo == -1 ) {

        printf("Pilha está vazia \n");
        return (s.topo);
    } else {
        num = s.pilha[s.topo];
        s.topo = s.topo - 1;
        return num; 

    }
}

//exibir 
void exibir() {
    int i; 
    if(p.topo2 == -1 ){
        printf("pilha vazia \n");
        return;
    } else {
        printf("\n Elementos \n ");
        for (i=p.topo2; i>=0; i--) {
            printf("%d \n", p.pilha2[i]);
        }
    }
    printf("\n");
}
    


//objetivo: criar uma pilha e inverte-la 
void main ()
{
    
    int i;
    s.topo= -1;
    p.topo2= -1;
    int elem = 0; 
 
    printf ("OPERAÇÕES DA PILHA\n");
    
    //criar uma pilha
    
    for(i=0;i<MAX; i++) {
        push();
    }

    //desimpilhar enquanto em pilha outra
    for(i=0; i<MAX; i++){
        
        elem = pop();
        if(elem != -1){
           push_inverte(elem); 
        } else {
            break;
        }
        

    }

    //exibir a pilha invertida 
     
        exibir();


}
