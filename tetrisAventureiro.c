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
    *removida = f->dados[f->head];
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
    *removida = p->dados[p->topo--];
    return 1;
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

void esperarEnter(void) {
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n');
}

