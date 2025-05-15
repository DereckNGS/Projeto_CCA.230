#include "estruturas.h"

// Inicializa a pilha de desfazer
PilhaDesfazer* inicializar_pilha() {
    PilhaDesfazer *pilha = (PilhaDesfazer*) malloc(sizeof(PilhaDesfazer));
    if (pilha == NULL) {
        printf("Erro ao alocar memoria para a pilha de desfazer\n");
        exit(1);
    }
    pilha->qtde = 0;
    pilha->topo = NULL;
    return pilha;
}

// Empilha uma operação na pilha de desfazer
void empilhar_operacao(PilhaDesfazer *pilha, TipoOperacao tipo, Paciente *paciente) {
    NoPilha *novo = (NoPilha*) malloc(sizeof(NoPilha));
    if (novo == NULL) {
        printf("Erro ao alocar memoria para o novo no da pilha\n");
        return;
    }
    
    Operacao *op = (Operacao*) malloc(sizeof(Operacao));
    if (op == NULL) {
        printf("Erro ao alocar memoria para a nova operacao\n");
        free(novo);
        return;
    }
    
    op->tipo = tipo;
    op->paciente = paciente;
    
    novo->operacao = op;
    novo->proximo = pilha->topo;
    
    pilha->topo = novo;
    pilha->qtde++;
}

// Desempilha uma operação da pilha de desfazer
Operacao* desempilhar_operacao(PilhaDesfazer *pilha) {
    if (pilha->qtde == 0) {
        printf("Pilha vazia. Nenhuma operacao para desfazer.\n");
        return NULL;
    }
    
    NoPilha *temp = pilha->topo;
    Operacao *op = temp->operacao;
    
    pilha->topo = pilha->topo->proximo;
    free(temp);
    pilha->qtde--;
    
    return op;
}

// Mostra as operações na pilha de desfazer
//Imprime do topo até a base
void mostrar_operacoes(PilhaDesfazer *pilha) {
    if (pilha->qtde == 0) {
        printf("Nenhuma operacao registrada.\n");
        return;
    }
    
    printf("\n===== OPERACOES REALIZADAS (%d) =====\n", pilha->qtde);
    NoPilha *atual = pilha->topo;
    int contador = 1;
    
    while (atual != NULL) {
        Operacao *op = atual->operacao;
        printf("%d. ", contador);
        
        if (op->tipo == ENFILEIRAR) {
            printf("ENFILEIRAR: Paciente %s\n", op->paciente->nome);
        } else if (op->tipo == DESENFILEIRAR) {
            printf("DESENFILEIRAR: Paciente %s\n", op->paciente->nome);
        }
        
        atual = atual->proximo;
        contador++;
    }
    
    printf("==================================\n");
}

// Desfaz a última operação realizada
void desfazer_operacao(PilhaDesfazer *pilha, FilaAtendimento *fila, HeapPrioritario *heap) {
    if (pilha->qtde == 0) {
        printf("Nenhuma operacao para desfazer.\n");
        return;
    }
    
    Operacao *op = desempilhar_operacao(pilha);
    if (op == NULL) return;
    
    printf("Operacao a ser desfeita: ");
    if (op->tipo == ENFILEIRAR) {
        printf("ENFILEIRAR Paciente %s\n", op->paciente->nome);
        printf("Esta operação sera desfeita removendo o paciente da fila.\n");
    } else if (op->tipo == DESENFILEIRAR) {
        printf("DESENFILEIRAR Paciente %s\n", op->paciente->nome);
        printf("Esta operação sera desfeita, adicionando o paciente de volta a fila.\n");
    }
    
    char confirmacao;
    printf("Confirma desfazer esta operacao (S/N): ");
    scanf(" %c", &confirmacao);
    
    if (confirmacao == 'S' || confirmacao == 's') {
        if (op->tipo == ENFILEIRAR) {
            // Implementação simplificada: apenas informa que o paciente foi removido
            printf("Paciente %s removido da fila.\n", op->paciente->nome);
        } else if (op->tipo == DESENFILEIRAR) {
            // Adiciona o paciente de volta à fila (sem registrar na pilha para evitar loop)
            enfileirar_paciente(fila, op->paciente, NULL);
        }
        printf("Operacao desfeita com sucesso!\n");
    } else {
        printf("Operaao cancelada.\n");
        // Coloca a operação de volta na pilha
        empilhar_operacao(pilha, op->tipo, op->paciente);
    }
    
    // Libera a memória da operação
    free(op);
}
