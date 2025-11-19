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

//Função para encontrar um pedido pelo clienteID
int encontrarPedidoPorClienteId(int clienteId) {
  for(int i = 0; i < qtdPedidos; i++){
    if(listaPedidos[i].clienteId == clienteId){
     return i;
    }
  }
return -1 
  }
//Função para calcular o total do pedido com base nos itens 
double calcularTotalPedido(Pedido *pedido){
   double total = 0.0;
    for(int i = 0; i < pedido->qtdItens; i++) {
     total += pedido->itens[i].subtotal;
    }
return total;
}

//função para cadastrar um item njo pedido
void cadastrarItemPedido(int pedidoId, int produtoId, int quantidade, double preo) {
  int posicao = encontrarPedidoPorId(pedidoId);
   if(posicao == -1) {
    printf("Erro: Pedido com ID %d não encontrado.\n", pedidoId);
     return;
   }
Pedido *pedido = &listaPedidos[posicao];

   if(pedido->qtdItens >= MAX_ITENS_POR_PEDIDO) {
    printf("Erro: Limite maximo de itens por pedido atingido.\n");
     return;
   }



