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

// Fará a pesquisa do item no catálogo
Item *search_cat(Item *cat, int id, char *desc)
{
    int i, v = 1;

    while(cat != NULL)
    {
        if(id == cat->id)
            break;
        else if(desc != NULL && *desc == *(cat->nome))
        {
            for(i=0; i<STRLEN; i++)
            {
                if(*(cat->nome + i) != *(desc + i))
                {
                    v = 0;
                    break;
                }
            }

            break;
        }

        cat = cat->prox;
    }

    return cat;
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

Carrinho *c_aloc()
{
    Carrinho *new = (Carrinho*) malloc(sizeof(Carrinho));

    if(new == NULL) return NULL;

    new->total = 0;
    new->itens = NULL;

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

void carrega(Catalogo *cat, DBLojas *db)
{
    /* Carrega os arquivos e os dados necessários,
       para o caso de não carregar, o programa
       voltará ao início, exibindo qual dos dados
       não foi carregado.
    */
    i_catalog("./src/entradas/produtos_v2.txt", cat);
    load_db("./src/entradas/filiais_v2.txt", db);
    if(db->prim == NULL || cat->p_item == NULL)
    {
        printf("\nERRO: Não foi possível carregar os arquivos.");
        return;
    }
    else
        printf("\nArquivos carregados com sucesso!\n");
}

void pesquisa(Item *cat)
{
    int opt, id;
    char nome[STRLEN];
    Item *i_enc = NULL;

    printf("\nComo deseja realizar a pesquisa?\n");
    printf("\n[1] Código\n[2] Nome/descrição\n[3] Ambos\n");
    printf("\nDigite aqui: ");
    scanf("%d", &opt);

    switch(opt)
    {
        case 1:
            {
                printf("\nDigite aqui o código do item: ");
                scanf("%d", &id);

                i_enc = search_cat(cat, id, NULL);
            } break;
        case 2:
            {
                int c;

                printf("\nDigite aqui o nome do item: ");
                
                while((c = getchar()) != '\n' && c != EOF){}
                fgets(nome, sizeof(nome), stdin);

                i_enc = search_cat(cat, 0, nome);
            } break;
        case 3:
            {
                printf("\nDigite aqui o código do item: ");
                scanf("%d", &id);

                printf("\nAgora, digite o nome do item: ");
                scanf("%[^\n]", nome);

                i_enc = search_cat(cat, id, nome);
            } break;
        default:
            {
                printf("\nComando não encontrado, tente novamente.\n");
            } break;
    }

    if(i_enc != NULL)
    {
        printf("\nA seguir as informações do produto encontrado:\n");
        printf("\nID do produto: %d\nNome/descrição: %s\nValor: R$%.2f\n", i_enc->id, i_enc->nome, i_enc->valor);
    }
    else {
        printf("\nProduto não encontrado, tente novamente.\n");
    }
}

void carrinho()
{

}

void verifica_dis()
{

}

// Verifica se a filial atende 100% do carrinho
int filial_apta(Carrinho *car, Filial *filial) {
    ICarrinho *item = car->itens;
    while (item != NULL) {
        IEstoque *e = filial->estoque;
        int encontrado = 0;
        do {
            if (e->id == item->id) {
                if (e->qtd < item->qtd)
                    return 0;
                encontrado = 1;
                break;
            }
            e = e->prox;
        } while (e->prox != filial->estoque);
        if (!encontrado)
            return 0;
        item = item->prox;
    }
    return 1;
}

// Ajusta o carrinho com base no estoque da filial
void ajusta_carrinho(Carrinho *car, Filial *filial) {
    ICarrinho *item = car->itens;
    ICarrinho *anterior = NULL;
    while (item != NULL) {
        IEstoque *e = filial->estoque;
        int disponivel = 0;

        do {
            if (e->id == item->id) {
                disponivel = e->qtd;
                break;
            }
            e = e->prox;
        } while (e->prox != filial->estoque);

        if (disponivel == 0) {
            car->total -= item->qtd * item->valor;
            if (anterior == NULL)
                car->itens = item->prox;
            else
                anterior->prox = item->prox;
            free(item);
            item = (anterior == NULL) ? car->itens : anterior->prox;
        } else if (disponivel < item->qtd) {
            car->total -= (item->qtd - disponivel) * item->valor;
            item->qtd = disponivel;
            anterior = item;
            item = item->prox;
        } else {
            anterior = item;
            item = item->prox;
        }
    }
}

// Abate o estoque da filial com os itens do carrinho
void abate_estoque(Carrinho *car, Filial *filial) {
    ICarrinho *item = car->itens;
    while (item != NULL) {
        IEstoque *e = filial->estoque;
        while (e != NULL) {
            if (e->id == item->id) {
                e->qtd -= item->qtd;
                break;
            }
            e = e->prox;
        }
        item = item->prox;
    }
}

int finaliza(Carrinho *car, DBLojas *db, Catalogo *cat, int id_filial) {
    Filial *filial = db->prim;
    while (filial != NULL && filial->id != id_filial)
        filial = filial->prox;

    if (filial == NULL) {
        printf("\nFilial não encontrada.\n");
        return 0;
    }

    if (!filial_apta(car, filial)) {
        ajusta_carrinho(car, filial);
        if (car->itens == NULL)
            return 0;
    }

    abate_estoque(car, filial);
    relatorio_pedido(car, id_filial);
    return 1;
}

void relatorio(DBLojas *db)
{

}

// Relatório do pedido finalizado (exibe no terminal)
void relatorio_pedido(Carrinho *car, int id_filial)
{
    printf("\nPedido finalizado na filial %d\n", id_filial);
    ICarrinho *item = car->itens;

    while(item)
    {
        float subtotal = item->qtd * item->valor;
        printf("Produto %d \n Qtd: %d \n Preço: %.2f \n Subtotal: %.2f\n", item->id, item->qtd, item->valor, subtotal);
        item = item->prox;
    }

    printf("\nTOTAL: %.2f\n", car->total);
}

// Relatório de diagnóstico por filial (exibe no terminal)
void relatorio_diagnostico(Carrinho *car, DBLojas *db, Catalogo *cat)
{
    Filial *filial = db->prim;

    while(filial)
    {
        int apta = 1;
        ICarrinho *item = car->itens;

        printf("\nFilial %d \n %s\n", filial->id, filial->nome);

        while(item)
        {
            IEstoque *e = filial->estoque;
            int disponivel = 0;

            while(e)
            {
                if(e->id == item->id)
                {
                    disponivel = e->qtd;
                    break;
                }
                e = e->prox;
            }

            if(disponivel < item->qtd)
            {
                apta = 0;
                printf("  Faltando: Produto %d \n Qtd faltante: %d\n", item->id, item->qtd - disponivel);
            }

            item = item->prox;
        }

        if(apta)
            printf("Filial apta para atender 100%% do carrinho\n");

        filial = filial->prox;
    }
}
