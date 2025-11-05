#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILAS 5 // Tamanho máximo da fila de peças

// Estrutura que representa uma peça
typedef struct {
    char nome; // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;    // Identificador único
} Peca;

// Estrutura que representa a fila circular de peças
typedef struct {
    Peca fila[MAX_FILAS];
    int frente;
    int tras;
    int tamanho;
} Fila;

// Função que gera uma peça aleatória
Peca gerarPeca(int id) {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

// Inicializa a fila com um número fixo de peças
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = 0;
    f->tamanho = 0;
    for (int i = 0; i < MAX_FILAS; i++) {
        f->fila[i] = gerarPeca(i);
        f->tras = (f->tras + 1) % MAX_FILAS;
        f->tamanho++;
    }
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->tamanho == MAX_FILAS;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

// Adiciona uma peça ao final da fila
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia! Não é possível adicionar nova peça.\n");
        return;
    }
    f->fila[f->tras] = p;
    f->tras = (f->tras + 1) % MAX_FILAS;
    f->tamanho++;
}

// Remove a peça da frente da fila
Peca dequeue(Fila *f) {
    Peca removida = {'X', -1}; // Valor padrão para caso de fila vazia
    if (filaVazia(f)) {
        printf("Fila vazia! Não há peça para jogar.\n");
        return removida;
    }
    removida = f->fila[f->frente];
    f->frente = (f->frente + 1) % MAX_FILAS;
    f->tamanho--;
    return removida;
}

// Exibe o estado atual da fila
void exibirFila(Fila *f) {
    printf("Fila de peças:\n");
    int i = f->frente;
    for (int count = 0; count < f->tamanho; count++) {
        printf("[%c %d] ", f->fila[i].nome, f->fila[i].id);
        i = (i + 1) % MAX_FILAS;
    }
    printf("\n\n");
}

int main() {
    Fila fila;
    int idContador = MAX_FILAS; // Para gerar ids únicos para novas peças
    int opcao;

    srand(time(NULL)); // Inicializa gerador de números aleatórios

    inicializarFila(&fila);
    exibirFila(&fila);

    do {
        printf("Opções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca p = dequeue(&fila);
                if (p.id != -1)
                    printf("Você jogou a peça [%c %d]\n", p.nome, p.id);
                exibirFila(&fila);
                break;
            }
            case 2: {
                Peca nova = gerarPeca(idContador++);
                enqueue(&fila, nova);
                printf("Nova peça [%c %d] adicionada à fila.\n", nova.nome, nova.id);
                exibirFila(&fila);
                break;
            }
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}


