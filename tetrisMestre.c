#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAPACIDADE_FILA 5
#define CAPACIDADE_PILHA 3

/* ===================== ESTRUTURAS ===================== */

/* Peça do jogo */
typedef struct {
    char nome; /* 'I', 'O', 'T', 'L' */
    int id;    /* identificador único */
} Peca;

/* Fila circular de peças futuras */
typedef struct {
    Peca dados[CAPACIDADE_FILA];
    int head;   /* índice do primeiro elemento */
    int tail;   /* índice de inserção */
    int tamanho;
} FilaPecas;

/* Pilha linear de peças reservadas */
typedef struct {
    Peca dados[CAPACIDADE_PILHA];
    int topo;
} PilhaReserva;

/* ===================== PROTÓTIPOS ===================== */
void inicializarFila(FilaPecas *f);
void inicializarPilha(PilhaReserva *p);
Peca gerarPeca(void);
int enqueue(FilaPecas *f, Peca p);
int dequeue(FilaPecas *f, Peca *removida);
int push(PilhaReserva *p, Peca x);
int pop(PilhaReserva *p, Peca *removida);
void imprimirFila(const FilaPecas *f);
void imprimirPilha(const PilhaReserva *p);
void esperarEnter(void);
void trocarFrenteComTopo(FilaPecas *f, PilhaReserva *p);
void trocarTresPrimeiros(FilaPecas *f, PilhaReserva *p);

/* ===================== VARIÁVEL GLOBAL ===================== */
static int proximoId = 0;

/* ===================== FUNÇÕES ===================== */

void inicializarFila(FilaPecas *f) {
    f->head = 0;
    f->tail = 0;
    f->tamanho = 0;
}

void inicializarPilha(PilhaReserva *p) {
    p->topo = -1;
}

/* Gera peça aleatória */
Peca gerarPeca(void) {
    const char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = proximoId++;
    return p;
}

/* Enfileira (inserir no fim) */
int enqueue(FilaPecas *f, Peca p) {
    if (f->tamanho == CAPACIDADE_FILA) return 0;
    f->dados[f->tail] = p;
    f->tail = (f->tail + 1) % CAPACIDADE_FILA;
    f->tamanho++;
    return 1;
}

/* Desenfileira (remover da frente) */
int dequeue(FilaPecas *f, Peca *removida) {
    if (f->tamanho == 0) return 0;
    if (removida != NULL) *removida = f->dados[f->head];
    f->head = (f->head + 1) % CAPACIDADE_FILA;
    f->tamanho--;
    return 1;
}

/* Empilhar */
int push(PilhaReserva *p, Peca x) {
    if (p->topo == CAPACIDADE_PILHA - 1) return 0;
    p->dados[++p->topo] = x;
    return 1;
}

/* Desempilhar */
int pop(PilhaReserva *p, Peca *removida) {
    if (p->topo == -1) return 0;
    if (removida != NULL) *removida = p->dados[p->topo--];
    return 1;
}

/* Troca direta: peça da frente da fila <-> topo da pilha.
   Valida se ambos existem antes de trocar. */
void trocarFrenteComTopo(FilaPecas *f, PilhaReserva *p) {
    if (f->tamanho == 0) {
        printf("\nOperação inválida: fila vazia.\n");
        return;
    }
    if (p->topo == -1) {
        printf("\nOperação inválida: pilha vazia.\n");
        return;
    }
    int idxFila = f->head;
    int idxPilha = p->topo;
    Peca temp = f->dados[idxFila];
    f->dados[idxFila] = p->dados[idxPilha];
    p->dados[idxPilha] = temp;
    printf("\nTroca realizada entre frente da fila e topo da pilha.\n");
}

/* Troca em bloco: os 3 primeiros da fila <-> as 3 peças da pilha.
   Garante que fila tenha pelo menos 3 e pilha exatamente (>=3) peças.
   Faz swaps mantendo a ordem do topo da pilha correspondendo ao primeiro da fila:
   Para i=0..2: fila[i] <-> pilha[topo - i] */
void trocarTresPrimeiros(FilaPecas *f, PilhaReserva *p) {
    if (f->tamanho < 3) {
        printf("\nOperação inválida: a fila precisa ter pelo menos 3 peças (atualmente %d).\n", f->tamanho);
        return;
    }
    if (p->topo < 2) {
        printf("\nOperação inválida: a pilha precisa ter pelo menos 3 peças (atualmente %d).\n", p->topo + 1);
        return;
    }
    for (int i = 0; i < 3; ++i) {
        int idxFila = (f->head + i) % CAPACIDADE_FILA;
        int idxPilha = p->topo - i;
        Peca temp = f->dados[idxFila];
        f->dados[idxFila] = p->dados[idxPilha];
        p->dados[idxPilha] = temp;
    }
    printf("\nTroca realizada entre os 3 primeiros da fila e as 3 peças da pilha.\n");
}

/* Impressões */
void imprimirFila(const FilaPecas *f) {
    printf("\nFila de peças:\n");
    if (f->tamanho == 0) {
        printf("(vazia)\n");
        return;
    }
    int idx = f->head;
    for (int i = 0; i < f->tamanho; ++i) {
        Peca p = f->dados[idx];
        printf("[ %c %d ] ", p.nome, p.id);
        idx = (idx + 1) % CAPACIDADE_FILA;
    }
    printf("\n");
}

void imprimirPilha(const PilhaReserva *p) {
    printf("\nPilha de reserva (Topo -> Base):\n");
    if (p->topo == -1) {
        printf("(vazia)\n");
        return;
    }
    for (int i = p->topo; i >= 0; --i) {
        printf("[ %c %d ] ", p->dados[i].nome, p->dados[i].id);
    }
    printf("\n");
}

/* Pausa para o usuário ler a saída */
void esperarEnter(void) {
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n');
}

/* ===================== PROGRAMA PRINCIPAL ===================== */

int main() {
    srand((unsigned) time(NULL));
    FilaPecas fila;
    PilhaReserva pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    proximoId = 0;

    /* Preenche fila inicial com CAPACIDADE_FILA peças */
    for (int i = 0; i < CAPACIDADE_FILA; ++i) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;
    do {
        printf("\n================ ESTADO ATUAL ================\n");
        imprimirFila(&fila);
        imprimirPilha(&pilha);
        printf("\n==============================================\n");

        printf("Opções de ação:\n");
        printf("1 - Jogar peça (remover da frente da fila)\n");
        printf("2 - Enviar peça da fila para a pilha de reserva\n");
        printf("3 - Usar peça da pilha de reserva (remover topo)\n");
        printf("4 - Trocar peça da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 peças da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
            int c; while ((c = getchar()) != '\n' && c != EOF);
            printf("Entrada inválida.\n");
            continue;
        }

        int c; while ((c = getchar()) != '\n' && c != EOF);

        if (opcao == 1) {
            /* Jogar peça: remove da frente e gera nova para manter fila cheia */
            Peca jogada;
            if (dequeue(&fila, &jogada)) {
                printf("\nPeça jogada: [ %c %d ]\n", jogada.nome, jogada.id);
                enqueue(&fila, gerarPeca()); /* repõe automaticamente */
            } else {
                printf("\nFila vazia.\n");
            }
        } 
        else if (opcao == 2) {
            /* Reservar peça: mover da fila para pilha, se houver espaço.
               Após retirar da fila, repõe com gerarPeca(). */
            if (pilha.topo == CAPACIDADE_PILHA - 1) {
                printf("\nPilha cheia. Não é possível reservar.\n");
            } else {
                Peca p;
                if (dequeue(&fila, &p)) {
                    if (push(&pilha, p)) {
                        printf("\nPeça %c %d movida para reserva.\n", p.nome, p.id);
                    } else {
                        /* push falhou por segurança (não deveria ocorrer) */
                        printf("\nErro ao empilhar a peça.\n");
                    }
                    enqueue(&fila, gerarPeca()); /* repõe automaticamente */
                } else {
                    printf("\nFila vazia.\n");
                }
            }
        } 
        else if (opcao == 3) {
            /* Usar peça reservada: desempilha (não volta para o jogo) */
            Peca usada;
            if (pop(&pilha, &usada)) {
                printf("\nPeça da reserva usada: [ %c %d ]\n", usada.nome, usada.id);
            } else {
                printf("\nPilha vazia. Nenhuma peça para usar.\n");
            }
        } 
        else if (opcao == 4) {
            /* Troca direta entre frente da fila e topo da pilha */
            trocarFrenteComTopo(&fila, &pilha);
        }
        else if (opcao == 5) {
            /* Troca em bloco (3 primeiros da fila <-> 3 da pilha) */
            trocarTresPrimeiros(&fila, &pilha);
        }
        else if (opcao == 0) {
            printf("\nSaindo...\n");
        } 
        else {
            printf("\nOpção inválida.\n");
        }

        esperarEnter();

    } while (opcao != 0);

    return 0;
}
