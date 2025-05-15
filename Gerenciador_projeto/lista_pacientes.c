#include "estruturas.h"

// Inicializa a lista de pacientes
ListaPacientes* inicializar_lista() {
    ListaPacientes *lista = (ListaPacientes*) malloc(sizeof(ListaPacientes));
    if (lista == NULL) {
        printf("Erro ao alocar memoria para a lista de pacientes\n");
        exit(1);
    }
    lista->qtde = 0;
    lista->inicio = NULL;
    return lista;
}

// Cadastra um novo paciente na lista (inserção no início)
void cadastrar_paciente(ListaPacientes *lista, Paciente *paciente) {
    NoPaciente *novo = (NoPaciente*) malloc(sizeof(NoPaciente));
    if (novo == NULL) {
        printf("Erro ao alocar memoria para o novo paciente\n");
        return;
    }
    
    novo->dados = paciente;
    novo->proximo = lista->inicio;
    lista->inicio = novo;
    lista->qtde++;
    
    printf("Paciente %s cadastrado com sucesso!\n", paciente->nome);
}

// Consulta um paciente pelo CPF
Paciente* consultar_paciente(ListaPacientes *lista, char *cpf) {
    NoPaciente *atual = lista->inicio;
    
    while (atual != NULL) {
        if (strcmp(atual->dados->cpf, cpf) == 0) {
            return atual->dados;
        }
        atual = atual->proximo;
    }
    
    return NULL; // Paciente não encontrado
}

// Mostra todos os pacientes cadastrados
void mostrar_lista_pacientes(ListaPacientes *lista) {
    if (lista->qtde == 0) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }
    
    printf("\n===== LISTA DE PACIENTES CADASTRADOS (%d) =====\n", lista->qtde);
    NoPaciente *atual = lista->inicio;
    int contador = 1;
    
    while (atual != NULL) {
        Paciente *p = atual->dados;
        printf("\n--- Paciente %d ---\n", contador);
        printf("Nome: %s\n", p->nome);
        printf("Idade: %d\n", p->idade);
        printf("CPF: %s\n", p->cpf);
        printf("Telefone: %s\n", p->telefone);
        printf("Data de registro: %02d/%02d/%04d\n", 
               p->data_registro.dia, 
               p->data_registro.mes, 
               p->data_registro.ano);
        
        atual = atual->proximo;
        contador++;
    }
    printf("\n==========================================\n");
}

// Atualiza os dados de um paciente
void atualizar_paciente(ListaPacientes *lista, char *cpf, Paciente *novos_dados) {
    NoPaciente *atual = lista->inicio;
    
    while (atual != NULL) { //strcmp-> para comparar strings
        if (strcmp(atual->dados->cpf, cpf) == 0) {
            // Preserva a data de registro original
            Data data_original = atual->dados->data_registro;
            
            // Atualiza os dados
            strcpy(atual->dados->nome, novos_dados->nome);
            atual->dados->idade = novos_dados->idade;
            strcpy(atual->dados->telefone, novos_dados->telefone);
            
            // Mantém o CPF e a data de registro originais
            atual->dados->data_registro = data_original;
            
            printf("Dados do paciente %s atualizados com sucesso!\n", atual->dados->nome);
            return;
        }
        atual = atual->proximo;
    }
    
    printf("Paciente com CPF %s nao encontrado.\n", cpf);
}

// Remove um paciente da lista
void remover_paciente(ListaPacientes *lista, char *cpf) {
    if (lista->inicio == NULL) {
        printf("Lista vazia. Nenhum paciente para remover.\n");
        return;
    }
    
    NoPaciente *atual = lista->inicio;
    NoPaciente *anterior = NULL;
    
    // Caso especial: o primeiro nó contém o paciente a ser removido
    if (strcmp(atual->dados->cpf, cpf) == 0) {
        lista->inicio = atual->proximo;
        printf("Paciente %s removido com sucesso!\n", atual->dados->nome);
        free(atual->dados); // Libera a memória do paciente
        free(atual);        // Libera a memória do nó
        lista->qtde--;
        return;
    }
    
    // Procura o paciente na lista
    while (atual != NULL && strcmp(atual->dados->cpf, cpf) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    
    // Se o paciente foi encontrado
    if (atual != NULL) {
        anterior->proximo = atual->proximo;
        printf("Paciente %s removido com sucesso!\n", atual->dados->nome);
        free(atual->dados); // Libera a memória do paciente
        free(atual);        // Libera a memória do nó
        lista->qtde--;
    } else {
        printf("Paciente com CPF %s não encontrado.\n", cpf);
    }
}
