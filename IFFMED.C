#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NOME 100
#define MAX_HISTORICO 500

typedef struct Aluno {
    int matricula;
    char nome[MAX_NOME];
    int idade;
    char historicoMedico[MAX_HISTORICO];
    char dataAdmissao[11]; // Data de admissão no formato dd/mm/aaaa
    struct Aluno* prox;  // Ponteiro para o próximo aluno
} Aluno;

// Função para criar um novo aluno
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

// Função para inserir um aluno na lista
void inserirAluno(Aluno** lista, int matricula, const char* nome, int idade, const char* historicoMedico, const char* dataAdmissao) {
    Aluno* novoAluno = criarAluno(matricula, nome, idade, historicoMedico, dataAdmissao);
    novoAluno->prox = *lista;
    *lista = novoAluno;
}

// Função para verificar se a matrícula é válida (só números)
int lerMatricula() {
    int matricula;
    while (1) {
        printf("Matrícula: ");
        if (scanf("%d", &matricula) != 1) {
            // Caso a leitura não seja um número válido (letras ou outros caracteres)
            printf("Erro: A matrícula deve ser um número válido!\n");
            while(getchar() != '\n'); // Limpar o buffer do teclado
        } else {
            return matricula;  // A matrícula foi lida com sucesso
        }
    }
}

// Função para alterar os dados de um aluno
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

// Função para excluir um aluno
void excluirAluno(Aluno** lista, int matricula) {
    Aluno *temp = *lista, *anterior = NULL;

    // Verifica se o aluno a ser removido está na cabeça da lista
    if (temp != NULL && temp->matricula == matricula) {
        *lista = temp->prox;
        free(temp);
        printf("Aluno com matrícula %d excluído com sucesso.\n", matricula);
        return;
    }

    // Procura o aluno na lista
    while (temp != NULL && temp->matricula != matricula) {
        anterior = temp;
        temp = temp->prox;
    }

    // Se o aluno não for encontrado
    if (temp == NULL) {
        printf("Aluno com matrícula %d não encontrado.\n", matricula);
        return;
    }

    // Desvincula o aluno da lista e o exclui
    anterior->prox = temp->prox;
    free(temp);
    printf("Aluno com matrícula %d excluído com sucesso.\n", matricula);
}

// Função para listar todos os alunos
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

// Função para liberar a memória alocada pela lista
void liberarLista(Aluno* lista) {
    Aluno* temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

// Função principal
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
        getchar(); // Limpar o buffer do teclado

        switch (escolha) {
            case 1:
                printf("\nInserir Novo Aluno na Enfermaria:\n");
                matricula = lerMatricula();  // Usando a função para ler matrícula
                getchar(); // Limpar o buffer
                printf("Nome: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;  // Remover o '\n' da string
                printf("Idade: ");
                scanf("%d", &idade);
                getchar(); // Limpar o buffer
                printf("Histórico Médico: ");
                fgets(historicoMedico, MAX_HISTORICO, stdin);
                historicoMedico[strcspn(historicoMedico, "\n")] = 0;
                printf("Data de Admissão (dd/mm/aaaa): ");
                fgets(dataAdmissao, 11, stdin);
                dataAdmissao[strcspn(dataAdmissao, "\n")] = 0;
                inserirAluno(&listaAlunos, matricula, nome, idade, historicoMedico, dataAdmissao);
                break;

            case 2:
                printf("\nAlterar Dados de um Aluno:\n");
                matricula = lerMatricula();  // Usando a função para ler matrícula
                getchar(); // Limpar o buffer
                printf("Novo Nome: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;  // Remover o '\n' da string
                printf("Nova Idade: ");
                scanf("%d", &idade);
                getchar(); // Limpar o buffer
                printf("Novo Histórico Médico: ");
                fgets(historicoMedico, MAX_HISTORICO, stdin);
                historicoMedico[strcspn(historicoMedico, "\n")] = 0;
                printf("Nova Data de Admissão (dd/mm/aaaa): ");
                fgets(dataAdmissao, 11, stdin);
                dataAdmissao[strcspn(dataAdmissao, "\n")] = 0;
                alterarAluno(listaAlunos, matricula, nome, idade, historicoMedico, dataAdmissao);
                break;

            case 3:
                printf("\nExcluir Aluno:\n");
                printf("Matrícula: ");
                scanf("%d", &matricula);
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
