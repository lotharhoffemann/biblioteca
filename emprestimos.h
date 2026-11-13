/* ======================================================================
 * emprestimos.h - MODULO DE EMPRESTIMOS (Biblioteca)
 * Autor original: LEONARDO MUSIASKI DOS SANTOS - RGM 47837501
 *
 * A estrutura fica neste header; os dados globais sao definidos em main.c.
 * Persistencia: emprestimos.csv (separador ';', compativel com Excel pt-BR)
 *
 * Dependencia: leitores.h, incluido abaixo.
 * ====================================================================== */

#ifndef EMPRESTIMOS_H
#define EMPRESTIMOS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "leitores.h"

#define EMPRESTIMOS_MAX      50
#define EMPRESTIMOS_CSV      "emprestimos.csv"
#define EMPRESTIMOS_CABECALHO "id;idLeitor;titulo;dataEmprestimo;dataDevolucao;emAberto"

/* ----------------------- STRUCT E VARIAVEIS GLOBAIS ----------------- */

typedef struct {
    int id;
    int idLeitor;
    char titulo[100];
    char dataEmprestimo[11];   /* dd/mm/aaaa */
    char dataDevolucao[11];    /* dd/mm/aaaa (vazio enquanto em aberto) */
    int emAberto;              /* 1 = em aberto, 0 = devolvido */
} Emprestimo;

Emprestimo emprestimos[EMPRESTIMOS_MAX];
int totalEmprestimos = 0;

/* ----------------------------- PROTOTIPOS --------------------------- */

/* Menu e operacoes */
void moduloEmprestimos(void);
void registrarEmprestimo(void);
void registrarDevolucao(void);
void listarEmprestimos(void);
void consultarEmAberto(void);

/* Auxiliares */
int  buscarLeitorAtivo(int idLeitor);
int  leitorTemEmprestimoAberto(int idLeitor);
void imprimirEmprestimo(int i);

/* Persistencia CSV */
int  carregarEmprestimosCSV(void);   /* retorna qtd carregada, -1 se nao ha arquivo */
int  salvarEmprestimosCSV(void);     /* retorna 1 se ok, 0 se erro */

/* ----------------------- FUNCOES AUXILIARES DE CSV ------------------ */

/* Troca ';' e quebras de linha por caracteres seguros para nao quebrar o CSV */
static void limparCampoCSV(char *texto) {
    int i;
    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == ';') {
            texto[i] = ',';
        } else if (texto[i] == '\n' || texto[i] == '\r') {
            texto[i] = ' ';
        }
    }
}

/* Divide a linha em campos separados por ';' (aceita campos vazios) */
static int dividirLinhaCSV(char *linha, char *campos[], int maximo) {
    int n = 0;
    char *p = linha;

    campos[n++] = p;
    while (*p != '\0' && n < maximo) {
        if (*p == ';') {
            *p = '\0';
            campos[n++] = p + 1;
        }
        p++;
    }
    return n;
}

/* ----------------------------- PERSISTENCIA ------------------------- */

int salvarEmprestimosCSV(void) {
    int i;
    FILE *arq = fopen(EMPRESTIMOS_CSV, "w");

    if (arq == NULL) {
        printf("Aviso: nao foi possivel gravar %s\n", EMPRESTIMOS_CSV);
        return 0;
    }

    fprintf(arq, "%s\n", EMPRESTIMOS_CABECALHO);

    for (i = 0; i < totalEmprestimos; i++) {
        fprintf(arq, "%d;%d;%s;%s;%s;%d\n",
                emprestimos[i].id,
                emprestimos[i].idLeitor,
                emprestimos[i].titulo,
                emprestimos[i].dataEmprestimo,
                emprestimos[i].dataDevolucao,
                emprestimos[i].emAberto);
    }

    fclose(arq);
    return 1;
}

int carregarEmprestimosCSV(void) {
    char linha[400];
    char *campos[6];
    int primeiraLinha = 1;
    FILE *arq = fopen(EMPRESTIMOS_CSV, "r");

    totalEmprestimos = 0;

    if (arq == NULL) {
        return -1;   /* primeira execucao: arquivo ainda nao existe */
    }

    while (fgets(linha, sizeof(linha), arq) != NULL && totalEmprestimos < EMPRESTIMOS_MAX) {
        Emprestimo *e;

        linha[strcspn(linha, "\r\n")] = '\0';

        if (primeiraLinha) {          /* pula o cabecalho */
            primeiraLinha = 0;
            continue;
        }
        if (linha[0] == '\0') {
            continue;
        }
        if (dividirLinhaCSV(linha, campos, 6) != 6) {
            continue;                 /* linha malformada: ignora */
        }

        e = &emprestimos[totalEmprestimos];

        e->id       = atoi(campos[0]);
        e->idLeitor = atoi(campos[1]);
        strncpy(e->titulo,         campos[2], sizeof(e->titulo) - 1);
        strncpy(e->dataEmprestimo, campos[3], sizeof(e->dataEmprestimo) - 1);
        strncpy(e->dataDevolucao,  campos[4], sizeof(e->dataDevolucao) - 1);
        e->titulo[sizeof(e->titulo) - 1] = '\0';
        e->dataEmprestimo[sizeof(e->dataEmprestimo) - 1] = '\0';
        e->dataDevolucao[sizeof(e->dataDevolucao) - 1] = '\0';
        e->emAberto = atoi(campos[5]) == 1 ? 1 : 0;

        if (e->id <= 0) {
            continue;                 /* id invalido: ignora */
        }

        totalEmprestimos++;
    }

    fclose(arq);
    return totalEmprestimos;
}

/* ==================== MODULO DE EMPRESTIMOS ==================== */

void moduloEmprestimos(void) {
    int opcaoE;

    do {
        printf("\n========== MODULO DE EMPRESTIMOS ==========\n");
        printf("1 - Registrar emprestimo\n");
        printf("2 - Registrar devolucao\n");
        printf("3 - Listar emprestimos\n");
        printf("4 - Consultar emprestimos em aberto\n");
        printf("0 - Voltar\n");
        printf("\nEscolha uma opcao: ");

        if (scanf("%d", &opcaoE) != 1) {
            printf("Entrada invalida!\n");
            return;
        }

        switch (opcaoE) {
            case 1:
                registrarEmprestimo();
                break;

            case 2:
                registrarDevolucao();
                break;

            case 3:
                listarEmprestimos();
                break;

            case 4:
                consultarEmAberto();
                break;

            case 0:
                printf("Voltando ao menu principal...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }

    } while (opcaoE != 0);
}

int buscarLeitorAtivo(int idLeitor) {
    int i;

    for (i = 0; i < totalLeitores; i++) {
        if (leitores[i].id == idLeitor && leitores[i].ativo == 1) {
            return i;
        }
    }

    return -1;
}

int leitorTemEmprestimoAberto(int idLeitor) {
    int i;

    for (i = 0; i < totalEmprestimos; i++) {
        if (emprestimos[i].idLeitor == idLeitor && emprestimos[i].emAberto == 1) {
            return 1;
        }
    }

    return 0;
}

void imprimirEmprestimo(int i) {
    int posLeitor = buscarLeitorAtivo(emprestimos[i].idLeitor);

    printf("\nID do emprestimo: %d\n", emprestimos[i].id);
    printf("ID do leitor: %d", emprestimos[i].idLeitor);

    if (posLeitor != -1) {
        printf(" (%s)", leitores[posLeitor].nome);
    }

    printf("\nLivro: %s\n", emprestimos[i].titulo);
    printf("Data do emprestimo: %s\n", emprestimos[i].dataEmprestimo);

    if (emprestimos[i].emAberto == 1) {
        printf("Situacao: EM ABERTO\n");
    } else {
        printf("Situacao: DEVOLVIDO em %s\n", emprestimos[i].dataDevolucao);
    }

    printf("------------------------------------------\n");
}

void registrarEmprestimo(void) {
    int idLeitor;

    if (totalEmprestimos >= EMPRESTIMOS_MAX) {
        printf("Limite de emprestimos atingido!\n");
        return;
    }

    printf("\n========== REGISTRO DE EMPRESTIMO ==========\n");

    printf("Digite o ID do leitor: ");

    if (scanf("%d", &idLeitor) != 1) {
        printf("ID invalido!\n");
        return;
    }

    if (buscarLeitorAtivo(idLeitor) == -1) {
        printf("\nLeitor nao encontrado ou inativo.\n");
        return;
    }

    emprestimos[totalEmprestimos].id = totalEmprestimos + 1;
    emprestimos[totalEmprestimos].idLeitor = idLeitor;

    printf("Digite o titulo do livro: ");
    scanf(" %99[^\n]", emprestimos[totalEmprestimos].titulo);
    limparCampoCSV(emprestimos[totalEmprestimos].titulo);

    printf("Digite a data do emprestimo (dd/mm/aaaa): ");
    scanf(" %10[^\n]", emprestimos[totalEmprestimos].dataEmprestimo);
    limparCampoCSV(emprestimos[totalEmprestimos].dataEmprestimo);

    emprestimos[totalEmprestimos].dataDevolucao[0] = '\0';
    emprestimos[totalEmprestimos].emAberto = 1;

    printf("\nEmprestimo registrado com sucesso!\n");
    printf("ID do emprestimo: %d\n", emprestimos[totalEmprestimos].id);

    totalEmprestimos++;

    salvarEmprestimosCSV();
}

void registrarDevolucao(void) {
    int buscaId, i, encontrado = 0;

    if (totalEmprestimos == 0) {
        printf("\nNenhum emprestimo registrado!\n");
        return;
    }

    printf("Digite o ID do emprestimo que deseja devolver: ");

    if (scanf("%d", &buscaId) != 1) {
        printf("ID invalido!\n");
        return;
    }

    for (i = 0; i < totalEmprestimos; i++) {
        if (emprestimos[i].id == buscaId && emprestimos[i].emAberto == 1) {

            encontrado = 1;

            printf("\nEmprestimo encontrado: %s\n", emprestimos[i].titulo);

            printf("Digite a data da devolucao (dd/mm/aaaa): ");
            scanf(" %10[^\n]", emprestimos[i].dataDevolucao);
            limparCampoCSV(emprestimos[i].dataDevolucao);

            emprestimos[i].emAberto = 0;

            printf("\nDevolucao registrada com sucesso!\n");

            salvarEmprestimosCSV();
            break;
        }
    }

    if (encontrado == 0) {
        printf("\nEmprestimo nao encontrado ou ja devolvido.\n");
    }
}

void listarEmprestimos(void) {
    int i;

    printf("\n========== EMPRESTIMOS REGISTRADOS ==========\n");

    if (totalEmprestimos == 0) {
        printf("\nNenhum emprestimo registrado.\n");
        return;
    }

    for (i = 0; i < totalEmprestimos; i++) {
        imprimirEmprestimo(i);
    }
}

void consultarEmAberto(void) {
    int i, encontrado = 0;

    printf("\n========== EMPRESTIMOS EM ABERTO ==========\n");

    for (i = 0; i < totalEmprestimos; i++) {
        if (emprestimos[i].emAberto == 1) {
            imprimirEmprestimo(i);
            encontrado = 1;
        }
    }

    if (encontrado == 0) {
        printf("\nNenhum emprestimo em aberto.\n");
    }
}

#endif /* EMPRESTIMOS_H */
