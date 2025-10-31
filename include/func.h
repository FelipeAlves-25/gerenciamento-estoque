#ifndef FUNC_H
#define FUNC_H
#define STRLEN 40

// Informações do produto
typedef struct item {
    int id;
    char nome[STRLEN];
    float valor;
    struct item *prox;
} Item;

// Catálogo dos produtos
typedef struct catalogo {
    Item *p_item;
    Item *u_item;
} Catalogo;

// Informações do estoque de cada produto nas lojas
typedef struct iestoque {
    int id;
    int qtd;
    struct iestoque *prox;
} IEstoque;

// Informações da filial
typedef struct filial {
    int id;
    char nome[STRLEN];
    IEstoque *estoque;
    struct filial *prox;
} Filial;

// Itens adicionado no carrinho
typedef struct icarrinho {
    int id;
    int qtd;
    float valor;
    struct icarrinho *prox;
} ICarrinho;

// Carrinho
typedef struct carrinho {
    float total;
    ICarrinho *itens;
} Carrinho;

// Funções do catálogo
Item *aloca_item(int id, char *nome, float valor);
void i_catalog(Catalogo *catalogo);
void search_cat(Catalogo *catalogo);

// Funções do programa
void init();
void carrega();
void pesquisa();
void carrinho();
void verifica_dis();

#endif