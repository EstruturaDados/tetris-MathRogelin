#include <stdio.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAPACIDADE_FILA 5

/* peça do jogo */
typedef struct {
    char nome; /* 'I', 'O', 'T', 'L' */
    int id;    /* id*/
} Peca;

/* Fila circular de peças */
typedef struct {
    Peca dados[CAPACIDADE_FILA];
    int head;   /* índice do elemento da frente */
    int tail;   /* índice para inserir o próximo elemento */
    int tamanho;/* número atual de elementos */
} FilaPecas;

/* Protótipos */
void inicializarFila(FilaPecas *f);
Peca gerarPeca(void);
int enqueue(FilaPecas *f, Peca p);
int dequeue(FilaPecas *f, Peca *removida);
void imprimirFila(const FilaPecas *f);
void esperarEnter(void);

static int proximoId = 0; /* contador de ids */

/* Inicializa a fila vazia */
void inicializarFila(FilaPecas *f) {
    f->head = 0;
    f->tail = 0;
    f->tamanho = 0;
}

/* Gera uma peça aleatória com id */
Peca gerarPeca(void) {
    const char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = proximoId++;
    return p;
}

/* Insere peça no final da fila. Retorna 1 se sucesso, 0 se cheia. */
int enqueue(FilaPecas *f, Peca p) {
    if (f->tamanho == CAPACIDADE_FILA) {
        return 0; /* fila cheia */
    }
    f->dados[f->tail] = p;
    f->tail = (f->tail + 1) % CAPACIDADE_FILA;
    f->tamanho++;
    return 1;
}

/* Remove peça da frente. Retorna 1 se removida, 0 se vazia. */
int dequeue(FilaPecas *f, Peca *removida) {
    if (f->tamanho == 0) return 0; /* fila vazia */
    if (removida != NULL) {
        *removida = f->dados[f->head];
    }
    f->head = (f->head + 1) % CAPACIDADE_FILA;
    f->tamanho--;
    return 1;
}

/* Imprime o estado atual da fila no formato: [T 0] [O 1] ... */
void imprimirFila(const FilaPecas *f) {
    printf("\nFila de peças\n\n");
    if (f->tamanho == 0) {
        printf("(vazia)\n");
        return;
    }
    int idx = f->head;
    for (int i = 0; i < f->tamanho; ++i) {
        Peca p = f->dados[idx];
        printf("[ %c %d ]", p.nome, p.id);
        if (i < f->tamanho - 1) printf(" ");
        idx = (idx + 1) % CAPACIDADE_FILA;
    }
    printf("\n");
}

/* Pequena pausa aguardando Enter para facilitar leitura */
void esperarEnter(void) {
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n');
}


int main() {

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.

    FilaPecas fila;
    inicializarFila(&fila);

    /* Inicializa gerador aleatório e id */
    srand((unsigned) time(NULL));
    proximoId = 0;

    /* Preenche fila inicial com CAPACIDADE_FILA peças */
    for (int i = 0; i < CAPACIDADE_FILA; ++i) {
        Peca p = gerarPeca();
        enqueue(&fila, p); /* sabemos que cabe */
    }


    return 0;
}

// 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha

