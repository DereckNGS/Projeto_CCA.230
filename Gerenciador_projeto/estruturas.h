#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar a data
typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

// Estrutura para armazenar os dados do paciente
typedef struct Paciente {
    char nome[100];
    int idade;
    char cpf[15];
    char telefone[20];
    Data data_registro;
} Paciente;

// Estrutura para o nó da lista encadeada de pacientes
typedef struct NoPaciente {
    Paciente *dados;
    struct NoPaciente *proximo;
} NoPaciente;

// Estrutura para a lista encadeada de pacientes
typedef struct ListaPacientes {
    int qtde;
    NoPaciente *inicio;
} ListaPacientes;

// Estrutura para o no da fila de atendimento
typedef struct NoFila {
    Paciente *dados;
    struct NoFila *proximo;
} NoFila;

// Estrutura para a fila de atendimento
typedef struct FilaAtendimento {
    int qtde;
    NoFila *head;
    NoFila *tail;
} FilaAtendimento;

// Estrutura para o heap de atendimento prioritario
typedef struct HeapPrioritario {
    Paciente *dados[20]; // Maximo de 20 pacientes por dia
    int tamanho;
} HeapPrioritario;

// Estrutura para o no da arvore binaria de busca
typedef struct NoArvore {
    Paciente *dados;
    struct NoArvore *filhoEsq;
    struct NoArvore *filhoDir;
} NoArvore;

// Estrutura para a arvore binaria de busca
typedef struct ArvoreBusca {
    NoArvore *raiz;
} ArvoreBusca;

// Tipos de operacoes para a pilha de desfazer
typedef enum TipoOperacao {
    ENFILEIRAR,
    DESENFILEIRAR
} TipoOperacao;

// Estrutura para armazenar operacoes na pilha de desfazer
typedef struct Operacao {
    TipoOperacao tipo;
    Paciente *paciente;
} Operacao;

// Estrutura para o nó da pilha de desfazer
typedef struct NoPilha {
    Operacao *operacao;
    struct NoPilha *proximo;
} NoPilha;

// Estrutura para a pilha de desfazer
typedef struct PilhaDesfazer {
    int qtde;
    NoPilha *topo;
} PilhaDesfazer;

// Funções para manipulação da lista de pacientes
ListaPacientes* inicializar_lista();
void cadastrar_paciente(ListaPacientes *lista, Paciente *paciente);
Paciente* consultar_paciente(ListaPacientes *lista, char *cpf);
void mostrar_lista_pacientes(ListaPacientes *lista);
void atualizar_paciente(ListaPacientes *lista, char *cpf, Paciente *novos_dados);
void remover_paciente(ListaPacientes *lista, char *cpf);

// Funções para manipulação da fila de atendimento
FilaAtendimento* inicializar_fila();
void enfileirar_paciente(FilaAtendimento *fila, Paciente *paciente, PilhaDesfazer *pilha);
Paciente* desenfileirar_paciente(FilaAtendimento *fila, PilhaDesfazer *pilha);
void mostrar_fila(FilaAtendimento *fila);

// Funções para manipulação do heap de atendimento prioritário
HeapPrioritario* inicializar_heap();
void enfileirar_prioritario(HeapPrioritario *heap, Paciente *paciente, PilhaDesfazer *pilha);
Paciente* desenfileirar_prioritario(HeapPrioritario *heap, PilhaDesfazer *pilha);
void mostrar_heap(HeapPrioritario *heap);

// Funções para manipulação da árvore binária de busca
ArvoreBusca* inicializar_arvore();
void inserir_arvore(ArvoreBusca *arvore, Paciente *paciente);
void mostrar_por_ano(ArvoreBusca *arvore);
void mostrar_por_mes(ArvoreBusca *arvore);
void mostrar_por_dia(ArvoreBusca *arvore);
void mostrar_por_idade(ArvoreBusca *arvore);

// Funções para manipulação da pilha de desfazer
PilhaDesfazer* inicializar_pilha();
void empilhar_operacao(PilhaDesfazer *pilha, TipoOperacao tipo, Paciente *paciente);
Operacao* desempilhar_operacao(PilhaDesfazer *pilha);
void mostrar_operacoes(PilhaDesfazer *pilha);
void desfazer_operacao(PilhaDesfazer *pilha, FilaAtendimento *fila, HeapPrioritario *heap);

// Funções para carregar e salvar dados
void carregar_dados(ListaPacientes *lista, char *arquivo);
void salvar_dados(ListaPacientes *lista, char *arquivo);

// Função para mostrar informações sobre o desenvolvedor
void mostrar_sobre();

#endif // ESTRUTURAS_H
