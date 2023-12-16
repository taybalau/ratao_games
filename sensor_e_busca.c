#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **adj;
    int m;
} grafo;

void parseia_sensor(int num, int *frente, int *dir, int *tras, int *esq) {
    *frente = (num >> 0) & 1;
    *dir = (num >> 1) & 1;
    *tras = (num >> 2) & 1;
    *esq = (num >> 3) & 1;
}

void busca_profundidade(grafo *g, int u, int v) {
    printf("c\n");
    fflush(stdout);
    int sensor;
    scanf("%d", &sensor);
    int frente, dir, tras, esq;
    parseia_sensor(sensor, &frente, &dir, &tras, &esq);
    // printf("%d %d %d %d", esq, tras, dir, frente);
    if (frente) {
        busca_profundidade(g, u+1, v+1); // nao sei direito a lógica nessa parte, frente é pra onde vc andaria com o ratinho normalmente sem virar né?? provavelmente vai ter que saber pra onde o rato ta apontando pra corrigir esse u+1 e v+1
    }
    if (dir) {
        busca_profundidade(g, u+1, v+1);
    }
    if (tras) {
        busca_profundidade(g, u+1, v+1);
    }
    if (esq) {
        busca_profundidade(g, u+1, v+1);
    }
}