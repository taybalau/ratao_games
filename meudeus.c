#include <stdio.h>

typedef struct {
  int **adj;
  int m;
} grafo;

// implementaçao com matriz

grafo * inicializa_grafo(int m) {
  grafo *g = malloc(sizeof(grafo));
  g->m = m;
  g->adj = malloc(m*sizeof(int *));
  for (int i = 0; i < m; i++) {
    g->adj[i] = malloc(m*sizeof(int));
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      g->adj[i][j] = 0;
    }
  }
  return g;
}

// void caminha_frente(grafo *g) {

// }

void rotaciona_horario(grafo *g) {
  printf("r\n");
  fflush(stdout);
  int result;
  scanf("%d", &result);
}

void rotaciona_antihorario(grafo *g) {
  printf("l\n");
  fflush(stdout);
  int result;
  scanf("%d", &result);
}

void parseia_sensor(int num, int *frente, int *dir, int *tras, int *esq) {
    *frente = (num >> 0) & 1;
    *dir = (num >> 1) & 1;
    *tras = (num >> 2) & 1;
    *esq = (num >> 3) & 1;
}


void busca_profundidade(grafo *g, int u, int v) {
  int result, frente = 0, dir = 0, tras = 0, esq = 0;
  printf("c\n");
  fflush(stdout);
  scanf("%d", &result);
  parseia_sensor(result, &frente, &dir, &tras, &esq);
  if (frente && g->adj[u][v+1] == 0) {
    printf("w\n"); // anda pa frente
    fflush(stdout);
    scanf("%d", result);
    g->adj[u][v+1] = 1;
    if (result == 2) { // encontrou o objetivo
      return;
    }
    busca_profundidade(g, u, v+1);
  }
  if (dir && g->adj[u+1][v] == 0) {
    rotaciona_horario(g);
    printf("w\n"); // anda pa frente
    fflush(stdout);
    scanf("%d", result);
    g->adj[u+1][v] = 1;
    if (result == 2) { // encontrou o objetivo
      return;
    }
    busca_profundidade(g, u+1, v);
  }
  if (esq && g->adj[u-1][v] == 0) {
    rotaciona_antihorario(g);
    printf("w\n"); // anda pa frente
    fflush(stdout);
    scanf("%d", result);
    g->adj[u-1][v] = 1;
    if (result == 2) { // encontrou o objetivo
      return;
    }
    // if (frente == dir == esq == 0 && ) {
    //   return;
    // }
    busca_profundidade(g, u-1, v);
  }
  if (tras && g->adj[u][v-1] == 0) {
    rotaciona_antihorario(g);
    rotaciona_antihorario(g);
    printf("w\n"); // anda pa frente
    fflush(stdout);
    scanf("%d", result);
    g->adj[u][v-1] = 1;
    if (result == 2) { // encontrou o objetivo
      return;
    }
    busca_profundidade(g, u, v-1);
  }
  else if (g->adj[u][v+1] == 1) {
    return;
  }
}

int main() {
  grafo *g = inicializa_grafo(29);
  g->adj[14][14] = 1; // posiçao que o rato começa
  // printf("%d\n", g->adj[0][0]);
  // printf("%d\n", g->adj[0][1]);
  busca_profundidade(g, 14, 14);
}