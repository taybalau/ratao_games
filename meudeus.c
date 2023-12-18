#include <stdio.h>

typedef struct {
  int **adj;
  int m;
} grafo;

// typedef struct {
//   int x;
//   int y;
// } coords;



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

void rotaciona_horario(grafo *g, int direcao) {
  printf("r\n");
  fflush(stdout);
  int result;
  scanf("%d", &result);
  direcao = (direcao++ % 4 + 4) % 4;
}

void rotaciona_antihorario(grafo *g, int direcao) {
  printf("l\n");
  fflush(stdout);
  int result;
  scanf("%d", &result);
  direcao = (direcao-- % 4 + 4) % 4;
}

void parseia_sensor(int num, int *frente, int *dir, int *tras, int *esq) {
    *frente = (num >> 0) & 1;
    *dir = (num >> 1) & 1;
    *tras = (num >> 2) & 1;
    *esq = (num >> 3) & 1;
}


void busca_profundidade(grafo *g, int u, int v, int direcao) {
  int result, frente = 0, dir = 0, tras = 0, esq = 0;
  printf("c\n");
  fflush(stdout);
  scanf("%d", &result);
  parseia_sensor(result, &frente, &dir, &tras, &esq);
  if (frente && g->adj[u][v+1] == 0) {
    printf("w\n"); // anda pa frente
    fflush(stdout);
    scanf("%d", &result);
    if (result == 2) { // encontrou o objetivo
      return;
    }
    switch (direcao) { // marca exatamente a coord pra onde ele navegou
      case 0:
        if (g->adj[u-1][v] == 0) {
          g->adj[u-1][v] = 1; // virado pro norte
        }
        else {
          return;
        }
      case 1:
        if (g->adj[u][v+1] == 0) {
          g->adj[u][v+1] = 1; // virado pro leste
        }
        else {
          return;
        }
      case 2:
        if (g->adj[u+1][v] == 0) {
          g->adj[u+1][v] = 1; // virado pro sul
        }
        else {
          return;
        }
      case 3:
        if (g->adj[u][v-1] == 0) {
          g->adj[u][v-1] = 1; // virado pro oeste
        }
        else {
          return;
        } 
    }
    switch (direcao) { // faz a busca e mantém rastreio da direçao
      case 0:
        busca_profundidade(g, u-1, v, direcao); // norte
      case 1:
        busca_profundidade(g, u, v+1, direcao); // leste
      case 2:
        busca_profundidade(g, u+1, v, direcao); // sul
      case 3:
        busca_profundidade(g, u, v-1, direcao); // oeste
    }
  }
  if (dir && g->adj[u+1][v] == 0) {
    rotaciona_horario(g, &direcao);
    printf("w\n"); // anda pa frente
    fflush(stdout);
    scanf("%d", &result);
    if (result == 2) { // encontrou o objetivo
      return;
    }
    switch (direcao) { // marca exatamente a coord pra onde ele navegou
      case 0:
        if (g->adj[u-1][v] == 0) {
          g->adj[u-1][v] = 1; // virado pro norte
        }
        else {
          return;
        }
      case 1:
        if (g->adj[u][v+1] == 0) {
          g->adj[u][v+1] = 1; // virado pro leste
        }
        else {
          return;
        }
      case 2:
        if (g->adj[u+1][v] == 0) {
          g->adj[u+1][v] = 1; // virado pro sul
        }
        else {
          return;
        }
      case 3:
        if (g->adj[u][v-1] == 0) {
          g->adj[u][v-1] = 1; // virado pro oeste
        }
        else {
          return;
        } 
    }
    switch (direcao) { // faz a busca e mantém rastreio da direçao
      case 0:
        busca_profundidade(g, u-1, v, direcao); // norte
      case 1:
        busca_profundidade(g, u, v+1, direcao); // leste
      case 2:
        busca_profundidade(g, u+1, v, direcao); // sul
      case 3:
        busca_profundidade(g, u, v-1, direcao); // oeste
    }
  }
  if (esq && g->adj[u-1][v] == 0) {
    rotaciona_antihorario(g, direcao);
    printf("w\n"); // anda pa frente
    fflush(stdout);
    scanf("%d", &result);
    if (result == 2) { // encontrou o objetivo
      return;
    }
    switch (direcao) { // marca exatamente a coord pra onde ele navegou
      case 0:
        if (g->adj[u-1][v] == 0) {
          g->adj[u-1][v] = 1; // virado pro norte
        }
        else {
          return;
        }
      case 1:
        if (g->adj[u][v+1] == 0) {
          g->adj[u][v+1] = 1; // virado pro leste
        }
        else {
          return;
        }
      case 2:
        if (g->adj[u+1][v] == 0) {
          g->adj[u+1][v] = 1; // virado pro sul
        }
        else {
          return;
        }
      case 3:
        if (g->adj[u][v-1] == 0) {
          g->adj[u][v-1] = 1; // virado pro oeste
        }
        else {
          return;
        } 
    }
    switch (direcao) { // faz a busca e mantém rastreio da direçao
      case 0:
        busca_profundidade(g, u-1, v, direcao); // norte
      case 1:
        busca_profundidade(g, u, v+1, direcao); // leste
      case 2:
        busca_profundidade(g, u+1, v, direcao); // sul
      case 3:
        busca_profundidade(g, u, v-1, direcao); // oeste
    }
  }
  if (tras && g->adj[u][v-1] == 0) {
    rotaciona_antihorario(g, direcao);
    rotaciona_antihorario(g, direcao);
    printf("w\n"); // anda pa frente
    fflush(stdout);
    scanf("%d", &result);
    if (result == 2) { // encontrou o objetivo
      return;
    }
    switch (direcao) { // marca exatamente a coord pra onde ele navegou
      case 0:
        if (g->adj[u-1][v] == 0) {
          g->adj[u-1][v] = 1; // virado pro norte
        }
        else {
          return;
        }
      case 1:
        if (g->adj[u][v+1] == 0) {
          g->adj[u][v+1] = 1; // virado pro leste
        }
        else {
          return;
        }
      case 2:
        if (g->adj[u+1][v] == 0) {
          g->adj[u+1][v] = 1; // virado pro sul
        }
        else {
          return;
        }
      case 3:
        if (g->adj[u][v-1] == 0) {
          g->adj[u][v-1] = 1; // virado pro oeste
        }
        else {
          return;
        } 
    }
    switch (direcao) { // faz a busca e mantém rastreio da direçao
      case 0:
        busca_profundidade(g, u-1, v, direcao); // norte
      case 1:
        busca_profundidade(g, u, v+1, direcao); // leste
      case 2:
        busca_profundidade(g, u+1, v, direcao); // sul
      case 3:
        busca_profundidade(g, u, v-1, direcao); // oeste
    }
  }
  // else if (g->adj[u][v+1] == 1) {
  //   return;
  // }
}

int main() {
  // coords *c = malloc(sizeof)
  grafo *g = inicializa_grafo(29);
  g->adj[14][14] = 1; // posiçao que o rato começa
  // printf("%d\n", g->adj[0][0]);
  // printf("%d\n", g->adj[0][1]);
  busca_profundidade(g, 14, 14, 0);
}