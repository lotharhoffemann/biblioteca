#include <stdio.h>
#include <string.h>
#include <locale.h>


//  --------------------- STRUCTS E VARIAVEIS GLOBAIS -------------------- //


//Nome: LOTHAR MATHEUS HOFFEMANN JUSSIM
//RGM: 47695145
typedef struct {
    int id;
    char nome[100];
    char telefone[20];
    char email[100];
    int ativo;
} Leitor;

Leitor leitores[50];
int totalLeitores = 0;
//Nome: SAMUEL GODOY MEDEIROS DA SILVA
//RGM: 49707400
struct livro {
    int idlivro;
    char nome_livro[50];
    char nome_autor[50];
    float preco;
    int quantidade;
};

struct livro livros[50];
int totalLivros = 0;
int proximoId = 1;
// Nome: LEONARDO MUSIASKI DOS SANTOS
// RGM: 47837501
typedef struct {
    int id;
    int idLeitor;
    char titulo[100];
    char dataEmprestimo[11];   /* dd/mm/aaaa */
    char dataDevolucao[11];    /* dd/mm/aaaa (vazio enquanto em aberto) */
    int emAberto;              /* 1 = em aberto, 0 = devolvido */
} Emprestimo;

Emprestimo emprestimos[50];
int totalEmprestimos = 0;

// Nome: EDUARDO HENRIQUE DE OLIVEIRA SOUZA
// RGM: 47013109
struct Relatorios{
    int idRelatorio;
    int totalLeitores;
    int totalLivros;
    int emprestimosEmAberto;
    char descricao[100];
};


struct Relatorios relatorios[50];
int totalRelatorios = 0;
int proximoIdRelatorio = 1;

//  --------------------- PROTOTIPOS -------------------- //

//Nome: LOTHAR MATHEUS HOFFEMANN JUSSIM
void menuPrincipal(void);
void cabecalho(void);

void moduloClientes(void);
void cadastrarLeitor(void);
void listarLeitores(void);
void editarLeitor(void);
void removerLeitor(void);

//Nome: SAMUEL GODOY MEDEIROS DA SILVA
void modulo_livros(void);
void cadastrarLivro(void);
void listarBuscarLivros(void);
void editarLivro(void);
void removerLivro(void);
void limparEntrada(void);
void lerTexto(char texto[], int tamanho);

//Nome: LEONARDO MUSIASKI DOS SANTOS
void moduloEmprestimos(void);
void registrarEmprestimo(void);
void registrarDevolucao(void);
void listarEmprestimos(void);
void consultarEmAberto(void);

int buscarLeitorAtivo(int idLeitor);
int leitorTemEmprestimoAberto(int idLeitor);
void imprimirEmprestimo(int i);

//Nome: EDUARDO HENRIQUE DE OLIVEIRA SOUZA
void moduloRelatorios(void);
void gerarResumoGeral(void);
void listarRelatorios(void);
void removerRelatorio(void);
int contarEmprestimosEmAberto(void);


int main(void) {
	setlocale(LC_ALL, "Portuguese");
	
    int opcaoA;
	cabecalho();
    
    do {
    	printf("\n========== MENU PRINCIPAL ==========\n");
    	printf("1 - Cadastro de leitores\n");
        printf("2 - Catalogo de livros\n");
        printf("3 - Emprestimos e devolucoes\n");
        printf("4 - Consultas e relatorios\n");
        printf("0 - Sair\n");
        printf("------------------------------------\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcaoA) != 1) {
        	printf("Opcao invalida!\n");
        	return;
		}

		switch (opcaoA) {
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
				
		}
	} while (opcaoA != 0);
    
    return 0;
}

// ==================== MODULO DE LEITORES ==================== //

void cabecalho(void) {
    printf("\n======================================================\n");
    printf("                    BIBLIOTECA\n");
    printf("======================================================\n");
}

void moduloClientes(void) {
    int opcaoI;

    do {
        printf("\n========== MODULO DE LEITORES ==========\n");
        printf("1 - Cadastrar leitor\n");
        printf("2 - Listar/buscar leitores\n");
        printf("3 - Editar leitor\n");
        printf("4 - Remover leitor\n");
        printf("0 - Sair\n");
        printf("\nEscolha uma opcao: ");

        if (scanf("%d", &opcaoI) != 1) {
            printf("Entrada invalida!\n");
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
                editarLeitor();
                break;

            case 4:
                removerLeitor();
                break;

            case 0:
                printf("Voltando ao menu principal...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }

    } while (opcaoI != 0);
}

void cadastrarLeitor(void) {
    if (totalLeitores >= 50) {
        printf("Limite de leitores atingido!\n");
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
}

void listarLeitores(void){

	int encontrado = 0, i;
	
	
	printf("\n========== LEITORES CADASTRADOS ==========\n");
	
	for (i=0; i < totalLeitores; i++) {
		if (leitores[i].ativo == 1){
			printf("\nID: %d\n", leitores[i].id);
            printf("Nome: %s\n", leitores[i].nome);
            printf("Telefone: %s\n", leitores[i].telefone);
            printf("E-mail: %s\n", leitores[i].email);
            printf("------------------------------------------\n");
		}
	}
	if (totalLeitores == 0) {
		printf("\nNenhum leitor cadastrado.\n");
		return;
	}
}

void editarLeitor(void){
	int buscaId, i, encontrado = 0;
	
	if (totalLeitores == 0) {
		printf("\nNenhum leitor cadastrado!\n");
		return;
	}
	
	printf("Digite o ID do leitor que deseja editar: ");
	
	if(scanf("%d", &buscaId) != 1) {
		printf("ID invalido!\n");
		return;
	}
	
	for (i = 0; i < totalLeitores; i++) {
		if (leitores[i].id == buscaId && leitores[i].ativo == 1){
			
			encontrado = 1;
			
			printf("\nLeitor encontrado: %s\n",
                   leitores[i].nome);

            printf("Digite o novo nome: ");
            scanf(" %99[^\n]", leitores[i].nome);

            printf("Digite o novo telefone: ");
            scanf(" %19[^\n]", leitores[i].telefone);

            printf("Digite o novo e-mail: ");
            scanf(" %99[^\n]", leitores[i].email);

            printf("\nDados atualizados com sucesso!\n");
            break;
		}
	}
	
	if (encontrado == 0){
			printf("\nLeitor não encontrado ou inativo.\n");
	}
}

void removerLeitor(void){
	int buscaId, i, encontrado = 0;
	
	if (totalLeitores == 0){
		printf("\nNenhum leitor cadastrado!\n");
		return;
	}
	
	printf("Digite o ID do Leitor que deseja remover: ");
	
	if (scanf("%d", &buscaId)!= 1) {
		printf("ID invalido!\n");
		return;
	}
	
	for (i = 0; i <totalLeitores; i++) {
		if (leitores[i].id == buscaId && leitores[i].ativo == 1) {
			
			leitores[i].ativo = 0;
			encontrado = 1;
			
			printf("\nLeitor removido com sucesso!\n");
			break;
		}
	}
	
	if (encontrado == 0){
		printf("\nLeitor nao encontrado ou ja removido.\n");
	}
}

// ==================== MODULO DE LIVROS ==================== //


void limparEntrada(void) {
    int caractere;

    while ((caractere = getchar()) != '\n' &&
           caractere != EOF) {
    }
}

void lerTexto(char texto[], int tamanho) {
    int i;

    fgets(texto, tamanho, stdin);

    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == '\n') {
            texto[i] = '\0';
            break;
        }
    }
}

void modulo_livros(void) {
    int opcao_livro;

    do {
        printf("\n===== CATALOGO DE LIVROS =====\n");
        printf("1 - Cadastrar livro\n");
        printf("2 - Listar / buscar livro\n");
        printf("3 - Editar livro\n");
        printf("4 - Remover livro\n");
        printf("0 - Voltar ao menu principal\n");
        printf("\nEscolha uma opcao: ");

        scanf("%d", &opcao_livro);
        limparEntrada();

        switch (opcao_livro) {
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
                printf("\nVoltando ao menu principal...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao_livro != 0);
}

void cadastrarLivro(void) {
    if (totalLivros >= 50) {
        printf("\nCatalogo cheio!\n");
    } else {
        livros[totalLivros].idlivro = proximoId;

        printf("\nDigite o titulo do livro: ");
        lerTexto(livros[totalLivros].nome_livro, 50);

        printf("Digite o nome do autor: ");
        lerTexto(livros[totalLivros].nome_autor, 50);

        printf("Digite o preco: ");
        scanf("%f", &livros[totalLivros].preco);
        limparEntrada();

        printf("Digite a quantidade: ");
        scanf("%d", &livros[totalLivros].quantidade);
        limparEntrada();

        totalLivros++;
        proximoId++;

        printf("\nLivro cadastrado com sucesso!\n");
    }
}

void listarBuscarLivros(void) {
    int opcao;
    int id;
    int encontrado = 0;
    int i;

    if (totalLivros == 0) {
        printf("\nNenhum livro cadastrado.\n");
    } else {
        printf("\n1 - Listar todos os livros\n");
        printf("2 - Buscar livro pelo ID\n");
        printf("Escolha: ");

        scanf("%d", &opcao);
        limparEntrada();

        if (opcao == 1) {
            for (i = 0; i < totalLivros; i++) {
                printf("\nID: %d\n", livros[i].idlivro);
                printf("Titulo: %s\n", livros[i].nome_livro);
                printf("Autor: %s\n", livros[i].nome_autor);
                printf("Preco: R$ %.2f\n", livros[i].preco);
                printf("Quantidade: %d\n",
                       livros[i].quantidade);
            }

        } else if (opcao == 2) {
            printf("Digite o ID do livro: ");
            scanf("%d", &id);
            limparEntrada();

            for (i = 0; i < totalLivros; i++) {
                if (livros[i].idlivro == id) {
                    printf("\nID: %d\n", livros[i].idlivro);
                    printf("Titulo: %s\n",
                           livros[i].nome_livro);
                    printf("Autor: %s\n",
                           livros[i].nome_autor);
                    printf("Preco: R$ %.2f\n",
                           livros[i].preco);
                    printf("Quantidade: %d\n",
                           livros[i].quantidade);

                    encontrado = 1;
                    break;
                }
            }

            if (encontrado == 0) {
                printf("\nLivro nao encontrado.\n");
            }

        } else {
            printf("\nOpcao invalida.\n");
        }
    }
}

void editarLivro(void) {
    int id;
    int encontrado = 0;
    int i;

    printf("\nDigite o ID do livro que deseja editar: ");
    scanf("%d", &id);
    limparEntrada();

    for (i = 0; i < totalLivros; i++) {
        if (livros[i].idlivro == id) {
            printf("Novo titulo: ");
            lerTexto(livros[i].nome_livro, 50);

            printf("Novo autor: ");
            lerTexto(livros[i].nome_autor, 50);

            printf("Novo preco: ");
            scanf("%f", &livros[i].preco);
            limparEntrada();

            printf("Nova quantidade: ");
            scanf("%d", &livros[i].quantidade);
            limparEntrada();

            encontrado = 1;

            printf("\nLivro editado com sucesso!\n");
            break;
        }
    }

    if (encontrado == 0) {
        printf("\nLivro nao encontrado.\n");
    }
}

void removerLivro(void) {
    int id;
    int encontrado = 0;
    int i;
    int j;

    printf("\nDigite o ID do livro que deseja remover: ");
    scanf("%d", &id);
    limparEntrada();

    for (i = 0; i < totalLivros; i++) {
        if (livros[i].idlivro == id) {
            for (j = i; j < totalLivros - 1; j++) {
                livros[j] = livros[j + 1];
            }

            totalLivros--;
            encontrado = 1;

            printf("\nLivro removido com sucesso!\n");
            break;
        }
    }

    if (encontrado == 0) {
        printf("\nLivro nao encontrado.\n");
    }
}

// ==================== MODULO DE EMPRESTIMOS ==================== //

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

    if (totalEmprestimos >= 50) {
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

    printf("Digite a data do emprestimo (dd/mm/aaaa): ");
    scanf(" %10[^\n]", emprestimos[totalEmprestimos].dataEmprestimo);

    emprestimos[totalEmprestimos].dataDevolucao[0] = '\0';
    emprestimos[totalEmprestimos].emAberto = 1;

    printf("\nEmprestimo registrado com sucesso!\n");
    printf("ID do emprestimo: %d\n", emprestimos[totalEmprestimos].id);

    totalEmprestimos++;
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

            emprestimos[i].emAberto = 0;

            printf("\nDevolucao registrada com sucesso!\n");
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

// ==================== MODULO DE CONSULTAS E RELATÓRIOS ==================== //
// Nome: EDUARDO HENRIQUE DE OLIVEIRA SOUZA
// RGM: 47013109
void moduloRelatorios(void) {
    int opcaoRelatorio;

    do {
        printf("\n========== CONSULTAS E RELATORIOS ==========\n");
        printf("1 - Gerar e salvar resumo geral da biblioteca\n");
        printf("2 - Consultar emprestimos em aberto\n");
        printf("3 - Listar relatorios registrados\n");
        printf("4 - Remover um relatorio\n");
        printf("0 - Voltar ao menu principal\n");
        printf("\nEscolha uma opcao: ");
        
         if (scanf("%d", &opcaoRelatorio) != 1) {
            printf("Entrada invalida! Digite um numero.\\n");
            limparEntrada();
            opcaoRelatorio = -1;
        } else {
            limparEntrada();

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
                    removerRelatorio();
                    break;
                case 0:
                    printf("\n Voltando ao menu principal...\n");
                    break;
                default:
                    printf("\n Opcao invalida! Escolha de 0 a 4.\n");
            }
        }
    } while (opcaoRelatorio != 0);
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

void gerarResumoGeral(void) {
    int posicao;

    if (totalRelatorios >= 50) {
        printf("\n Limite de relatorios atingido!\\n");
        return;
    }

    posicao = totalRelatorios;

    relatorios[posicao].idRelatorio = proximoIdRelatorio;
    relatorios[posicao].totalLeitores = 0;
    
{
        int i;
        for (i = 0; i < totalLeitores; i++) {
            if (leitores[i].ativo == 1) {
                relatorios[posicao].totalLeitores++;
            }
        }
    }

    relatorios[posicao].totalLivros = totalLivros;
    relatorios[posicao].emprestimosEmAberto = contarEmprestimosEmAberto();
    
printf("\\n Digite uma descricao para este relatorio: ");
    lerTexto(relatorios[posicao].descricao, 100);

    printf("\n========== RESUMO GERAL DA BIBLIOTECA ==========\n");
    printf("Leitores ativos: %d\n", relatorios[posicao].totalLeitores);
    printf("Livros cadastrados: %d\n", relatorios[posicao].totalLivros);
    printf("Emprestimos em aberto: %d\n",
           relatorios[posicao].emprestimosEmAberto);
    printf("Descricao: %s\n", relatorios[posicao].descricao);

    totalRelatorios++;
    proximoIdRelatorio++;

    printf("\n Relatorio gerado e salvo com sucesso! ID: %d\n",
           relatorios[posicao].idRelatorio);
}

void listarRelatorios(void) {
    int i;

    printf("\n========== RELATORIOS REGISTRADOS ==========\n");

    if (totalRelatorios == 0) {
        printf("Nenhum relatorio registrado.\n");
        return;
    }

    for (i = 0; i < totalRelatorios; i++) {
        printf("\n ID do relatorio: %d\n", relatorios[i].idRelatorio);
        printf("Descricao: %s\n", relatorios[i].descricao);
        printf("Leitores ativos: %d\n", relatorios[i].totalLeitores);
        printf("Livros cadastrados: %d\n", relatorios[i].totalLivros);
        printf("Emprestimos em aberto: %d\n",
               relatorios[i].emprestimosEmAberto);
        printf("--------------------------------------------\n");
    }
}

void removerRelatorio(void) {
    int id;
    int i;
    int j;
    int encontrado = 0;

    if (totalRelatorios == 0) {
        printf("\n Nao existem relatorios para remover.\n");
        return;
    }

    printf("\n Digite o ID do relatorio que deseja remover: ");
    if (scanf("%d", &id) != 1) {
        printf("ID invalido!\n");
        limparEntrada();
        return;
    }
    limparEntrada();

    for (i = 0; i < totalRelatorios; i++) {
        if (relatorios[i].idRelatorio == id) {
            for (j = i; j < totalRelatorios - 1; j++) {
                relatorios[j] = relatorios[j + 1];
            }

            totalRelatorios--;
            encontrado = 1;
            printf("\n Relatorio removido com sucesso! \n");
            break;
        }
    }

    if (encontrado == 0) {
        printf("\n Relatorio nao encontrado.\n");
    }
}
