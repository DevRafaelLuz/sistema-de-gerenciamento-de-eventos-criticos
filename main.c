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

// Função para remover um evento crítico
void removerEventoCritico() {

}

// Função para buscar um evento crítico por ID
void buscarEventoCritico() {

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

struct tm obtemDataHoraAtual() {
    EventoCritico ec;
    time_t t = time(NULL);
    ec.dataHora = *localtime(&t);
    return ec.dataHora;
}

// Função para exibir o menu principal do sistema
void exibirMenu() {
    struct EventoCritico *raiz = NULL;
    EventoCritico ec;   

    int opcao, tipoEvento;

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
                            ec.tipo = ACIDENTE_TRANSITO;
                            break;
                        case 2:
                            ec.tipo = FALHA_SEMAFORO;
                            break;
                        case 3:
                            ec.tipo = INTERRUPCAO_ENERGIA;
                            break;
                        case 4:
                            ec.tipo = ALAGAMENTO;
                            break;
                        case 5:
                            ec.tipo = INCENDIO;
                            break;
                        default:
                            printf("Tipo de evento invalido!\n");
                    }
                } while (ec.tipo < 1 || ec.tipo > 5);

                do {
                    printf("|-> Informe a seriedade do evento (1-5): ");
                    scanf("%d", &ec.seriedade);
                } while (ec.seriedade < 1 || ec.seriedade > 5); 

                printf("|-> Informe a regiao do evento: ");
                scanf("%s", ec.regiao);

                if (ec.regiao == NULL || strlen(ec.regiao) == 0) {
                    printf("Regiao invalida!\n");
                    break;
                }

                cadastrarEventoCritico(raiz, ec.id = geraId(), ec.tipo, ec.seriedade, ec.dataHora = obtemDataHoraAtual(), ec.regiao, ec.situacao = ATIVO);
                printf("+------------------------------------------------------+\n");
                printf("|        Evento critico cadastrado com sucesso!        |\n");
                printf("+------------------------------------------------------+\n");
                printf("|-> ID do evento: %d\n", ec.id);

                switch (ec.tipo) {
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

                printf("|-> Seriedade do evento: %d\n", ec.seriedade);
                printf("|-> Data e hora do evento: %02d/%02d/%04d %02d:%02d:%02d\n", ec.dataHora.tm_mday, ec.dataHora.tm_mon + 1, ec.dataHora.tm_year + 1900, ec.dataHora.tm_hour, ec.dataHora.tm_min, ec.dataHora.tm_sec);
                printf("|-> Regiao do evento: %s\n", ec.regiao);

                if (ec.situacao == ATIVO) {
                    printf("|-> Situacao do evento: ATIVO\n");
                } else {
                    printf("|-> Situacao do evento: RESOLVIDO\n");
                }
                break;
            case 2:
                removerEventoCritico();
                break;
            case 3:
                buscarEventoCritico();
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