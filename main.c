
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100
#define TAM_ID 6

typedef struct {
    char id[TAM_ID + 1];
    char nome[100];
    int prioridade;
    char descricao[100];
} Paciente;

const char *cores[] = {
    "",
    "VERMELHO",
    "LARANJA",
    "AMARELO",
    "VERDE",
    "AZUL"
};

const char *classificacoes[] = {
    "",
    "EMERGENCIA",
    "MUITO URGENTE",
    "URGENTE",
    "POUCO URGENTE",
    "NAO URGENTE"
};

const char *tempos[] = {
    "",
    "Imediato",
    "10 minutos",
    "60 minutos",
    "120 minutos",
    "240 minutos"
};

// Gera um ID aleatorio de 6 caracteres.
void gerarID(char id[]) {
    const char caracteres[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    int quantidade = (int)(sizeof(caracteres) - 1);

    for (int i = 0; i < TAM_ID; i++) {
        id[i] = caracteres[rand() % quantidade];
    }

    id[TAM_ID] = '\0';
}

// Verifica se o ID ja existe.
int idExiste(Paciente pacientes[], int total, const char id[]) {
    for (int i = 0; i < total; i++) {
        if (strcmp(pacientes[i].id, id) == 0) {
            return 1;
        }
    }

    return 0;
}

// Gera um ID unico.
void gerarIDUnico(Paciente pacientes[], int total, char id[]) {
    do {
        gerarID(id);
    } while (idExiste(pacientes, total, id));
}

// Ordena os pacientes por prioridade usando Insertion Sort.
void ordenarPacientes(Paciente pacientes[], int total) {
    for (int i = 1; i < total; i++) {
        Paciente atual = pacientes[i];
        int j = i - 1;

        while (j >= 0 &&
               pacientes[j].prioridade > atual.prioridade) {
            pacientes[j + 1] = pacientes[j];
            j--;
        }

        pacientes[j + 1] = atual;
    }
}

// Exibe a tabela de pacientes.
void mostrarTabela(Paciente pacientes[], int total) {
    ordenarPacientes(pacientes, total);

    printf("\n");
    printf("========================================================================================\n");
    printf("                         SISTEMA DE TRIAGEM HOSPITALAR\n");
    printf("========================================================================================\n");

    printf("%-8s %-20s %-13s %-19s %-14s %s\n",
           "ID", "NOME", "COR", "CLASSIFICACAO",
           "TEMPO-ALVO", "DESCRICAO");

    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < total; i++) {
        int p = pacientes[i].prioridade;

        printf("%-8s %-20.20s %-13s %-19s %-14s %s\n",
               pacientes[i].id,
               pacientes[i].nome,
               cores[p],
               classificacoes[p],
               tempos[p],
               pacientes[i].descricao);
    }

    printf("========================================================================================\n");
    printf("Total de pacientes: %d\n", total);
}

// Le uma linha de texto sem exigir Enter duas vezes.
int lerTexto(const char *mensagem, char destino[], int tamanho) {
    printf("%s", mensagem);
    fflush(stdout);

    if (fgets(destino, tamanho, stdin) == NULL) {
        return 0;
    }

    char *quebraLinha = strchr(destino, '\n');

    if (quebraLinha != NULL) {
        *quebraLinha = '\0';
    } else {
        // Limpa o restante se o texto ultrapassar o limite.
        int c;

        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    return 1;
}

// Cadastra um novo paciente.
void cadastrarPaciente(Paciente pacientes[], int *total) {
    int prioridade;
    char nome[100];
    char descricao[100];

    if (*total >= MAX) {
        printf("\nLimite de pacientes atingido!\n");
        return;
    }

    printf("\n--- CADASTRO DE PACIENTE ---\n");

    if (!lerTexto("Nome do paciente: ", nome, sizeof(nome))) {
        printf("Erro ao ler o nome.\n");
        return;
    }

    if (strlen(nome) == 0) {
        printf("O nome nao pode ficar vazio.\n");
        return;
    }

    if (!lerTexto("Descricao do caso: ",
                  descricao, sizeof(descricao))) {
        printf("Erro ao ler a descricao.\n");
        return;
    }

    if (strlen(descricao) == 0) {
        strcpy(descricao, "Caso sem descricao");
    }

    printf("\nNiveis de classificacao da simulacao:\n");
    printf("1 - Vermelho | Emergencia     | Imediato\n");
    printf("2 - Laranja  | Muito urgente  | 10 minutos\n");
    printf("3 - Amarelo  | Urgente        | 60 minutos\n");
    printf("4 - Verde    | Pouco urgente  | 120 minutos\n");
    printf("5 - Azul     | Nao urgente     | 240 minutos\n");

    printf("\nClassificacao atribuida na simulacao (1 a 5): ");

    if (scanf("%d", &prioridade) != 1) {
        printf("Entrada invalida.\n");

        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }

        return;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }

    if (prioridade < 1 || prioridade > 5) {
        printf("Nivel invalido. Escolha de 1 a 5.\n");
        return;
    }

    // Preenche os dados do novo paciente.
    gerarIDUnico(pacientes, *total, pacientes[*total].id);

    strcpy(pacientes[*total].nome, nome);
    pacientes[*total].prioridade = prioridade;
    strcpy(pacientes[*total].descricao, descricao);

    (*total)++;

    printf("\nPaciente cadastrado com sucesso!\n");
    printf("ID gerado: %s\n", pacientes[*total - 1].id);
    printf("Atualizando tabela de prioridades...\n");

    mostrarTabela(pacientes, *total);
}

int main(void) {
    srand((unsigned int)time(NULL));

    Paciente pacientes[MAX] = {0};
    int total = 4;
    int opcao;

    char *nomesIniciais[] = {
        "Carlos Mendes",
        "Mariana Oliveira",
        "Joao Pedro Santos",
        "Ana Beatriz Lima"
    };

    int prioridadesIniciais[] = {1, 2, 3, 4};

    char *descricoesIniciais[] = {
        "Infarto",
        "Corte profundo na perna esquerda",
        "Tosse com sangue e febre",
        "Ansia de vomito"
    };

    // Cria os quatro pacientes iniciais.
    for (int i = 0; i < total; i++) {
        gerarIDUnico(pacientes, i, pacientes[i].id);

        strcpy(pacientes[i].nome, nomesIniciais[i]);
        pacientes[i].prioridade = prioridadesIniciais[i];
        strcpy(pacientes[i].descricao, descricoesIniciais[i]);
    }

    printf("Sistema academico de triagem hospitalar\n");
    printf("Simulacao educativa - nao utilizar em atendimento real.\n");

    mostrarTabela(pacientes, total);

    do {
        printf("\nMENU PRINCIPAL\n");
        printf("1 - Cadastrar paciente\n");
        printf("2 - Visualizar tabela de urgencia\n");
        printf("0 - Encerrar programa\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida.\n");

            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
            }

            opcao = -1;
            continue;
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }

        switch (opcao) {
            case 1:
                cadastrarPaciente(pacientes, &total);
                break;

            case 2:
                mostrarTabela(pacientes, total);
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}