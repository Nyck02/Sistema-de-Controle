#include <stdio.h>

void main() {

    //variáveis
int numero[10];

    //entrada 
    for(int i= 0; i<10; i++){
        printf("diga o número do elemento");
        scanf("%d", &numero[i]);
    }
    
    

    for(int i= 9; i>=0; i--){
        printf("%d \n", numero[i]);
    }
}