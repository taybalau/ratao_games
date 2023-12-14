#include <stdio.h>
#include <stdlib.h>

#define MAX_NOS 1000

typedef struct {
    int nos[MAX_NOS][MAX_NOS];
    int num_nos;
} Matriz;

void inicializarMatriz(Matriz* g, int num_nos) {
    g->num_nos = num_nos;
    
    for (int i = 0; i < num_nos; ++i) {
        for (int j = 0; j < num_nos; ++j) {
            g->nos[i][j] = 0; 
        }
    }
}

void adicionarParede(Matriz* g, int no1, int no2) {
    g->nos[no1][no2] = 1; 
    g->nos[no2][no1] = 1; 
}

void girar_para_esquerda() {
    printf("l\n");
    fflush(stdout);
    int _;
    scanf("%d", &_);
}

void girar_para_direita() {
    printf("r\n");
    fflush(stdout);
    int _;
    scanf("%d", &_);
}

int mover_para_frente(Matriz* g, int no_atual) {
    int resultado;
    
    printf("w\n");
    fflush(stdout);
    scanf("%d", &resultado);

    if (resultado == 1) {
        return 1;
    } else if (resultado == 0) {
        adicionarParede(g, no_atual, no_atual + 1); 
    }

    return resultado;
}

void explorar_labirinto(Matriz* g, int no_atual) {
    while (1) {
        int resultado = mover_para_frente(g, no_atual);

        if (resultado == 0) {
            girar_para_esquerda();
        } else if (resultado == 2) {
            break; 
        } else {
            no_atual++;
        }
    }
}