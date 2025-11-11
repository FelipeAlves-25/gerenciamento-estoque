#include<stdio.h>
#include<stdlib.h>
#include "../include/func.h"

// Cria um novo item, já inserindo os elementos dentro dele
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

// Inicia o catálogo
void i_catalog(Catalogo *catalogo)
{
    FILE *produtos; // Ponteiro do arquivo
    Item *produto = NULL; // Produto a ser inserido no catálogo
    
    // Valores para especificar o item
    int id;
    char nome[STRLEN];
    float valor;

    produtos = fopen("./src/entradas/produtos_v2.txt", "r"); // Abre o arquivo

    // Verifica se o item foi aberto corretamente
    if(!produtos)
    {
        fprintf(stderr, "Erro ao abrir arquivo.\n");
        return;
    }

    // Fará o mapeamento do arquivo enquanto a função retornar maior que 0
    while(fscanf(produtos, "%d %s %f\n", &id, nome, &valor) > 0)
    {
        produto = aloca_item(id, nome, valor); // Insere os dados no item

        // Verifica se o catálogo esteja vazio
        if(catalogo->p_item == NULL)
        {
            catalogo->p_item = produto;
            catalogo->u_item = produto;
        }

        // Caso contrário
        else {
            catalogo->u_item->prox = produto;
            catalogo->u_item = produto;
        }
    }
}


void search_cat(Catalogo *catalogo)
{
    // Fará a pesquisa do item no catálogo

}
