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
void i_catalog(const char *dir, Catalogo *catalogo)
{
    FILE *produtos; // Ponteiro do arquivo
    Item *produto = NULL; // Produto a ser inserido no catálogo
    
    // Valores para especificar o item
    int id;
    char nome[STRLEN];
    float valor;

    produtos = fopen(dir, "r"); // Abre o arquivo

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

    fclose(produtos);
}


void search_cat(Catalogo *catalogo)
{
    // Fará a pesquisa do item no catálogo

}

// Aloca o item do estoque
IEstoque *ie_aloca(int id, int qtd)
{
    IEstoque *new = (IEstoque*) malloc(sizeof(IEstoque));
    
    if(new == NULL) return NULL;

    new->id = id;
    new->qtd = qtd;
    new->prox = NULL;

    return new;
}

// Carrega o estoque na filial correspondente
void *ie_load(Filial *f, int id)
{
    int item_id, f_id, qtd;
    FILE *estoques;
    IEstoque *new = NULL, *aux = NULL;

    estoques = fopen("./src/entradas/estoques_v2.txt", "r");

    while(fscanf(estoques, "%d %d %d\n", &f_id, &item_id, &qtd) > 0)
    {
        if(f_id == id)
        {
            new = ie_aloca(item_id, qtd);

            if(f->estoque == NULL)
            {
                new->prox = new;
                f->estoque = new;
            }
            else {
                aux = f->estoque;

                while(aux->prox != f->estoque)
                    aux = aux->prox;
                
                aux->prox = new;
                new->prox = f->estoque;
                f->estoque = new;
            }
        }
    }

    fclose(estoques);
}

// Aloca a filial
Filial *f_aloc(int id, char *nome)
{
    int i;
    Filial *new = (Filial*) malloc(sizeof(Filial));

    if(new == NULL) return NULL;

    new->id = id;
    new->estoque = NULL;

    for(i=0; i<STRLEN; i++)
        *(new->nome + i) = *(nome + i);
    
    return new;
}

// Inicia a base de dados
DBLojas *db_aloc()
{
    DBLojas *new = (DBLojas*) malloc(sizeof(DBLojas));

    if(new == NULL) return NULL;

    new->prim = NULL;
    new->ult = NULL;

    return new;
}

// Carrega as filiais na base de dados
void load_db(const char *dir, DBLojas *db)
{
    FILE *info;

    Filial *new = NULL;

    int id;
    char nome[STRLEN];
    char linha[256];

    info = fopen(dir, "r");

    if(!info) fprintf(stderr, "\nNão foi possível abrir o arquivo.");
    
    while(fgets(linha, sizeof(linha), info))
    {
        if(sscanf(linha, "%d %[^\n]", &id, nome) == 2)
        {
            new = f_aloc(id, nome);
            ie_load(new, new->id);
            if(db->prim == NULL)
            {
                db->prim = new;
                db->ult = new;
            }
            else {

                db->ult->prox = new;
                db->ult = new;
            }
        }
    }
}

/* Funções do programa
   
   As funções a seguir são as funções de controle do programa,
   por exemplo a função 1 (carrega), que irá carregar todos os
   dados do programa, e assim por diante
*/

void carrega(Catalogo *c, DBLojas *db)
{
    /* Carrega os arquivos e os dados necessários,
       para o caso de não carregar, o programa
       voltará ao início, exibindo qual dos dados
       não foi carregado.
    */
    i_catalog("./src/entradas/produtos_v2.txt", c);
    if(c->p_item == NULL)
    {
        printf("\nERRO: Não foi possível carregar o catálogo.");
        return;
    }

    load_db("./src/entradas/filiais_v2.txt", db);
    if(db->prim == NULL)
    {
        printf("\nERRO: Não foi possível carregar a base de dados.");
        return;
    }
}

void pesquisa();
void carrinho();
void verifica_dis();
void finaliza();
void relatorio();
