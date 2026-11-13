#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/* Cada modulo contem sua estrutura, variaveis globais e funcoes. */
#include "leitores.h"
#include "livros.h"
#include "emprestimos.h"
#include "relatorios.h"

/* =========================================================
   MENU PRINCIPAL
   ========================================================= */

void limparTela(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void cabecalho(void) {
    printf("\n======================================================\n");
    printf("                 SISTEMA DE BIBLIOTECA                \n");
    printf("======================================================\n");
}

void menuPrincipal(void) {
    int opcao;

    do {
        limparTela();
        cabecalho();

        printf("\n========== MENU PRINCIPAL ==========\n");
        printf("1 - Cadastro de leitores\n");
        printf("2 - Catalogo de livros\n");
        printf("3 - Emprestimos e devolucoes\n");
        printf("4 - Consultas e relatorios\n");
        printf("0 - Sair\n");
        printf("------------------------------------\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida. Digite um numero.\n");
            while (getchar() != '\n' && !feof(stdin)) {
            }
            opcao = -1;
            printf("Pressione ENTER para continuar...");
            getchar();
            continue;
        }

        switch (opcao) {
            case 1:
                moduloClientes();
                break;
            case 2:
                modulo_livros();
                break;
            case 3:
                moduloEmprestimos();
                break;
            case 4:
                moduloRelatorios();
                break;
            case 0:
                printf("\nEncerrando o sistema. Ate logo!\n");
                break;
            default:
                printf("\nOpcao invalida! Escolha uma opcao de 0 a 4.\n");
                printf("Pressione ENTER para continuar...");
                while (getchar() != '\n' && !feof(stdin)) {
                }
                getchar();
                break;
        }

    } while (opcao != 0);
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");

    carregarLeitoresCSV();
    carregarLivrosCSV();
    carregarEmprestimosCSV();
    carregarRelatoriosCSV();

    menuPrincipal();
    return 0;
}
