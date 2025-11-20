#include<stdio.h>
#include<stdlib.h>
#include "../include/func.h"

int main()
{
    // Variáveis iniciais
    int opt = 0;
    Catalogo *catalogo = (Catalogo*) malloc(sizeof(Catalogo)); // Catálogo onde ficará as especificações dos produtos da rede
    DBLojas *db = db_aloc();
    Carrinho *car = c_aloc();

    // Fluxo do programa
    while(opt >= 0)
    {
        printf("\nBem-vindo ao sistema de estoque! A seguir as opções:\n");
        printf("\n[1] Carregar dados\n[2] Pesquisa\n[3] Carrinho\n[4] Verificar disponibilidade\n[5] Finalizar compra\n[6] Relatórios\n");
        printf("\nDigite aqui: ");
        scanf("%d", &opt);

        switch(opt)
        {
            case 1:
                {
                    carrega(catalogo, db);
                } break;
            case 2:
                {
                    pesquisa(catalogo->p_item);
                } break;
            case 3:
                {
                    carrinho();
                } break;
            case 4:
                {
                    verifica_dis();
                } break;
            case 5:
                {
                    // Parte que você implementa: finalização da compra
                    int id_filial;
                    printf("\nDigite o ID da filial para finalizar a compra: ");
                    scanf("%d", &id_filial);

                    if (!finaliza(car, db, catalogo, id_filial)) {
                        printf("\nVenda cancelada: nenhum item disponível para retirada nesta filial.\n");
                    } else {
                        printf("\nCompra finalizada com sucesso!\n");
                    }
                } break;
            case 6:
                {
                    relatorio(db);
                } break;
            default:
                {
                    printf("\nComando não encontrado, tente novamente.\n");
                } break;
        }
    }

    return 0;
}
