#include<stdio.h>
#include<stdlib.h>
#include "../include/func.h"

Item *aloca_item(int id, char *nome, float valor)
{
    Item *new = NULL;
    new = (Item*) malloc(sizeof(Item));

    if(new)
    {
        int i;

        new->id = id;
        new->valor = valor;
        new->prox = NULL;

        for(i=0; i<STRLEN; i++)
        {
            *(new->nome+i) = *(nome+i);
        }
    }

    return new;
}

void i_catalog(Catalogo *catalogo)
{
    FILE *produtos;
    Item *produto = NULL;
    int id;
    char nome[STRLEN];
    float valor;

    produtos = fopen("./src/entradas/produtos_v2.txt", "r");

    if(!produtos)
    {
        fprintf(stderr, "Erro ao abrir arquivo.\n");
        return;
    }

    while(fscanf(produtos, "%d %s %f\n", &id, nome, &valor) > 0)
    {
        produto = aloca_item(id, nome, valor);

        if(catalogo->p_item == NULL)
        {
            catalogo->p_item = produto;
            catalogo->u_item = produto;
        }
        else {
            catalogo->u_item->prox = produto;
            catalogo->u_item = produto;
        }
    }
}

void search_cat(Catalogo *catalogo)
{

}
