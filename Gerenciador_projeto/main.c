#include "estruturas.h"

// Função para limpar o buffer de entrada
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para ler uma string com segurança
void ler_string(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove o caractere de nova linha
}

// Função para criar um novo paciente com dados fornecidos pelo usuário
Paciente* criar_paciente() {
    Paciente *p = (Paciente*) malloc(sizeof(Paciente));
    if (p == NULL) {
        printf("Erro ao alocar memoria para o paciente.\n");
        return NULL;
    }
    
    printf("\n--- Cadastro de Paciente ---\n");
    
    printf("Nome: ");
    ler_string(p->nome, sizeof(p->nome));
    
    printf("Idade: ");
    scanf("%d", &p->idade);
    limpar_buffer();
    
    printf("CPF: ");
    ler_string(p->cpf, sizeof(p->cpf));
    
    printf("Telefone: ");
    ler_string(p->telefone, sizeof(p->telefone));
    
    // Obtém a data atual (simplificado)
    printf("Dia de registro: ");
    scanf("%d", &p->data_registro.dia);
    
    printf("Mes de registro: ");
    scanf("%d", &p->data_registro.mes);
    
    printf("Ano de registro: ");
    scanf("%d", &p->data_registro.ano);
    limpar_buffer();
    
    return p;
}

// Função para o menu de cadastro
void menu_cadastro(ListaPacientes *lista) {
    int opcao;
    char cpf[15];
    
    do {
        printf("\n===== MENU DE CADASTRO =====\n");
        printf("1. Cadastrar novo paciente\n");
        printf("2. Consultar paciente cadastrado\n");
        printf("3. Mostrar lista completa\n");
        printf("4. Atualizar dados de paciente\n");
        printf("5. Remover paciente\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_buffer();
        
        switch (opcao) {
            case 1:
                cadastrar_paciente(lista, criar_paciente());
                break;
                
            case 2:
                printf("Digite o CPF do paciente: ");
                ler_string(cpf, sizeof(cpf));
                
                Paciente *p = consultar_paciente(lista, cpf);
                if (p != NULL) {
                    printf("\n--- Dados do Paciente ---\n");
                    printf("Nome: %s\n", p->nome);
                    printf("Idade: %d\n", p->idade);
                    printf("CPF: %s\n", p->cpf);
                    printf("Telefone (11): %s\n", p->telefone);
                    printf("Data de registro 00/00/00: %02d/%02d/%04d\n", 
                           p->data_registro.dia, 
                           p->data_registro.mes, 
                           p->data_registro.ano);
                } else {
                    printf("Paciente nao encontrado.\n");
                }
                break;
                
            case 3:
                mostrar_lista_pacientes(lista);
                break;
                
            case 4:
                printf("Digite o CPF do paciente a ser atualizado: ");
                ler_string(cpf, sizeof(cpf));
                
                if (consultar_paciente(lista, cpf) != NULL) {
                    printf("Digite os novos dados do paciente:\n");
                    Paciente *novos_dados = criar_paciente();
                    atualizar_paciente(lista, cpf, novos_dados);
                    free(novos_dados); // Libera a memória, pois a função atualizar_paciente copia os dados
                } else {
                    printf("Paciente nao encontrado.\n");
                }
                break;
                
            case 5:
                printf("Digite o CPF do paciente a ser removido: ");
                ler_string(cpf, sizeof(cpf));
                remover_paciente(lista, cpf);
                break;
                
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
                
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Função para o menu de atendimento
void menu_atendimento(ListaPacientes *lista, FilaAtendimento *fila, PilhaDesfazer *pilha) {
    int opcao;
    char cpf[15];
    
    do {
        printf("\n===== MENU DE ATENDIMENTO =====\n");
        printf("1. Enfileirar paciente\n");
        printf("2. Desenfileirar paciente\n");
        printf("3. Mostrar fila\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_buffer();
        
        switch (opcao) {
            case 1:
                printf("Digite o CPF do paciente a ser enfileirado: ");
                ler_string(cpf, sizeof(cpf));
                
                Paciente *p = consultar_paciente(lista, cpf);
                if (p != NULL) {
                    enfileirar_paciente(fila, p, pilha);
                } else {
                    printf("Paciente nao encontrado. Cadastre o paciente primeiro.\n");
                }
                break;
                
            case 2:
                desenfileirar_paciente(fila, pilha);
                break;
                
            case 3:
                mostrar_fila(fila);
                break;
                
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
                
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Função para o menu de atendimento prioritário
void menu_atendimento_prioritario(ListaPacientes *lista, HeapPrioritario *heap, PilhaDesfazer *pilha) {
    int opcao;
    char cpf[15];
    
    do {
        printf("\n===== MENU DE ATENDIMENTO PRIORITARIO =====\n");
        printf("1. Enfileirar paciente prioritario\n");
        printf("2. Desenfileirar paciente prioritario\n");
        printf("3. Mostrar fila prioritaria\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_buffer();
        
        switch (opcao) {
            case 1:
                printf("Digite o CPF do paciente a ser enfileirado com prioridade: ");
                ler_string(cpf, sizeof(cpf));
                
                Paciente *p = consultar_paciente(lista, cpf);
                if (p != NULL) {
                    enfileirar_prioritario(heap, p, pilha);
                } else {
                    printf("Paciente nao encontrado. Cadastre o paciente primeiro.\n");
                }
                break;
                
            case 2:
                desenfileirar_prioritario(heap, pilha);
                break;
                
            case 3:
                mostrar_heap(heap);
                break;
                
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
                
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Função para o menu de pesquisa
void menu_pesquisa(ListaPacientes *lista, ArvoreBusca *arvore) {
    int opcao;
    char cpf[15];
    
    do {
        printf("\n===== MENU DE PESQUISA =====\n");
        printf("1. Inserir paciente na árvore de busca\n");
        printf("2. Mostrar registros ordenados por ano\n");
        printf("3. Mostrar registros ordenados por mes\n");
        printf("4. Mostrar registros ordenados por dia\n");
        printf("5. Mostrar registros ordenados por idade\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_buffer();
        
        switch (opcao) {
            case 1:
                printf("Digite o CPF do paciente a ser inserido na arvore: ");
                ler_string(cpf, sizeof(cpf));
                
                Paciente *p = consultar_paciente(lista, cpf);
                if (p != NULL) {
                    inserir_arvore(arvore, p);
                } else {
                    printf("Paciente nao encontrado. Cadastre o paciente primeiro.\n");
                }
                break;
                
            case 2:
                mostrar_por_ano(arvore);
                break;
                
            case 3:
                mostrar_por_mes(arvore);
                break;
                
            case 4:
                mostrar_por_dia(arvore);
                break;
                
            case 5:
                mostrar_por_idade(arvore);
                break;
                
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
                
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Função para o menu de desfazer
void menu_desfazer(PilhaDesfazer *pilha, FilaAtendimento *fila, HeapPrioritario *heap) {
    int opcao;
    
    do {
        printf("\n===== MENU DE DESFAZER =====\n");
        printf("1. Mostrar operações realizadas\n");
        printf("2. Desfazer ultima operacao\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_buffer();
        
        switch (opcao) {
            case 1:
                mostrar_operacoes(pilha);
                break;
                
            case 2:
                desfazer_operacao(pilha, fila, heap);
                break;
                
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
                
            default:
                printf("Opcao invslida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Função para o menu de carregar/salvar
void menu_arquivo(ListaPacientes *lista) {
    int opcao;
    char arquivo[100];
    
    do {
        printf("\n===== MENU DE ARQUIVO =====\n");
        printf("1. Carregar dados de arquivo\n");
        printf("2. Salvar dados em arquivo\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_buffer();
        
        switch (opcao) {
            case 1:
                printf("Digite o nome do arquivo para carregar: ");
                ler_string(arquivo, sizeof(arquivo));
                carregar_dados(lista, arquivo);
                break;
                
            case 2:
                printf("Digite o nome do arquivo para salvar: ");
                ler_string(arquivo, sizeof(arquivo));
                salvar_dados(lista, arquivo);
                break;
                
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
                
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Função principal
int main() {
    int opcao;
    
    // Inicializa as estruturas
    ListaPacientes *lista = inicializar_lista();
    FilaAtendimento *fila = inicializar_fila();
    HeapPrioritario *heap = inicializar_heap();
    ArvoreBusca *arvore = inicializar_arvore();
    PilhaDesfazer *pilha = inicializar_pilha();
    
    do {
        printf("\n===== GERENCIADOR DE ATENDIMENTO MEDICO =====\n");
        printf("1. Cadastrar\n");
        printf("2. Atendimento\n");
        printf("3. Atendimento prioritario\n");
        printf("4. Pesquisa\n");
        printf("5. Desfazer\n");
        printf("6. Carregar / Salvar\n");
        printf("7. Sobre\n");
        printf("0. Sair\n");
        printf("Escolha uma opcaoo: ");
        scanf("%d", &opcao);
        limpar_buffer();
        
        switch (opcao) {
            case 1:
                menu_cadastro(lista);
                break;
                
            case 2:
                menu_atendimento(lista, fila, pilha);
                break;
                
            case 3:
                menu_atendimento_prioritario(lista, heap, pilha);
                break;
                
            case 4:
                menu_pesquisa(lista, arvore);
                break;
                
            case 5:
                menu_desfazer(pilha, fila, heap);
                break;
                
            case 6:
                menu_arquivo(lista);
                break;
                
            case 7:
                mostrar_sobre();
                break;
                
            case 0:
                printf("Saindo do sistema...\n");
                break;
                
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
    
    // Libera a memória alocada 
    free(lista);
    free(fila);
    free(heap);
    free(arvore);
    free(pilha);
    
    return 0;
}
