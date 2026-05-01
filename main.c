#include <stdio.h>
#include <time.h>

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
struct EventoCritico *criarNO(int id) {
    struct EventoCritico *no = (struct EventoCritico *)malloc(sizeof(struct EventoCritico));
    no->id = id;
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
void cadastrarEventoCritico() {

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

// Função para exibir o menu principal do sistema
void exibirMenu() {
    int opcao;

    do {
        printf("+------------------------------------------------------+\n");
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
                cadastrarEventoCritico();
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