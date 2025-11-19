#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include pedido.h 

//Lista global de pedidos
Pedido listaPedidos[MAX_PEDIDOS];
int qtdPedidos = 0; 

//função para achar o pedido pelo ID
int encontrarPedidoPorId(int id) {
  for(int i = 0; i < qtdPedidos; i++){
    if(listaPedidos[i].id == id){
      return i;
    }
  }
return -1 //quando não encontra pedido 
  } 
//Função para encontrar um pedido pelo clienteId
int encontrarPedidoPorClienteId(int clienteId) {
  for(int i= 0; i < qtdPedidos. i++) {
   if(listaPedidos[i].clienteId == clienteId) {
       return i;
   }
  }
    return -1;
}
