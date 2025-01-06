#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_NOME 100
#define MAX_HISTORICO 500

typedef struct Aluno {
    int matricula;
    char nome[MAX_NOME];
    int idade;
    char historicoMedico[MAX_HISTORICO];
    char dataAdmissao[11];
    struct Aluno* prox;
} Aluno;

Aluno* criarAluno(int matricula, const char* nome, int idade, const char* historicoMedico, const char* dataAdmissao) {
    Aluno* novoAluno = (Aluno*)malloc(sizeof(Aluno));
    novoAluno->matricula = matricula;
    strncpy(novoAluno->nome, nome, MAX_NOME);
    novoAluno->idade = idade;
    strncpy(novoAluno->historicoMedico, historicoMedico, MAX_HISTORICO);
    strncpy(novoAluno->dataAdmissao, dataAdmissao, 11);
    novoAluno->prox = NULL;
    return novoAluno;
}

void inserirAluno(Aluno** lista, int matricula, const char* nome, int idade, const char* historicoMedico, const char* dataAdmissao) {
    Aluno* novoAluno = criarAluno(matricula, nome, idade, historicoMedico, dataAdmissao);
    novoAluno->prox = *lista;
    *lista = novoAluno;
}

int lerMatricula() {
    int matricula;
    while (1) {
        printf("Matrícula: ");
        if (scanf("%d", &matricula) != 1) {
            printf("Erro: A matrícula deve ser um número válido!\n");
            while(getchar() != '\n');
        } else {
            return matricula;
        }
    }
}

int nomeValido(const char* nome) {
    for (int i = 0; nome[i] != '\0'; i++) {
        if (isdigit(nome[i])) {
            return 0;
        }
    }
    return 1;
}

int lerIdade() {
    int idade;
    while (1) {
        printf("Idade: ");
        if (scanf("%d", &idade) != 1 || idade <= 0) {
            printf("Erro: A idade deve ser um número inteiro positivo!\n");
            while(getchar() != '\n');
        } else {
            return idade;
        }
    }
}

int dataValida(const char* data) {
    int dia, mes, ano;
    if (strlen(data) != 10) {
        return 0;
    }
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) {
        return 0;
    }
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900) {
        return 0;
    }
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
        return 0;
    }
    if (mes == 2) {
        if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
            if (dia > 29) return 0;
        } else {
            if (dia > 28) return 0;
        }
    }
    return 1;
}

void alterarAluno(Aluno* lista, int matricula, const char* novoNome, int novaIdade, const char* novoHistoricoMedico, const char* novaDataAdmissao) {
    Aluno* temp = lista;
    while (temp != NULL) {
        if (temp->matricula == matricula) {
            strncpy(temp->nome, novoNome, MAX_NOME);
            temp->idade = novaIdade;
            strncpy(temp->historicoMedico, novoHistoricoMedico, MAX_HISTORICO);
            strncpy(temp->dataAdmissao, novaDataAdmissao, 11);
            printf("Aluno com matrícula %d alterado com sucesso.\n", matricula);
            return;
        }
        temp = temp->prox;
    }
    printf("Aluno com matrícula %d não encontrado.\n", matricula);
}

void excluirAluno(Aluno** lista, int matricula) {
    Aluno *temp = *lista, *anterior = NULL;
    if (temp != NULL && temp->matricula == matricula) {
        *lista = temp->prox;
        free(temp);
        printf("Aluno com matrícula %d excluído com sucesso.\n", matricula);
        return;
    }
    while (temp != NULL && temp->matricula != matricula) {
        anterior = temp;
        temp = temp->prox;
    }
    if (temp == NULL) {
        printf("Aluno com matrícula %d não encontrado.\n", matricula);
        return;
    }
    anterior->prox = temp->prox;
    free(temp);
    printf("Aluno com matrícula %d excluído com sucesso.\n", matricula);
}

void listarAlunos(Aluno* lista) {
    Aluno* temp = lista;
    if (temp == NULL) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    printf("\nLista de Alunos da Enfermaria IFF Med:\n");
    while (temp != NULL) {
        printf("\nMatrícula: %d\n", temp->matricula);
        printf("Nome: %s\n", temp->nome);
        printf("Idade: %d\n", temp->idade);
        printf("Histórico Médico: %s\n", temp->historicoMedico);
        printf("Data de Admissão: %s\n", temp->dataAdmissao);
        printf("----------------------------\n");
        temp = temp->prox;
    }
}

void liberarLista(Aluno* lista) {
    Aluno* temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

int main() {
    Aluno* listaAlunos = NULL;
    int escolha, matricula, idade;
    char nome[MAX_NOME];
    char historicoMedico[MAX_HISTORICO];
    char dataAdmissao[11];

    while (1) {
        printf("\nMenu de Opções IFF Med - Enfermaria:\n");
        printf("1. Inserir novo aluno\n");
        printf("2. Alterar dados de um aluno\n");
        printf("3. Excluir aluno\n");
        printf("4. Listar todos os alunos\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);
        getchar();

        switch (escolha) {
            case 1:
                printf("\nInserir Novo Aluno na Enfermaria:\n");
                matricula = lerMatricula();
                getchar();
                while (1) {
                    printf("Nome: ");
                    fgets(nome, MAX_NOME, stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    if (nomeValido(nome)) {
                        break;
                    } else {
                        printf("Erro: O nome não pode conter números. Tente novamente.\n");
                    }
                }
                idade = lerIdade();
                getchar();
                printf("Histórico Médico: ");
                fgets(historicoMedico, MAX_HISTORICO, stdin);
                historicoMedico[strcspn(historicoMedico, "\n")] = 0;
                while (1) {
                    printf("Data de Admissão (dd/mm/aaaa): ");
                    fgets(dataAdmissao, 11, stdin);
                    dataAdmissao[strcspn(dataAdmissao, "\n")] = 0;
                    if (dataValida(dataAdmissao)) {
                        break;
                    } else {
                        printf("Erro: Data inválida! O formato deve ser dd/mm/aaaa.\n");
                    }
                }
                inserirAluno(&listaAlunos, matricula, nome, idade, historicoMedico, dataAdmissao);
                break;

            case 2:
                printf("\nAlterar Dados de um Aluno:\n");
                matricula = lerMatricula();
                getchar();
                while (1) {
                    printf("Novo Nome: ");
                    fgets(nome, MAX_NOME, stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    if (nomeValido(nome)) {
                        break;
                    } else {
                        printf("Erro: O nome não pode conter números. Tente novamente.\n");
                    }
                }
                idade = lerIdade();
                getchar();
                printf("Novo Histórico Médico: ");
                fgets(historicoMedico, MAX_HISTORICO, stdin);
                historicoMedico[strcspn(historicoMedico, "\n")] = 0;
                while (1) {
                    printf("Nova Data de Admissão (dd/mm/aaaa): ");
                    fgets(dataAdmissao, 11, stdin);
                    dataAdmissao[strcspn(dataAdmissao, "\n")] = 0;
                    if (dataValida(dataAdmissao)) {
                        break;
                    } else {
                        printf("Erro: Data inválida! O formato deve ser dd/mm/aaaa.\n");
                    }
                }
                alterarAluno(listaAlunos, matricula, nome, idade, historicoMedico, dataAdmissao);
                break;

            case 3:
                printf("\nExcluir Aluno:\n");
                matricula = lerMatricula();
                excluirAluno(&listaAlunos, matricula);
                break;

            case 4:
                listarAlunos(listaAlunos);
                break;

            case 5:
                liberarLista(listaAlunos);
                printf("Saindo do programa...\n");
                return 0;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
    return 0;
}
