#include <stdio.h>
#include <stdlib.h>

#define MAX_NOS 200

typedef struct {
    int nos[MAX_NOS][MAX_NOS];
    int num_nos;
} Matriz;

typedef struct {
    int **adj;
    int m;
} grafo;

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

void parseia_sensor(int num, int *frente, int *dir, int *tras, int *esq) {
    *frente = (num >> 0) & 1;
    *dir = (num >> 1) & 1;
    *tras = (num >> 2) & 1;
    *esq = (num >> 3) & 1;
}

void busca_profundidade(Matriz *labirinto, int u, int v) {
    printf("c\n");
    fflush(stdout);
    
    int sensor;
    scanf("%d", &sensor);

    int frente, dir, tras, esq;
    parseia_sensor(sensor, &frente, &dir, &tras, &esq);

    if (frente) {
        int proximo_u = u + 1;  
        int proximo_v = v;
        busca_profundidade(labirinto, proximo_u, proximo_v);
    }

    if (dir) {
        int proximo_u = u;  
        int proximo_v = v + 1;
        busca_profundidade(labirinto, proximo_u, proximo_v);
    }

    if (tras) {
        int proximo_u = u - 1;  
        int proximo_v = v;
        busca_profundidade(labirinto, proximo_u, proximo_v);
    }

    if (esq) {
        int proximo_u = u;
        int proximo_v = v - 1;  
        busca_profundidade(labirinto, proximo_u, proximo_v);
    }
}


int mover_para_frente(Matriz* g, int no_atual) {
    int resultado;
    
    printf("w\n");
    fflush(stdout);
    scanf("%d", &resultado);

    if (resultado == 1) {
        return 1;
    } else if (resultado == 0) {
        
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

int main() {
    Matriz labirinto;
    
    explorar_labirinto(&labirinto, 0);

    return 0;
}