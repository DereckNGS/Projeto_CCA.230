#include "estruturas.h"
#include <stdio.h>

// Inicializa o heap de atendimento prioritário
HeapPrioritario* inicializar_heap() {
    HeapPrioritario *heap = (HeapPrioritario*) malloc(sizeof(HeapPrioritario));
    if (heap == NULL) {
        printf("Erro ao alocar memoria para o heap prioritario\n");
        exit(1);
    }
    heap->tamanho = 0;
    return heap;
}

// Função auxiliar para subir um elemento no heap
void subir_heap(HeapPrioritario *heap, int indice) {
    if (indice <= 0) return;
    
    int pai = (indice - 1) / 2;
    
    // Se o pai tem idade menor que o filho, troca (heap de máximo por idade)
    if (heap->dados[pai]->idade < heap->dados[indice]->idade) {
        Paciente *temp = heap->dados[pai];
        heap->dados[pai] = heap->dados[indice];
        heap->dados[indice] = temp;
        
        // Continua subindo recursivamente
        subir_heap(heap, pai);
    }
}

// Função auxiliar para descer um elemento no heap
void descer_heap(HeapPrioritario *heap, int indice) {
    int maior = indice;
    int esquerda = 2 * indice + 1;
    int direita = 2 * indice + 2;
    
    // Verifica se o filho da esquerda é maior que o pai
    if (esquerda < heap->tamanho && heap->dados[esquerda]->idade > heap->dados[maior]->idade) {
        maior = esquerda;
    }
    
    // Verifica se o filho da direita é maior que o pai e o filho da esquerda
    if (direita < heap->tamanho && heap->dados[direita]->idade > heap->dados[maior]->idade) {
        maior = direita;
    }
    
    // Se o maior não é o pai, troca e continua descendo
    if (maior != indice) {
        Paciente *temp = heap->dados[indice];
        heap->dados[indice] = heap->dados[maior];
        heap->dados[maior] = temp;
        
        // Continua descendo recursivamente
        descer_heap(heap, maior);
    }
}

// Enfileira um paciente no heap prioritário
void enfileirar_prioritario(HeapPrioritario *heap, Paciente *paciente, PilhaDesfazer *pilha) {
    if (heap->tamanho >= 20) {
        printf("Heap cheio. Capacidade maxima de atendimentos prioritarios atingida (20).\n");
        return;
    }
    
    // Adiciona o paciente no final do heap
    heap->dados[heap->tamanho] = paciente;
    
    // Sobe o elemento para manter a propriedade do heap
    subir_heap(heap, heap->tamanho);
    
    heap->tamanho++;
    
    // Registra a operação na pilha de desfazer
    if (pilha != NULL) {
        empilhar_operacao(pilha, ENFILEIRAR, paciente);
    }
    
    printf("Paciente %s enfileirado com prioridade (idade: %d)!\n", paciente->nome, paciente->idade);
}

// Desenfileira um paciente do heap prioritário
Paciente* desenfileirar_prioritario(HeapPrioritario *heap, PilhaDesfazer *pilha) {
    if (heap->tamanho == 0) {
        printf("Heap vazio. Nenhum paciente prioritario para atender.\n");
        return NULL;
    }
    
    // O paciente com maior prioridade está na raiz
    Paciente *paciente = heap->dados[0];
    
    // Move o último elemento para a raiz
    heap->dados[0] = heap->dados[heap->tamanho - 1];
    heap->tamanho--;
    
    // Desce o elemento para manter a propriedade do heap
    if (heap->tamanho > 0) {
        descer_heap(heap, 0);
    }
    
    // Registra a operação na pilha de desfazer
    if (pilha != NULL) {
        empilhar_operacao(pilha, DESENFILEIRAR, paciente);
    }
    
    printf("Paciente prioritario %s atendido com sucesso!\n", paciente->nome);
    return paciente;
}

// Mostra o heap de atendimento prioritário
void mostrar_heap(HeapPrioritario *heap) {
    if (heap->tamanho == 0) {
        printf("Fila de atendimento prioritario vazia.\n");
        return;
    }
    
    printf("\n===== FILA DE ATENDIMENTO PRIORITaRIO (%d) =====\n", heap->tamanho);
    printf("Ordem de atendimento por prioridade (idade):\n");
    
    // Cria uma cópia do heap para não alterar o original
    HeapPrioritario copia;
    copia.tamanho = heap->tamanho;
    
    for (int i = 0; i < heap->tamanho; i++) {
        copia.dados[i] = heap->dados[i];
    }
    
    // Remove os elementos um a um para mostrar em ordem de prioridade
    int posicao = 1;
    while (copia.tamanho > 0) {
        Paciente *p = copia.dados[0];
        printf("%d. %s (Idade: %d, CPF: %s)\n", posicao, p->nome, p->idade, p->cpf);
        
        // Remove o elemento de maior prioridade
        copia.dados[0] = copia.dados[copia.tamanho - 1];
        copia.tamanho--;
        
        // Desce o elemento para manter a propriedade do heap
        if (copia.tamanho > 0) {
            descer_heap(&copia, 0);
        }
        
        posicao++;
    }
    
    printf("==============================================\n");
}
