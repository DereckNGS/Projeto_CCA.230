#include "estruturas.h"

// Carrega os dados dos pacientes de um arquivo
void carregar_dados(ListaPacientes *lista, char *arquivo) {
    FILE *fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s para leitura.\n", arquivo);
        return;
    }
    
    char linha[256];
    int contador = 0;
    
    // Limpa a lista atual
    // Implementacao simplificada: apenas reinicializa a lista
    lista->inicio = NULL;
    lista->qtde = 0;
    
    while (fgets(linha, sizeof(linha), fp)) {
        // Remove o caractere de nova linha
        linha[strcspn(linha, "\n")] = 0;
        
        // Aloca memoria para o novo paciente
        Paciente *p = (Paciente*) malloc(sizeof(Paciente));
        if (p == NULL) {
            printf("Erro ao alocar memoria para o paciente.\n");
            continue;
        }
        
        // Formato esperado: nome,idade,cpf,telefone,dia,mes,ano
        char *token = strtok(linha, ",");
        if (token != NULL) {
            strcpy(p->nome, token);
            
            token = strtok(NULL, ",");
            if (token != NULL) {
                p->idade = atoi(token);
                
                token = strtok(NULL, ",");
                if (token != NULL) {
                    strcpy(p->cpf, token);
                    
                    token = strtok(NULL, ",");
                    if (token != NULL) {
                        strcpy(p->telefone, token);
                        
                        token = strtok(NULL, ",");
                        if (token != NULL) {
                            p->data_registro.dia = atoi(token);
                            
                            token = strtok(NULL, ",");
                            if (token != NULL) {
                                p->data_registro.mes = atoi(token);
                                
                                token = strtok(NULL, ",");
                                if (token != NULL) {
                                    p->data_registro.ano = atoi(token);
                                    
                                    // Cadastra o paciente na lista
                                    cadastrar_paciente(lista, p);
                                    contador++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    fclose(fp);
    printf("Dados carregados com sucesso! %d pacientes cadastrados.\n", contador);
}

// Salva os dados dos pacientes em um arquivo
void salvar_dados(ListaPacientes *lista, char *arquivo) {
    FILE *fp = fopen(arquivo, "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", arquivo);
        return;
    }
    
    NoPaciente *atual = lista->inicio;
    int contador = 0;
    
    while (atual != NULL) {
        Paciente *p = atual->dados;
        
        // Formato: nome,idade,cpf,telefone,dia,mes,ano
        fprintf(fp, "%s,%d,%s,%s,%d,%d,%d\n", 
                p->nome, p->idade, p->cpf, p->telefone, 
                p->data_registro.dia, p->data_registro.mes, p->data_registro.ano);
        
        atual = atual->proximo;
        contador++;
    }
    
    fclose(fp);
    printf("Dados salvos com sucesso! %d pacientes registrados no arquivo.\n", contador);
}

// Mostra informacoes sobre o desenvolvedor
void mostrar_sobre() {
    printf("\n===== SOBRE O SISTEMA =====\n");
    printf("Gerenciador de Atendimento Medico\n");
    printf("Estrutura de Dados(CCA230)\n");
    printf("Centro Universitario FEI\n");
    printf("Engenharia de Robos\n");
    printf("Primeiro Semestre de 2025\n");
    printf("Professor: Luciano Rossi\n");
    printf("Desenvolvedor: [Dereck Nasser Garcia Santos]\n");
    printf("Ciclo: Setimo Ciclo\n");
    printf("Data: %s\n", __DATE__);
    printf("==========================\n");
}
