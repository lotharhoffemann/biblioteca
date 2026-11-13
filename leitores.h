#ifndef LEITORES_H
#define LEITORES_H

#include <stdio.h>
#include <string.h>

// ==================== STRUCT E VARIAVEIS ==================== //

// Nome: LOTHAR MATHEUS HOFFEMANN JUSSIM
// RGM: 47695145

typedef struct {
    int id;
    char nome[100];
    char telefone[20];
    char email[100];
    int ativo;
} Leitor;

Leitor leitores[50];
int totalLeitores = 0;


// ==================== PROTOTIPOS ==================== //

void salvarLeitoresCSV(void);
void carregarLeitoresCSV(void);

int buscarIndiceLeitor(int id);

void cadastrarLeitor(void);
void listarLeitores(void);
void buscarLeitor(void);
void editarLeitor(void);
void removerLeitor(void);

void moduloClientes(void);


// ==================== SALVAR LEITORES NO CSV ==================== //

void salvarLeitoresCSV(void) {

    FILE *arquivo;
    int i;

    arquivo = fopen("leitores.csv", "w");

    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo leitores.csv!\n");
        return;
    }

    for (i = 0; i < totalLeitores; i++) {

        fprintf(arquivo, "%d;%s;%s;%s;%d\n",
                leitores[i].id,
                leitores[i].nome,
                leitores[i].telefone,
                leitores[i].email,
                leitores[i].ativo);
    }

    fclose(arquivo);

    printf("\nDados dos leitores salvos com sucesso!\n");
}


// ==================== CARREGAR LEITORES DO CSV ==================== //

void carregarLeitoresCSV(void) {

    FILE *arquivo;

    arquivo = fopen("leitores.csv", "r");

    if (arquivo == NULL) {
        totalLeitores = 0;
        return;
    }

    totalLeitores = 0;

    while (totalLeitores < 50 &&
           fscanf(arquivo, "%d;%99[^;];%19[^;];%99[^;];%d",
                  &leitores[totalLeitores].id,
                  leitores[totalLeitores].nome,
                  leitores[totalLeitores].telefone,
                  leitores[totalLeitores].email,
                  &leitores[totalLeitores].ativo) == 5) {

        totalLeitores++;
    }

    fclose(arquivo);

    printf("\nLeitores carregados: %d\n", totalLeitores);
}


// ==================== BUSCAR LEITOR PELO ID ==================== //

int buscarIndiceLeitor(int id) {

    int i;

    for (i = 0; i < totalLeitores; i++) {

        if (leitores[i].id == id) {
            return i;
        }
    }

    return -1;
}


// ==================== CADASTRAR LEITOR ==================== //

void cadastrarLeitor(void) {

    if (totalLeitores >= 50) {
        printf("\nLimite de leitores atingido!\n");
        return;
    }

    leitores[totalLeitores].id = totalLeitores + 1;

    printf("\n========== CADASTRO DE LEITOR ==========\n");

    printf("Digite o nome: ");
    scanf(" %99[^\n]", leitores[totalLeitores].nome);

    printf("Digite o telefone: ");
    scanf(" %19[^\n]", leitores[totalLeitores].telefone);

    printf("Digite o e-mail: ");
    scanf(" %99[^\n]", leitores[totalLeitores].email);

    leitores[totalLeitores].ativo = 1;

    printf("\nLeitor cadastrado com sucesso!\n");
    printf("ID do leitor: %d\n", leitores[totalLeitores].id);

    totalLeitores++;

    salvarLeitoresCSV();
}


// ==================== LISTAR LEITORES ==================== //

void listarLeitores(void) {

    int i;
    int encontrado = 0;

    printf("\n========== LEITORES CADASTRADOS ==========\n");

    for (i = 0; i < totalLeitores; i++) {

        if (leitores[i].ativo == 1) {

            printf("\nID: %d\n", leitores[i].id);
            printf("Nome: %s\n", leitores[i].nome);
            printf("Telefone: %s\n", leitores[i].telefone);
            printf("E-mail: %s\n", leitores[i].email);

            printf("------------------------------------------\n");

            encontrado = 1;
        }
    }

    if (encontrado == 0) {
        printf("\nNenhum leitor cadastrado.\n");
    }
}


// ==================== BUSCAR LEITOR PELO NOME ==================== //

void buscarLeitor(void) {

    char termo[100];
    int i;
    int encontrado = 0;

    printf("\n========== BUSCAR LEITOR ==========\n");

    printf("Digite o nome ou parte do nome: ");
    scanf(" %99[^\n]", termo);

    for (i = 0; i < totalLeitores; i++) {

        if (leitores[i].ativo == 1 &&
            strstr(leitores[i].nome, termo) != NULL) {

            printf("\nLeitor encontrado!\n");
            printf("ID: %d\n", leitores[i].id);
            printf("Nome: %s\n", leitores[i].nome);
            printf("Telefone: %s\n", leitores[i].telefone);
            printf("E-mail: %s\n", leitores[i].email);

            encontrado = 1;
        }
    }

    if (encontrado == 0) {
        printf("\nNenhum leitor encontrado.\n");
    }
}


// ==================== EDITAR LEITOR ==================== //

void editarLeitor(void) {

    int buscaId;
    int pos;

    if (totalLeitores == 0) {
        printf("\nNenhum leitor cadastrado!\n");
        return;
    }

    printf("\nDigite o ID do leitor que deseja editar: ");

    if (scanf("%d", &buscaId) != 1) {
        printf("\nID invalido!\n");
        return;
    }

    pos = buscarIndiceLeitor(buscaId);

    if (pos == -1 || leitores[pos].ativo == 0) {

        printf("\nLeitor nao encontrado ou inativo.\n");
        return;
    }

    printf("\nLeitor encontrado: %s\n", leitores[pos].nome);

    printf("Digite o novo nome: ");
    scanf(" %99[^\n]", leitores[pos].nome);

    printf("Digite o novo telefone: ");
    scanf(" %19[^\n]", leitores[pos].telefone);

    printf("Digite o novo e-mail: ");
    scanf(" %99[^\n]", leitores[pos].email);

    salvarLeitoresCSV();

    printf("\nDados atualizados com sucesso!\n");
}


// ==================== REMOVER LEITOR ==================== //

void removerLeitor(void) {

    int buscaId;
    int pos;

    if (totalLeitores == 0) {
        printf("\nNenhum leitor cadastrado!\n");
        return;
    }

    printf("\nDigite o ID do leitor que deseja remover: ");

    if (scanf("%d", &buscaId) != 1) {
        printf("\nID invalido!\n");
        return;
    }

    pos = buscarIndiceLeitor(buscaId);

    if (pos == -1 || leitores[pos].ativo == 0) {

        printf("\nLeitor nao encontrado ou ja removido.\n");
        return;
    }

    leitores[pos].ativo = 0;

    salvarLeitoresCSV();

    printf("\nLeitor removido com sucesso!\n");
}


// ==================== SUBMENU DE LEITORES ==================== //

void moduloClientes(void) {

    int opcaoI;

    do {

        printf("\n========== MODULO DE LEITORES ==========\n");
        printf("1 - Cadastrar leitor\n");
        printf("2 - Listar leitores\n");
        printf("3 - Buscar leitor por nome\n");
        printf("4 - Editar leitor\n");
        printf("5 - Remover leitor\n");
        printf("0 - Voltar ao menu principal\n");

        printf("\nEscolha uma opcao: ");

        if (scanf("%d", &opcaoI) != 1) {
            printf("\nEntrada invalida!\n");
            return;
        }

        switch (opcaoI) {

            case 1:
                cadastrarLeitor();
                break;

            case 2:
                listarLeitores();
                break;

            case 3:
                buscarLeitor();
                break;

            case 4:
                editarLeitor();
                break;

            case 5:
                removerLeitor();
                break;

            case 0:
                printf("\nVoltando ao menu principal...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
                break;
        }

    } while (opcaoI != 0);
}

#endif

