#include "estruturas.h"

// Inicializa a fila de atendimento
FilaAtendimento* inicializar_fila() {
    FilaAtendimento *fila = (FilaAtendimento*) malloc(sizeof(FilaAtendimento));
    if (fila == NULL) {
        printf("Erro ao alocar memoria para a fila de atendimento\n");
        exit(1);
    }
    fila->qtde = 0;
    fila->head = NULL;
    fila->tail = NULL;
    return fila;
}

// Enfileira um paciente na fila de atendimento(coloca no final da fila)
// A função também registra a operação na pilha de desfazer
void enfileirar_paciente(FilaAtendimento *fila, Paciente *paciente, PilhaDesfazer *pilha) {
    NoFila *novo = (NoFila*) malloc(sizeof(NoFila));
    if (novo == NULL) {
        printf("Erro ao alocar memória para o novo no da fila\n");
        return;
    }
    
    novo->dados = paciente;
    novo->proximo = NULL;
    
    // Se a fila estiver vazia
    if (fila->qtde == 0) {
        fila->head = novo;
    } else {
        fila->tail->proximo = novo;
    }
    
    fila->tail = novo;
    fila->qtde++;
    
    // Registra a operação na pilha de desfazer
    if (pilha != NULL) {
        empilhar_operacao(pilha, ENFILEIRAR, paciente);
    }
    
    printf("Paciente %s enfileirado com sucesso!\n", paciente->nome);
}

// Desenfileira um paciente da fila de atendimento(remove do início da fila)
Paciente* desenfileirar_paciente(FilaAtendimento *fila, PilhaDesfazer *pilha) {
    if (fila->qtde == 0) {
        printf("Fila vazia. Nenhum paciente para atender.\n");
        return NULL;
    }
    
    NoFila *temp = fila->head;
    Paciente *paciente = temp->dados;
    
    // Se há apenas um elemento na fila
    if (fila->qtde == 1) {
        fila->head = NULL;
        fila->tail = NULL;
    } else {
        fila->head = fila->head->proximo;
    }
    
    free(temp);
    fila->qtde--;
    
    // Registra a operação na pilha de desfazer
    if (pilha != NULL) {
        empilhar_operacao(pilha, DESENFILEIRAR, paciente);
    }
    
    printf("Paciente %s atendido com sucesso!\n", paciente->nome);
    return paciente;
}

// Mostra a fila de atendimento
void mostrar_fila(FilaAtendimento *fila) {
    if (fila->qtde == 0) {
        printf("Fila de atendimento vazia.\n");
        return;
    }
    
    printf("\n===== FILA DE ATENDIMENTO (%d) =====\n", fila->qtde);
    NoFila *atual = fila->head;
    int posicao = 1;
    
    while (atual != NULL) {
        Paciente *p = atual->dados;
        printf("%d. %s (CPF: %s)\n", posicao, p->nome, p->cpf);
        atual = atual->proximo;
        posicao++;
    }
    
    printf("==================================\n");
}
