#include<stdio.h>
#include<stdlib.h>
#include "../include/func.h"

int main()
{
    Catalogo *catalogo = (Catalogo*) malloc(sizeof(Catalogo));
    i_catalog(catalogo);

    Item *aux = catalogo->p_item;
    while(aux != NULL)
    {
        printf("%d %s %f\n", aux->id, aux->nome, aux->valor);

        aux = aux->prox;
    }    

    return 0;
}
