#include "../include/cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#define ARQ_CLIENTES "data/clientes.csv"

// inicio da lista - 0
void inicio_lista(ListaClientes *lista) {
    lista->clientes = NULL;
    lista->totalClientes = 0;
    lista->capacidade = 0;
}

//