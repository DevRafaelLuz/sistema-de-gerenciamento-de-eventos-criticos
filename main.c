#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

enum tipoEvento { ACIDENTE_TRANSITO, FALHA_SEMAFORO, INTERRUPCAO_ENERGIA, ALAGAMENTO, INCENDIO };
enum status { ATIVO, RESOLVIDO };

// Definição do nó da árvore AVL para eventos críticos
typedef struct EventoCritico {
    int id;
    enum tipoEvento tipo;
    int seriedade;
    struct tm dataHora;
    char regiao[50];
    enum status situacao;
    int altura;
    struct EventoCritico *esquerda, *direita;
} EventoCritico;

// Função para calcular a altura de um nó
int calcularAlturaNO(struct EventoCritico *no) {
    if (no == NULL) {
        return -1;
    }
    return no->altura;
}

// Função para calcular o maior valor entre dois números
int calcularMaiorValor(int x, int y) {
    return (x > y) ? x : y;
}

// Função para criar novo nó
struct EventoCritico *criarNO(int id, enum tipoEvento tipo, int seriedade, struct tm dataHora, char *regiao, enum status situacao) {
    struct EventoCritico *no = (struct EventoCritico *)malloc(sizeof(struct EventoCritico));
    no->id = id;
    no->tipo = tipo;
    no->seriedade = seriedade;
    no->dataHora = dataHora;
    strcpy(no->regiao, regiao);
    no->situacao = situacao;
    no->altura = 0;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

// Função para realizar rotação simples à esquerda
struct EventoCritico *rotacaoRR(struct EventoCritico *raiz) {
    struct EventoCritico *no = raiz->direita;
    raiz->direita = no->esquerda;
    no->esquerda = raiz;
    raiz->altura = calcularMaiorValor(calcularAlturaNO(raiz->esquerda), calcularAlturaNO(raiz->direita)) + 1;
    no->altura = calcularMaiorValor(calcularAlturaNO(no->esquerda), calcularAlturaNO(no->direita)) + 1;
    return no;
}

// Função para realizar rotação simples à direita
struct EventoCritico *rotacaoLL(struct EventoCritico *raiz) {
    struct EventoCritico *no = raiz->esquerda;
    raiz->esquerda = no->direita;
    no->direita = raiz;
    raiz->altura = calcularMaiorValor(calcularAlturaNO(raiz->esquerda), calcularAlturaNO(raiz->direita)) + 1;
    no->altura = calcularMaiorValor(calcularAlturaNO(no->esquerda), calcularAlturaNO(no->direita)) + 1;
    return no;
}

// Função para realizar rotação dupla à esquerda-direita
struct EventoCritico *rotacaoLR(struct EventoCritico *raiz) {
    raiz->esquerda = rotacaoRR(raiz->esquerda);
    return rotacaoLL(raiz);
}

// Função para realizar rotação dupla à direita-esquerda
struct EventoCritico *rotacaoRL(struct EventoCritico *raiz) {
    raiz->direita = rotacaoLL(raiz->direita);
    return rotacaoRR(raiz);
}

// Função para calcular o fator de balanceamento
int fatorBalanceamento(struct EventoCritico *no) {
    if (no == NULL) {
        return 0;
    }
    return calcularAlturaNO(no->esquerda) - calcularAlturaNO(no->direita);
}

// Função para cadastrar um novo evento crítico
struct EventoCritico *cadastrarEventoCritico(struct EventoCritico *raiz, int id, enum tipoEvento tipo, int seriedade, struct tm dataHora, char *regiao, enum status situacao) {
    if (raiz == NULL) {
        return criarNO(id, tipo, seriedade, dataHora, regiao, situacao);
    }

    if (id < raiz->id) {
        raiz->esquerda = cadastrarEventoCritico(raiz->esquerda, id, tipo, seriedade, dataHora, regiao, situacao);
    } else if (id > raiz->id) {
        raiz->direita = cadastrarEventoCritico(raiz->direita, id, tipo, seriedade, dataHora, regiao, situacao);
    } else {
        return raiz; // IDs duplicados não são permitidos
    }

    raiz->altura = calcularMaiorValor(calcularAlturaNO(raiz->esquerda), calcularAlturaNO(raiz->direita)) + 1;

    int fb = fatorBalanceamento(raiz);

    // Casos de desbalanceamento
    if (fb > 1 && id < raiz->esquerda->id) {
        return rotacaoLL(raiz);
    }
    if (fb < -1 && id > raiz->direita->id) {
        return rotacaoRR(raiz);
    }
    if (fb > 1 && id > raiz->esquerda->id) {
        return rotacaoLR(raiz);
    }
    if (fb < -1 && id < raiz->direita->id) {
        return rotacaoRL(raiz);
    }
    return raiz;
}

// Função para encontrar o menor valor em uma subárvore
struct EventoCritico *encontraMenorValor(struct EventoCritico *no) {
    struct EventoCritico *atual = no;
    while (atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

// Função para remover um evento crítico
struct EventoCritico *removerEventoCritico(struct EventoCritico *raiz, int id) {
    if (raiz == NULL || raiz->situacao == ATIVO) {
        printf("+------------------------------------------------------+\n");
        printf("|       Nao e possivel remover o evento critico.       |\n");
        printf("|     Causa: evento ativo ou ID do evento invalido!    |\n");
        printf("+------------------------------------------------------+\n");
        return raiz;
    }

    if (id < raiz->id) {
        raiz->esquerda = removerEventoCritico(raiz->esquerda, id);
    } else if (id > raiz->id) {
        raiz->direita = removerEventoCritico(raiz->direita, id);
    } else {
        if (raiz->esquerda == NULL || raiz->direita == NULL) {
            struct EventoCritico *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else { // Caso 2: Nó com dois filhos
            struct EventoCritico *temp = encontraMenorValor(raiz->direita);
            raiz->id = temp->id;
            raiz->direita = removerEventoCritico(raiz->direita, temp->id);
        }
    }
    // Se a árvore estiver vazia após a remoção
    if (raiz == NULL) {
        return raiz;
    }

    // Atualiza a altura
    raiz->altura = calcularMaiorValor(calcularAlturaNO(raiz->esquerda), calcularAlturaNO(raiz->direita)) + 1;

    // Rebalanceamento
    int fb = fatorBalanceamento(raiz);

    // LL
    if (fb > 1 && fatorBalanceamento(raiz->esquerda) >= 0) { return rotacaoLL(raiz); }

    // LR
    if (fb > 1 && fatorBalanceamento(raiz->esquerda) < 0) { return rotacaoLR(raiz); }

    // RR
    if (fb < -1 && fatorBalanceamento(raiz->direita) <= 0) { return rotacaoRR(raiz); }

    // RL
    if (fb < -1 && fatorBalanceamento(raiz->direita) > 0) { return rotacaoRL(raiz); }

    return raiz;
}

// Função para buscar um evento crítico por ID
struct EventoCritico *buscarEventoCriticoPorID(struct EventoCritico *raiz, int id) {
    if (raiz == NULL) {
        return NULL;
    } else {
        if (id < raiz->id) {
            buscarEventoCriticoPorID(raiz->esquerda, id);
        } 
        if (id > raiz->id) {
            buscarEventoCriticoPorID(raiz->direita, id);
        }
        return raiz;
    }
}

// Função para listar eventos ativos por intervalo de seriedade
void listarEventosAtivosPorSeriedade() {

}

// Função para listar eventos por intervalo de ID
void listarEventosPorIntervaloDeID() {

}

// Função para alterar o status de um evento
void alterarStatusEvento() {

}

// Função para atualizar a seriedade de um evento ativo
void atualizarSeriedadeEventoAtivo() {

}

// Função para gerar um ID único para cada evento crítico
int geraId() {
    srand(time(NULL));
    return rand() % 900 + 100;
}

struct tm obtemDataHoraAtual(struct tm dataHora) {
    time_t t = time(NULL);
    dataHora = *localtime(&t);
    return dataHora;
}

// Função para exibir o menu principal do sistema
void exibirMenu() {
    struct EventoCritico *raiz = NULL;

    int opcao, tipoEvento, idRemocao, idBusca, seriedade;
    char regiao[50];
    enum tipoEvento tipo;
    enum status situacao;
    struct tm dataHora;

    do {
        printf("\n+------------------------------------------------------+\n");
        printf("|     Sistema de Gerenciamento de Eventos Criticos     |\n");
        printf("+------------------------------------------------------+\n");
        printf("| 1. Cadastrar Novo Evento Critico                     |\n");
        printf("| 2. Remover Evento Critico                            |\n");
        printf("| 3. Buscar Evento Critico                             |\n");
        printf("| 4. Listar Eventos Ativos por Intervalo de Seriedade  |\n");
        printf("| 5. Listar Eventos por Intervalo de ID                |\n");
        printf("| 6. Alterar Status de um Evento                       |\n");
        printf("| 7. Atualizar Seriedade de um Evento Ativo            |\n");
        printf("| 0. Sair                                              |\n");
        printf("+------------------------------------------------------+\n");
        printf("|-> Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                do {
                    printf("|-> Informe o tipo do evento: \n(1. ACIDENTE_TRANSITO, 2. FALHA_SEMAFORO, 3. INTERRUPCAO_ENERGIA, 4. ALAGAMENTO, 5. INCENDIO): ");
                    scanf("%d", &tipoEvento);                    

                    switch (tipoEvento) {
                        case 1:
                            tipo = ACIDENTE_TRANSITO;
                            break;
                        case 2:
                            tipo = FALHA_SEMAFORO;
                            break;
                        case 3:
                            tipo = INTERRUPCAO_ENERGIA;
                            break;
                        case 4:
                            tipo = ALAGAMENTO;
                            break;
                        case 5:
                            tipo = INCENDIO;
                            break;
                        default:
                            printf("Tipo de evento invalido!\n");
                    }
                } while (tipo < 1 || tipo > 5);

                do {
                    printf("|-> Informe a seriedade do evento (1-5): ");
                    scanf("%d", &seriedade);
                } while (seriedade < 1 || seriedade > 5); 

                printf("|-> Informe a regiao do evento: ");
                scanf("%s", regiao);

                if (regiao == NULL || strlen(regiao) == 0) {
                    printf("Regiao invalida!\n");
                    break;
                }

                raiz = cadastrarEventoCritico(raiz, geraId(), tipo, seriedade, obtemDataHoraAtual(dataHora), regiao, situacao = RESOLVIDO);
                printf("+------------------------------------------------------+\n");
                printf("|        Evento critico cadastrado com sucesso!        |\n");
                printf("+------------------------------------------------------+\n");
                printf("|-> ID do evento: %d\n", raiz->id);

                switch (raiz->tipo) {
                    case ACIDENTE_TRANSITO:
                        printf("|-> Tipo do evento: ACIDENTE_TRANSITO\n");
                        break;
                    case FALHA_SEMAFORO:
                        printf("|-> Tipo do evento: FALHA_SEMAFORO\n");
                        break;
                    case INTERRUPCAO_ENERGIA:
                        printf("|-> Tipo do evento: INTERRUPCAO_ENERGIA\n");
                        break;
                    case ALAGAMENTO:
                        printf("|-> Tipo do evento: ALAGAMENTO\n");
                        break;
                    case INCENDIO:
                        printf("|-> Tipo do evento: INCENDIO\n");
                        break;
                    default:
                        printf("|-> Tipo do evento: DESCONHECIDO\n");
                }

                printf("|-> Seriedade do evento: %d\n", raiz->seriedade);
                printf("|-> Data e hora do evento: %02d/%02d/%04d %02d:%02d:%02d\n", raiz->dataHora.tm_mday, raiz->dataHora.tm_mon + 1, raiz->dataHora.tm_year + 1900, raiz->dataHora.tm_hour, raiz->dataHora.tm_min, raiz->dataHora.tm_sec);
                printf("|-> Regiao do evento: %s\n", raiz->regiao);

                if (raiz->situacao == ATIVO) {
                    printf("|-> Situacao do evento: ATIVO\n");
                } else {
                    printf("|-> Situacao do evento: RESOLVIDO\n");
                }
                break;
            case 2:
                printf("|-> Informe o ID do evento a ser removido: ");
                scanf("%d", &idRemocao);
                removerEventoCritico(raiz, idRemocao);
                printf("+------------------------------------------------------+\n");
                printf("|              Evento removido com sucesso!            |\n");
                printf("+------------------------------------------------------+\n");
                break;
            case 3:
                printf("|-> Informe o ID do evento a ser buscado: ");
                scanf("%d", &idBusca);
                if (buscarEventoCriticoPorID(raiz, idBusca)) {
                    printf("+------------------------------------------------------+\n");
                    printf("|              Evento critico encontrado!              |\n");
                    printf("+------------------------------------------------------+\n");
                    printf("|-> ID do evento: %d\n", raiz->id);

                    switch (raiz->tipo) {
                        case ACIDENTE_TRANSITO:
                            printf("|-> Tipo do evento: ACIDENTE_TRANSITO\n");
                            break;
                        case FALHA_SEMAFORO:
                            printf("|-> Tipo do evento: FALHA_SEMAFORO\n");
                            break;
                        case INTERRUPCAO_ENERGIA:
                            printf("|-> Tipo do evento: INTERRUPCAO_ENERGIA\n");
                            break;
                        case ALAGAMENTO:
                            printf("|-> Tipo do evento: ALAGAMENTO\n");
                            break;
                        case INCENDIO:
                            printf("|-> Tipo do evento: INCENDIO\n");
                            break;
                        default:
                            printf("|-> Tipo do evento: DESCONHECIDO\n");
                    }
                    printf("|-> Seriedade do evento: %d\n", raiz->seriedade);
                    printf("|-> Data e hora do evento: %02d/%02d/%04d %02d:%02d:%02d\n", raiz->dataHora.tm_mday, raiz->dataHora.tm_mon + 1, raiz->dataHora.tm_year + 1900, raiz->dataHora.tm_hour, raiz->dataHora.tm_min, raiz->dataHora.tm_sec);
                    printf("|-> Regiao do evento: %s\n", raiz->regiao);
                    if (raiz->situacao == ATIVO) {
                        printf("|-> Situacao do evento: ATIVO\n");
                    } else {
                        printf("|-> Situacao do evento: RESOLVIDO\n");
                    }
                } else {
                    printf("+------------------------------------------------------+\n");
                    printf("|       Evento critico com ID %d nao encontrado       |\n", idBusca);
                    printf("+------------------------------------------------------+\n");
                }
                break;
            case 4:
                listarEventosAtivosPorSeriedade();
                break;
            case 5:
                listarEventosPorIntervaloDeID();
                break;
            case 6:
                alterarStatusEvento();
                break;
            case 7:
                atualizarSeriedadeEventoAtivo();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente!\n");
        }
    } while (opcao != 0);
}

// Função principal para iniciar o sistema
int main() {
    exibirMenu();
    return 0;
}