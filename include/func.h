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

// Base de dados do programa
typedef struct dblojas {
    Filial *prim;
    Filial *ult;
} DBLojas;

// Funções do catálogo
Item *aloca_item(int id, char *nome, float valor);
void i_catalog(const char *dir, Catalogo *catalogo);
void search_cat(Catalogo *catalogo);

// Funções dos itens do estoque
IEstoque *ie_aloca(int id, int qtd);
void *ie_load(Filial *f, int id);

// Funções das filiais
Filial *f_aloc(int id, char *nome);

// Funções do carrinho
Carrinho *c_aloc();

// Funções da base de dados
DBLojas *db_aloc();
void load_db(const char *dir, DBLojas *db);

// Funções do programa na main
void carrega(Catalogo *c, DBLojas *db); // Função 1
void pesquisa(); // Função 2
void carrinho(); // Função 3
void verifica_dis(); // Função 4
void finaliza(); // Função 5
void relatorio(); // Função 6

#endif