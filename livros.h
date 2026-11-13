#ifndef LIVROS_H
#define LIVROS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIVROS_MAX 50
#define LIVROS_CSV "livros.csv"

// -------------------- STRUCT E VARIAVEIS --------------------

// Nome: SAMUEL GODOY MEDEIROS DA SILVA
// RGM: 49707400

typedef struct livro {
    int idlivro;
    char nome_livro[50];
    char nome_autor[50];
    float preco;
    int quantidade;
} Livro;

struct livro livros[LIVROS_MAX];
int totalLivros = 0;
int proximoId = 1;

// -------------------- PROTOTIPOS --------------------

void modulo_livros(void);
void cadastrarLivro(void);
void listarBuscarLivros(void);
void editarLivro(void);
void removerLivro(void);

void salvarLivrosCSV(void);
void carregarLivrosCSV(void);

void limparEntradaLivros(void);
void lerTextoLivro(char texto[], int tamanho);

// -------------------- FUNCOES AUXILIARES --------------------

void limparEntradaLivros(void) {
    int caractere;

    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

void lerTextoLivro(char texto[], int tamanho) {
    int i;

    fgets(texto, tamanho, stdin);

    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == '\n') {
            texto[i] = '\0';
            break;
        }
    }
}

// -------------------- SALVAR LIVROS NO CSV --------------------

void salvarLivrosCSV(void) {
    FILE *arq;
    int i;

    arq = fopen(LIVROS_CSV, "w");

    if (arq == NULL) {
        printf("Erro ao salvar os livros!\n");
        return;
    }

    fprintf(arq, "idlivro;nome_livro;nome_autor;preco;quantidade\n");

    for (i = 0; i < totalLivros; i++) {
        fprintf(arq, "%d;%s;%s;%.2f;%d\n",
                livros[i].idlivro,
                livros[i].nome_livro,
                livros[i].nome_autor,
                livros[i].preco,
                livros[i].quantidade);
    }

    fclose(arq);
}

// -------------------- CARREGAR LIVROS DO CSV --------------------

void carregarLivrosCSV(void) {
    FILE *arq;
    char linha[200];

    totalLivros = 0;
    proximoId = 1;

    arq = fopen(LIVROS_CSV, "r");

    if (arq == NULL) {
        return;
    }

    // Pula a primeira linha, que contém os nomes das colunas.
    if (fgets(linha, sizeof(linha), arq) == NULL) {
        fclose(arq);
        return;
    }

    while (totalLivros < LIVROS_MAX &&
           fscanf(arq, "%d;%49[^;];%49[^;];%f;%d",
                  &livros[totalLivros].idlivro,
                  livros[totalLivros].nome_livro,
                  livros[totalLivros].nome_autor,
                  &livros[totalLivros].preco,
                  &livros[totalLivros].quantidade) == 5) {

        if (livros[totalLivros].idlivro >= proximoId) {
            proximoId = livros[totalLivros].idlivro + 1;
        }

        totalLivros++;
    }

    fclose(arq);
}

// -------------------- MENU DE LIVROS --------------------

void modulo_livros(void) {
    int opcao;

    do {
        printf("\n========== MODULO DE LIVROS ==========\n");
        printf("1 - Cadastrar livro\n");
        printf("2 - Listar e buscar livros\n");
        printf("3 - Editar livro\n");
        printf("4 - Remover livro\n");
        printf("0 - Voltar ao menu principal\n");
        printf("Escolha: ");

        scanf("%d", &opcao);
        limparEntradaLivros();

        switch (opcao) {
            case 1:
                cadastrarLivro();
                break;

            case 2:
                listarBuscarLivros();
                break;

            case 3:
                editarLivro();
                break;

            case 4:
                removerLivro();
                break;

            case 0:
                printf("Voltando ao menu principal...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);
}

// -------------------- CADASTRAR LIVRO --------------------

void cadastrarLivro(void) {
    if (totalLivros >= LIVROS_MAX) {
        printf("\nLimite de livros atingido!\n");
        return;
    }

    printf("\n========== CADASTRAR LIVRO ==========\n");

    livros[totalLivros].idlivro = proximoId;

    printf("Nome do livro: ");
    lerTextoLivro(livros[totalLivros].nome_livro, 50);

    printf("Nome do autor: ");
    lerTextoLivro(livros[totalLivros].nome_autor, 50);

    printf("Preco: ");
    scanf("%f", &livros[totalLivros].preco);
    limparEntradaLivros();

    printf("Quantidade: ");
    scanf("%d", &livros[totalLivros].quantidade);
    limparEntradaLivros();

    printf("\nLivro cadastrado com sucesso!\n");
    printf("ID do livro: %d\n", livros[totalLivros].idlivro);

    totalLivros++;
    proximoId++;

    salvarLivrosCSV();
}

// -------------------- LISTAR E BUSCAR LIVROS --------------------

void listarBuscarLivros(void) {
    int opcao;
    int i;
    int id;
    int encontrou;
    char busca[50];

    printf("\n========== LIVROS ==========\n");
    printf("1 - Listar todos os livros\n");
    printf("2 - Buscar livro pelo ID\n");
    printf("3 - Buscar livro pelo nome\n");
    printf("Escolha: ");

    scanf("%d", &opcao);
    limparEntradaLivros();

    switch (opcao) {
        case 1:
            if (totalLivros == 0) {
                printf("\nNenhum livro cadastrado.\n");
                return;
            }

            for (i = 0; i < totalLivros; i++) {
                printf("\nID: %d\n", livros[i].idlivro);
                printf("Livro: %s\n", livros[i].nome_livro);
                printf("Autor: %s\n", livros[i].nome_autor);
                printf("Preco: R$ %.2f\n", livros[i].preco);
                printf("Quantidade: %d\n", livros[i].quantidade);
            }
            break;

        case 2:
            printf("\nDigite o ID do livro: ");
            scanf("%d", &id);
            limparEntradaLivros();

            encontrou = 0;

            for (i = 0; i < totalLivros; i++) {
                if (livros[i].idlivro == id) {
                    printf("\nLivro encontrado!\n");
                    printf("ID: %d\n", livros[i].idlivro);
                    printf("Livro: %s\n", livros[i].nome_livro);
                    printf("Autor: %s\n", livros[i].nome_autor);
                    printf("Preco: R$ %.2f\n", livros[i].preco);
                    printf("Quantidade: %d\n", livros[i].quantidade);

                    encontrou = 1;
                    break;
                }
            }

            if (encontrou == 0) {
                printf("\nLivro nao encontrado!\n");
            }
            break;

        case 3:
            printf("\nDigite o nome ou parte do nome: ");
            lerTextoLivro(busca, 50);

            encontrou = 0;

            for (i = 0; i < totalLivros; i++) {
                if (strstr(livros[i].nome_livro, busca) != NULL) {
                    printf("\nID: %d\n", livros[i].idlivro);
                    printf("Livro: %s\n", livros[i].nome_livro);
                    printf("Autor: %s\n", livros[i].nome_autor);
                    printf("Preco: R$ %.2f\n", livros[i].preco);
                    printf("Quantidade: %d\n", livros[i].quantidade);

                    encontrou = 1;
                }
            }

            if (encontrou == 0) {
                printf("\nNenhum livro encontrado!\n");
            }
            break;

        default:
            printf("\nOpcao invalida!\n");
    }
}

// -------------------- EDITAR LIVRO --------------------

void editarLivro(void) {
    int id;
    int i;
    int encontrou = 0;

    printf("\n========== EDITAR LIVRO ==========\n");
    printf("Digite o ID do livro: ");
    scanf("%d", &id);
    limparEntradaLivros();

    for (i = 0; i < totalLivros; i++) {
        if (livros[i].idlivro == id) {
            printf("\nLivro encontrado!\n");

            printf("Novo nome do livro: ");
            lerTextoLivro(livros[i].nome_livro, 50);

            printf("Novo nome do autor: ");
            lerTextoLivro(livros[i].nome_autor, 50);

            printf("Novo preco: ");
            scanf("%f", &livros[i].preco);
            limparEntradaLivros();

            printf("Nova quantidade: ");
            scanf("%d", &livros[i].quantidade);
            limparEntradaLivros();

            salvarLivrosCSV();

            printf("\nLivro atualizado com sucesso!\n");

            encontrou = 1;
            break;
        }
    }

    if (encontrou == 0) {
        printf("\nLivro nao encontrado!\n");
    }
}

// -------------------- REMOVER LIVRO --------------------

void removerLivro(void) {
    int id;
    int i;
    int j;
    int encontrou = 0;

    printf("\n========== REMOVER LIVRO ==========\n");
    printf("Digite o ID do livro: ");
    scanf("%d", &id);
    limparEntradaLivros();

    for (i = 0; i < totalLivros; i++) {
        if (livros[i].idlivro == id) {
            for (j = i; j < totalLivros - 1; j++) {
                livros[j] = livros[j + 1];
            }

            totalLivros--;

            salvarLivrosCSV();

            printf("\nLivro removido com sucesso!\n");

            encontrou = 1;
            break;
        }
    }

    if (encontrou == 0) {
        printf("\nLivro nao encontrado!\n");
    }
}

#endif
