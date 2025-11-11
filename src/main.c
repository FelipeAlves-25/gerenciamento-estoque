#include<stdio.h>
#include<stdlib.h>
#include "../include/func.h"

int main()
{
    Catalogo *catalogo = (Catalogo*) malloc(sizeof(Catalogo)); // Catálogo onde ficará as especificações dos produtos da rede
    i_catalog(catalogo); // inicia o catálogo

    // Testando se o catálogo está em funcionamento
    Item *aux = catalogo->p_item;
    while(aux != NULL)
    {
        printf("%d %s %f\n", aux->id, aux->nome, aux->valor);

        aux = aux->prox;
    }

    return 0;
}
