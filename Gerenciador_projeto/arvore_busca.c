#include "estruturas.h"
#include <stdio.h>

// Funcao auxiliar para percorrer a arvore em ordem (para mostrar por ano)
void percorrer_em_ordem_ano(NoArvore *no) {
    if (no == NULL) return;
    
    percorrer_em_ordem_ano(no->filhoEsq);
    
    Paciente *p = no->dados;
    printf("Nome: %s, Data: %02d/%02d/%04d, Idade: %d\n", 
           p->nome, p->data_registro.dia, p->data_registro.mes, 
           p->data_registro.ano, p->idade);
    
    percorrer_em_ordem_ano(no->filhoDir);
}

// Funcao auxiliar para percorrer a arvore em ordem (para mostrar por mes)
void percorrer_em_ordem_mes(NoArvore *no) {
    if (no == NULL) return;
    
    percorrer_em_ordem_mes(no->filhoEsq);
    
    Paciente *p = no->dados;
    printf("Nome: %s, Data: %02d/%02d/%04d, Idade: %d\n", 
           p->nome, p->data_registro.dia, p->data_registro.mes, 
           p->data_registro.ano, p->idade);
    
    percorrer_em_ordem_mes(no->filhoDir);
}

// Funcao auxiliar para percorrer a arvore em ordem (para mostrar por dia)
void percorrer_em_ordem_dia(NoArvore *no) {
    if (no == NULL) return;
    
    percorrer_em_ordem_dia(no->filhoEsq);
    
    Paciente *p = no->dados;
    printf("Nome: %s, Data: %02d/%02d/%04d, Idade: %d\n", 
           p->nome, p->data_registro.dia, p->data_registro.mes, 
           p->data_registro.ano, p->idade);
    
    percorrer_em_ordem_dia(no->filhoDir);
}

// Funcao auxiliar para percorrer a arvore em ordem (para mostrar por idade)
void percorrer_em_ordem_idade(NoArvore *no) {
    if (no == NULL) return;
    
    percorrer_em_ordem_idade(no->filhoEsq);
    
    Paciente *p = no->dados;
    printf("Nome: %s, Idade: %d, Data: %02d/%02d/%04d\n", 
           p->nome, p->idade, p->data_registro.dia, p->data_registro.mes, 
           p->data_registro.ano);
    
    percorrer_em_ordem_idade(no->filhoDir);
}

// Inicializa a arvore binaria de busca
ArvoreBusca* inicializar_arvore() {
    ArvoreBusca *arvore = (ArvoreBusca*) malloc(sizeof(ArvoreBusca));
    if (arvore == NULL) {
        printf("Erro ao alocar memoria para a arvore de busca\n");
        exit(1);
    }
    arvore->raiz = NULL;
    return arvore;
}

// Funcao auxiliar para inserir um no na arvore por ano
NoArvore* inserir_no_por_ano(NoArvore *raiz, Paciente *paciente) {
    if (raiz == NULL) {
        NoArvore *novo = (NoArvore*) malloc(sizeof(NoArvore));
        if (novo == NULL) {
            printf("Erro ao alocar memoria para o novo no da arvore\n");
            return NULL;
        }
        novo->dados = paciente;
        novo->filhoEsq = NULL;
        novo->filhoDir = NULL;
        return novo;
    }
    
    // Compara o ano de registro
    if (paciente->data_registro.ano < raiz->dados->data_registro.ano) {
        raiz->filhoEsq = inserir_no_por_ano(raiz->filhoEsq, paciente);
    } else {
        raiz->filhoDir = inserir_no_por_ano(raiz->filhoDir, paciente);
    }
    
    return raiz;
}

// Funcao auxiliar para inserir um no na arvore por mes
NoArvore* inserir_no_por_mes(NoArvore *raiz, Paciente *paciente) {
    if (raiz == NULL) {
        NoArvore *novo = (NoArvore*) malloc(sizeof(NoArvore));
        if (novo == NULL) {
            printf("Erro ao alocar memoria para o novo no da arvore\n");
            return NULL;
        }
        novo->dados = paciente;
        novo->filhoEsq = NULL;
        novo->filhoDir = NULL;
        return novo;
    }
    
    // Compara o mes de registro
    if (paciente->data_registro.mes < raiz->dados->data_registro.mes) {
        raiz->filhoEsq = inserir_no_por_mes(raiz->filhoEsq, paciente);
    } else {
        raiz->filhoDir = inserir_no_por_mes(raiz->filhoDir, paciente);
    }
    
    return raiz;
}

// Funcao auxiliar para inserir um no na arvore por dia
NoArvore* inserir_no_por_dia(NoArvore *raiz, Paciente *paciente) {
    if (raiz == NULL) {
        NoArvore *novo = (NoArvore*) malloc(sizeof(NoArvore));
        if (novo == NULL) {
            printf("Erro ao alocar memoria para o novo no da arvore\n");
            return NULL;
        }
        novo->dados = paciente;
        novo->filhoEsq = NULL;
        novo->filhoDir = NULL;
        return novo;
    }
    
    // Compara o dia de registro
    if (paciente->data_registro.dia < raiz->dados->data_registro.dia) {
        raiz->filhoEsq = inserir_no_por_dia(raiz->filhoEsq, paciente);
    } else {
        raiz->filhoDir = inserir_no_por_dia(raiz->filhoDir, paciente);
    }
    
    return raiz;
}

// Funcao auxiliar para inserir um no na arvore por idade
NoArvore* inserir_no_por_idade(NoArvore *raiz, Paciente *paciente) {
    if (raiz == NULL) {
        NoArvore *novo = (NoArvore*) malloc(sizeof(NoArvore));
        if (novo == NULL) {
            printf("Erro ao alocar memoria para o novo no da arvore\n");
            return NULL;
        }
        novo->dados = paciente;
        novo->filhoEsq = NULL;
        novo->filhoDir = NULL;
        return novo;
    }
    
    // Compara a idade
    if (paciente->idade < raiz->dados->idade) {
        raiz->filhoEsq = inserir_no_por_idade(raiz->filhoEsq, paciente);
    } else {
        raiz->filhoDir = inserir_no_por_idade(raiz->filhoDir, paciente);
    }
    
    return raiz;
}

// Insere um paciente na arvore binaria de busca
void inserir_arvore(ArvoreBusca *arvore, Paciente *paciente) {
    arvore->raiz = inserir_no_por_ano(arvore->raiz, paciente);
    printf("Paciente %s inserido na arvore de busca!\n", paciente->nome);
}

// Mostra os registros ordenados por ano
void mostrar_por_ano(ArvoreBusca *arvore) {
    if (arvore->raiz == NULL) {
        printf("Arvore vazia. Nenhum paciente para mostrar.\n");
        return;
    }
    
    printf("\n===== PACIENTES ORDENADOS POR ANO DE REGISTRO =====\n");
    percorrer_em_ordem_ano(arvore->raiz);
    printf("==================================================\n");
}

// Mostra os registros ordenados por mes
void mostrar_por_mes(ArvoreBusca *arvore) {
    if (arvore->raiz == NULL) {
        printf("Arvore vazia. Nenhum paciente para mostrar.\n");
        return;
    }
    
    // Cria uma nova arvore ordenada por mes
    ArvoreBusca arvore_mes;
    arvore_mes.raiz = NULL;
    
    // Funcao auxiliar para percorrer a arvore original e inserir na nova arvore
    void preencher_arvore_mes(NoArvore *no) {
        if (no == NULL) return;
        
        preencher_arvore_mes(no->filhoEsq);
        arvore_mes.raiz = inserir_no_por_mes(arvore_mes.raiz, no->dados);
        preencher_arvore_mes(no->filhoDir);
    }
    
    preencher_arvore_mes(arvore->raiz);
    
    printf("\n===== PACIENTES ORDENADOS POR MES DE REGISTRO =====\n");
    percorrer_em_ordem_mes(arvore_mes.raiz);
    printf("==================================================\n");
}

// Mostra os registros ordenados por dia
void mostrar_por_dia(ArvoreBusca *arvore) {
    if (arvore->raiz == NULL) {
        printf("Arvore vazia. Nenhum paciente para mostrar.\n");
        return;
    }
    
    // Cria uma nova Arvore ordenada por dia
    ArvoreBusca arvore_dia;
    arvore_dia.raiz = NULL;
    
    // Funcao auxiliar para percorrer a arvore original e inserir na nova arvore
    void preencher_arvore_dia(NoArvore *no) {
        if (no == NULL) return;
        
        preencher_arvore_dia(no->filhoEsq);
        arvore_dia.raiz = inserir_no_por_dia(arvore_dia.raiz, no->dados);
        preencher_arvore_dia(no->filhoDir);
    }
    
    preencher_arvore_dia(arvore->raiz);
    
    printf("\n===== PACIENTES ORDENADOS POR DIA DE REGISTRO =====\n");
    percorrer_em_ordem_dia(arvore_dia.raiz);
    printf("==================================================\n");
}

// Mostra os registros ordenados por idade
void mostrar_por_idade(ArvoreBusca *arvore) {
    if (arvore->raiz == NULL) {
        printf("Arvore vazia. Nenhum paciente para mostrar.\n");
        return;
    }
    
    // Cria uma nova arvore ordenada por idade
    ArvoreBusca arvore_idade;
    arvore_idade.raiz = NULL;
    
    // Funcao auxiliar para percorrer a arvore original e inserir na nova arvore
    void preencher_arvore_idade(NoArvore *no) {
        if (no == NULL) return;
        
        preencher_arvore_idade(no->filhoEsq);
        arvore_idade.raiz = inserir_no_por_idade(arvore_idade.raiz, no->dados);
        preencher_arvore_idade(no->filhoDir);
    }
    
    preencher_arvore_idade(arvore->raiz);
    
    printf("\n===== PACIENTES ORDENADOS POR IDADE =====\n");
    percorrer_em_ordem_idade(arvore_idade.raiz);
    printf("========================================\n");
}
