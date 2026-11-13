/*
 * Arquivo: relatorios.h
 * Integrante: Eduardo Henrique de Oliveira Souza
 * RGM: 47013109
 *
 * Modulo de Consultas e Relatorios da Biblioteca.
 * Os dados sao gravados em relatorios.csv usando ';' como separador.
 */

#ifndef RELATORIOS_H
#define RELATORIOS_H

#include <stdio.h>
#include <string.h>

#include "leitores.h"
#include "livros.h"
#include "emprestimos.h"

#define MAX_RELATORIOS 50

/* Estrutura propria do modulo de relatorios. */
typedef struct Relatorios {
    int idRelatorio;
    int totalLeitores;
    int totalLivros;
    int emprestimosEmAberto;
    char descricao[100];
} Relatorio;

/* Vetor e contadores globais deste modulo. */
Relatorio relatorios[MAX_RELATORIOS];
int totalRelatorios = 0;
int proximoIdRelatorio = 1;


/* Funcao do modulo de emprestimos, criada pelo outro integrante. */
void consultarEmAberto(void);
void limparTela(void);

/* Prototipos deste modulo. */
void moduloRelatorios(void);
void carregarRelatoriosCSV(void);
void salvarRelatoriosCSV(void);
int contarEmprestimosEmAberto(void);
int contarLeitoresAtivos(void);
void gerarResumoGeral(void);
void listarRelatorios(void);
void buscarRelatorioPorDescricao(void);
void editarRelatorio(void);
void removerRelatorio(void);
void exibirMatrizEmprestimos(void);
int buscarIndiceRelatorio(int idProcurado);

/* ---------------------------------------------------------
   Funcoes auxiliares de entrada
   --------------------------------------------------------- */

void limparEntradaRelatorio(void) {
    int caractere;

    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

void lerTextoRelatorio(char texto[], int tamanho) {
    int i;

    if (fgets(texto, tamanho, stdin) == NULL) {
        texto[0] = '\0';
        return;
    }

    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == '\n') {
            texto[i] = '\0';
            break;
        }
    }
}

/* ---------------------------------------------------------
   1. LEITURA DO CSV
   --------------------------------------------------------- */

void carregarRelatoriosCSV(void) {
    FILE *arquivo;
    int lidos;

    arquivo = fopen("relatorios.csv", "r");

    if (arquivo == NULL) {
        totalRelatorios = 0;
        proximoIdRelatorio = 1;
        return;
    }

    totalRelatorios = 0;
    proximoIdRelatorio = 1;

    while (totalRelatorios < MAX_RELATORIOS) {
        Relatorio registro;

        lidos = fscanf(arquivo, "%d;%d;%d;%d;%99[^\n]\n",
                       &registro.idRelatorio,
                       &registro.totalLeitores,
                       &registro.totalLivros,
                       &registro.emprestimosEmAberto,
                       registro.descricao);

        if (lidos != 5) {
            break;
        }

        relatorios[totalRelatorios] = registro;

        if (registro.idRelatorio >= proximoIdRelatorio) {
            proximoIdRelatorio = registro.idRelatorio + 1;
        }

        totalRelatorios++;
    }

    fclose(arquivo);
}

/* ---------------------------------------------------------
   2. ESCRITA DO CSV
   --------------------------------------------------------- */

void salvarRelatoriosCSV(void) {
    FILE *arquivo;
    int i;

    arquivo = fopen("relatorios.csv", "w");

    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel salvar relatorios.csv.\n");
        return;
    }

    for (i = 0; i < totalRelatorios; i++) {
        fprintf(arquivo, "%d;%d;%d;%d;%s\n",
                relatorios[i].idRelatorio,
                relatorios[i].totalLeitores,
                relatorios[i].totalLivros,
                relatorios[i].emprestimosEmAberto,
                relatorios[i].descricao);
    }

    fclose(arquivo);
}

/* ---------------------------------------------------------
   3. FUNCOES DE CONSULTA E CALCULO
   --------------------------------------------------------- */

int contarLeitoresAtivos(void) {
    int i;
    int quantidade = 0;

    for (i = 0; i < totalLeitores; i++) {
        if (leitores[i].ativo == 1) {
            quantidade++;
        }
    }

    return quantidade;
}

int contarEmprestimosEmAberto(void) {
    int i;
    int quantidade = 0;

    for (i = 0; i < totalEmprestimos; i++) {
        if (emprestimos[i].emAberto == 1) {
            quantidade++;
        }
    }

    return quantidade;
}

int buscarIndiceRelatorio(int idProcurado) {
    int i;

    for (i = 0; i < totalRelatorios; i++) {
        if (relatorios[i].idRelatorio == idProcurado) {
            return i;
        }
    }

    return -1;
}

/* ---------------------------------------------------------
   4. GERACAO DE RESUMO GERAL
   O resumo utiliza os vetores reais dos outros modulos.
   --------------------------------------------------------- */

void gerarResumoGeral(void) {
    int posicao;

    if (totalRelatorios >= MAX_RELATORIOS) {
        printf("\n[ERRO] Limite de relatorios atingido.\n");
        return;
    }

    posicao = totalRelatorios;

    relatorios[posicao].idRelatorio = proximoIdRelatorio;
    relatorios[posicao].totalLeitores = contarLeitoresAtivos();
    relatorios[posicao].totalLivros = totalLivros;
    relatorios[posicao].emprestimosEmAberto = contarEmprestimosEmAberto();

    printf("\nDigite uma descricao para o relatorio: ");
    lerTextoRelatorio(relatorios[posicao].descricao,
                      sizeof(relatorios[posicao].descricao));

    if (relatorios[posicao].descricao[0] == '\0') {
        strcpy(relatorios[posicao].descricao, "Resumo geral da biblioteca");
    }

    totalRelatorios++;
    proximoIdRelatorio++;

    salvarRelatoriosCSV();

    printf("\n========== RESUMO GERAL DA BIBLIOTECA ==========\n");
    printf("ID do relatorio: %d\n", relatorios[posicao].idRelatorio);
    printf("Leitores ativos: %d\n", relatorios[posicao].totalLeitores);
    printf("Livros cadastrados: %d\n", relatorios[posicao].totalLivros);
    printf("Emprestimos em aberto: %d\n",
           relatorios[posicao].emprestimosEmAberto);
    printf("Descricao: %s\n", relatorios[posicao].descricao);
    printf("\nRelatorio salvo em relatorios.csv.\n");
}

/* ---------------------------------------------------------
   5. LISTAGEM DOS RELATORIOS
   --------------------------------------------------------- */

void listarRelatorios(void) {
    int i;

    printf("\n========== RELATORIOS REGISTRADOS ==========\n");

    if (totalRelatorios == 0) {
        printf("Nenhum relatorio registrado.\n");
        return;
    }

    for (i = 0; i < totalRelatorios; i++) {
        printf("\nID: %d\n", relatorios[i].idRelatorio);
        printf("Descricao: %s\n", relatorios[i].descricao);
        printf("Leitores ativos: %d\n", relatorios[i].totalLeitores);
        printf("Livros cadastrados: %d\n", relatorios[i].totalLivros);
        printf("Emprestimos em aberto: %d\n", relatorios[i].emprestimosEmAberto);
        printf("--------------------------------------------\n");
    }
}

/* ---------------------------------------------------------
   6. BUSCA TEXTUAL COM STRSTR
   --------------------------------------------------------- */

void buscarRelatorioPorDescricao(void) {
    char termo[100];
    int i;
    int encontrado = 0;

    if (totalRelatorios == 0) {
        printf("\nNao existem relatorios cadastrados.\n");
        return;
    }

    printf("\nDigite uma palavra ou trecho da descricao: ");
    lerTextoRelatorio(termo, sizeof(termo));

    if (termo[0] == '\0') {
        printf("\nTermo de busca vazio.\n");
        return;
    }

    for (i = 0; i < totalRelatorios; i++) {
        if (strstr(relatorios[i].descricao, termo) != NULL) {
            printf("\nID: %d | Descricao: %s\n",
                   relatorios[i].idRelatorio,
                   relatorios[i].descricao);
            printf("Leitores: %d | Livros: %d | Emprestimos em aberto: %d\n",
                   relatorios[i].totalLeitores,
                   relatorios[i].totalLivros,
                   relatorios[i].emprestimosEmAberto);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("\nNenhum relatorio corresponde ao termo informado.\n");
    }
}

/* ---------------------------------------------------------
   7. EDICAO
   --------------------------------------------------------- */

void editarRelatorio(void) {
    int id;
    int posicao;

    if (totalRelatorios == 0) {
        printf("\nNao existem relatorios para editar.\n");
        return;
    }

    printf("\nDigite o ID do relatorio que deseja editar: ");
    if (scanf("%d", &id) != 1) {
        printf("\nID invalido.\n");
        limparEntradaRelatorio();
        return;
    }
    limparEntradaRelatorio();

    posicao = buscarIndiceRelatorio(id);

    if (posicao == -1) {
        printf("\nRelatorio nao encontrado.\n");
        return;
    }

    printf("Nova descricao: ");
    lerTextoRelatorio(relatorios[posicao].descricao,
                      sizeof(relatorios[posicao].descricao));

    if (relatorios[posicao].descricao[0] == '\0') {
        printf("\nA descricao nao pode ficar vazia.\n");
        return;
    }

    relatorios[posicao].totalLeitores = contarLeitoresAtivos();
    relatorios[posicao].totalLivros = totalLivros;
    relatorios[posicao].emprestimosEmAberto = contarEmprestimosEmAberto();

    salvarRelatoriosCSV();
    printf("\nRelatorio editado e arquivo CSV atualizado.\n");
}

/* ---------------------------------------------------------
   8. REMOCAO
   --------------------------------------------------------- */

void removerRelatorio(void) {
    int id;
    int posicao;
    int i;

    if (totalRelatorios == 0) {
        printf("\nNao existem relatorios para remover.\n");
        return;
    }

    printf("\nDigite o ID do relatorio que deseja remover: ");
    if (scanf("%d", &id) != 1) {
        printf("\nID invalido.\n");
        limparEntradaRelatorio();
        return;
    }
    limparEntradaRelatorio();

    posicao = buscarIndiceRelatorio(id);

    if (posicao == -1) {
        printf("\nRelatorio nao encontrado.\n");
        return;
    }

    for (i = posicao; i < totalRelatorios - 1; i++) {
        relatorios[i] = relatorios[i + 1];
    }

    totalRelatorios--;
    salvarRelatoriosCSV();

    printf("\nRelatorio removido da memoria e do arquivo CSV.\n");
}

/* ---------------------------------------------------------
   9. MATRIZ 2D DE EMPRESTIMOS
   Linhas: leitor ativo / leitor inativo ou inexistente.
   Colunas: emprestimo em aberto / emprestimo devolvido.
   --------------------------------------------------------- */

void exibirMatrizEmprestimos(void) {
    int matriz[2][2] = {{0, 0}, {0, 0}};
    int i;
    int j;
    int leitorAtivo;

    for (i = 0; i < totalEmprestimos; i++) {
        leitorAtivo = 0;

        for (j = 0; j < totalLeitores; j++) {
            if (leitores[j].id == emprestimos[i].idLeitor &&
                leitores[j].ativo == 1) {
                leitorAtivo = 1;
                break;
            }
        }

        if (emprestimos[i].emAberto == 1) {
            matriz[leitorAtivo][0]++;
        } else {
            matriz[leitorAtivo][1]++;
        }
    }

    printf("\n======= MATRIZ DE EMPRESTIMOS =======\n");
    printf("%-28s | %12s | %12s\n",
           "Situacao do leitor", "Em aberto", "Devolvidos");
    printf("----------------------------------------------------------\n");
    printf("%-28s | %12d | %12d\n",
           "Leitor ativo", matriz[1][0], matriz[1][1]);
    printf("%-28s | %12d | %12d\n",
           "Leitor inativo/nao localizado", matriz[0][0], matriz[0][1]);
    printf("----------------------------------------------------------\n");
    printf("Total de emprestimos analisados: %d\n",
           matriz[0][0] + matriz[0][1] + matriz[1][0] + matriz[1][1]);
}

/* ---------------------------------------------------------
   10. SUBMENU DO MODULO
   Cada opcao chama uma subfuncao propria.
   --------------------------------------------------------- */

void moduloRelatorios(void) {
    int opcaoRelatorio;

    do {
        limparTela();
        printf("\n========== CONSULTAS E RELATORIOS ==========\n");
        printf("1 - Gerar e salvar resumo geral da biblioteca\n");
        printf("2 - Consultar emprestimos em aberto\n");
        printf("3 - Listar relatorios registrados\n");
        printf("4 - Buscar relatorio por descricao\n");
        printf("5 - Editar relatorio\n");
        printf("6 - Remover relatorio\n");
        printf("7 - Exibir matriz de emprestimos\n");
        printf("0 - Voltar ao menu principal\n");
        printf("--------------------------------------------\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcaoRelatorio) != 1) {
            printf("\nEntrada invalida. Digite um numero.\n");
            limparEntradaRelatorio();
            opcaoRelatorio = -1;
            continue;
        }
        limparEntradaRelatorio();

        switch (opcaoRelatorio) {
            case 1:
                gerarResumoGeral();
                break;

            case 2:
                consultarEmAberto();
                break;

            case 3:
                listarRelatorios();
                break;

            case 4:
                buscarRelatorioPorDescricao();
                break;

            case 5:
                editarRelatorio();
                break;

            case 6:
                removerRelatorio();
                break;

            case 7:
                exibirMatrizEmprestimos();
                break;

            case 0:
                printf("\nVoltando ao menu principal...\n");
                break;

            default:
                printf("\nOpcao invalida. Escolha de 0 a 7.\n");
                break;
        }

        if (opcaoRelatorio != 0) {
            printf("\nPressione ENTER para voltar ao menu de relatorios...");
            getchar();
        }

    } while (opcaoRelatorio != 0);
}

#endif
