#include <stdio.h>

typedef struct {
  int **adj;
  int m;
} grafo;

typedef struct {
  int x;
  int y;
  int vizinhos[4]; // posiçoes 0 1 2 e 3 para respectivamente vizinhos do norte, oeste, sul e leste (binário)
  int direcao; // 0 1 2 ou 3 para dizer se o rato tá apontando pro norte, oeste..
} stackRato;

// stackRato *s = malloc(225 * sizeof(stackRato));
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

void rotaciona_horario(grafo *g, int *direcao) {
  printf("r\n");
  fflush(stdout);
  int result;
  scanf("%d", &result);
  *direcao = (*direcao+1 % 4 + 4) % 4;
}

void rotaciona_antihorario(grafo *g, int *direcao) {
  printf("l\n");
  fflush(stdout);
  int result;
  scanf("%d", &result);
  *direcao = (*direcao-1 % 4 + 4) % 4;
}

void parseia_sensor(int num, int *frente, int *dir, int *tras, int *esq) {
    *frente = (num >> 0) & 1;
    *dir = (num >> 1) & 1;
    *tras = (num >> 2) & 1;
    *esq = (num >> 3) & 1;

}

// void salva_sensor_parseado()


void busca_profundidade(grafo *g, int u, int v, int direcao) {
  int result, frente = 0, dir = 0, tras = 0, esq = 0;
  printf("c\n");
  fflush(stdout);
  scanf("%d", &result);
  parseia_sensor(result, &frente, &dir, &tras, &esq);
  if (frente) {
    if (direcao == 0) {
      if (g->adj[u-1][v] == 0) {
        printf("w\n"); // anda pa frente
        fflush(stdout);
        scanf("%d", &result);
        g->adj[u-1][v] = 1; // visita a coordenada
        s[++stackPointer].vizinhos[0] = frente;
        s[stackPointer].vizinhos[1] = dir;
        s[stackPointer].vizinhos[2] = tras;
        s[stackPointer].vizinhos[3] = esq;
        s[stackPointer].x = u-1;
        s[stackPointer].y = v;
        s[stackPointer].direcao = direcao;
        if (result == 2) { // encontrou o objetivo
          return;
        }
        busca_profundidade(g, u-1, v, direcao); // norte
      }
      else {
        return;
      }
    }
    else if (direcao == 1) {
      if (g->adj[u][v+1] == 0) {
        printf("w\n"); // anda pa frente
        fflush(stdout);
        scanf("%d", &result);
        g->adj[u][v+1] = 1; // virado pro leste
        s[++stackPointer].vizinhos[0] = frente;
        s[stackPointer].vizinhos[1] = dir;
        s[stackPointer].vizinhos[2] = tras;
        s[stackPointer].vizinhos[3] = esq;
        s[stackPointer].x = u;
        s[stackPointer].y = v+1;
        s[stackPointer].direcao = direcao;
        if (result == 2) { // encontrou o objetivo
          return;
        }
        busca_profundidade(g, u, v+1, direcao); // leste
      }
      else {
        return;
      }
    }
    else if (direcao == 2) {
      if (g->adj[u+1][v] == 0) {
        printf("w\n"); // anda pa frente
        fflush(stdout);
        scanf("%d", &result);
        g->adj[u+1][v] = 1; // virado pro sul
        s[++stackPointer].vizinhos[0] = frente;
        s[stackPointer].vizinhos[1] = dir;
        s[stackPointer].vizinhos[2] = tras;
        s[stackPointer].vizinhos[3] = esq;
        s[stackPointer].x = u+1;
        s[stackPointer].y = v;
        s[stackPointer].direcao = direcao;
        if (result == 2) { // encontrou o objetivo
          return;
        }
        busca_profundidade(g, u+1, v, direcao); // sul
      }
      else {
        return;
      }
    }
    else if (direcao == 3) {
      if (g->adj[u][v-1] == 0) {
        printf("w\n"); // anda pa frente
        fflush(stdout);
        scanf("%d", &result);
        g->adj[u][v-1] = 1; // virado pro oeste
        s[++stackPointer].vizinhos[0] = frente;
        s[stackPointer].vizinhos[1] = dir;
        s[stackPointer].vizinhos[2] = tras;
        s[stackPointer].vizinhos[3] = esq;
        s[stackPointer].x = u;
        s[stackPointer].y = v-1;
        s[stackPointer].direcao = direcao;
        if (result == 2) { // encontrou o objetivo
          return;
        }
        busca_profundidade(g, u, v-1, direcao); // oeste
      }
      else {
        return;
      }
    }
    return;
  }
  if (dir) {
    if (direcao == 0) {
      if (g->adj[u-1][v] == 0) {
        rotaciona_horario(g, &direcao);
        printf("w\n"); // anda pa frente
        fflush(stdout);
        scanf("%d", &result);
        g->adj[u-1][v] = 1; // visita a coordenada
        if (result == 2) { // encontrou o objetivo
          return;
        }
        busca_profundidade(g, u-1, v, direcao); // norte
      }
      else {
        return;
      }
    }
    else if (direcao == 1) {
      if (g->adj[u][v+1] == 0) {
        rotaciona_horario(g, &direcao);
        printf("w\n"); // anda pa frente
        fflush(stdout);
        scanf("%d", &result);
        g->adj[u][v+1] = 1; // virado pro leste
        if (result == 2) { // encontrou o objetivo
          return;
        }
        busca_profundidade(g, u, v+1, direcao); // leste
      }
      else {
        return;
      }
    }
    else if (direcao == 2) {
      if (g->adj[u+1][v] == 0) {
        rotaciona_horario(g, &direcao);
        printf("w\n"); // anda pa frente
        fflush(stdout);
        scanf("%d", &result);
        g->adj[u+1][v] = 1; // virado pro sul
        if (result == 2) { // encontrou o objetivo
          return;
        }
        busca_profundidade(g, u+1, v, direcao); // sul
      }
      else {
        return;
      }
    }
    else if (direcao == 3) {
      if (g->adj[u][v-1] == 0) {
        rotaciona_horario(g, &direcao);
        printf("w\n"); // anda pa frente
        fflush(stdout);
        scanf("%d", &result);
        g->adj[u][v-1] = 1; // virado pro oeste
        if (result == 2) { // encontrou o objetivo
          return;
        }
        busca_profundidade(g, u, v-1, direcao); // oeste
      }
      else {
        return;
      }
    }
    return;
  }
  if (esq) {
    if (direcao == 0) {
      if (g->adj[u-1][v] == 0) {
        rotaciona_antihorario(g, &direcao);
        printf("w\n"); // anda pa frente
        fflush(stdout);
        scanf("%d", &result);
        g->adj[u-1][v] = 1; // visita a coordenada
        if (result == 2) { // encontrou o objetivo
          return;
        }
        busca_profundidade(g, u-1, v, direcao); // norte
      }
      else {
        return;
      }
    }
    else if (direcao == 1) {
      if (g->adj[u][v+1] == 0) {
        rotaciona_antihorario(g, &direcao);
        printf("w\n"); // anda pa frente
        fflush(stdout);
        scanf("%d", &result);
        g->adj[u][v+1] = 1; // virado pro leste
        if (result == 2) { // encontrou o objetivo
          return;
        }
        busca_profundidade(g, u, v+1, direcao); // leste
      }
      else {
        return;
      }
    }
    else if (direcao == 2) {
      if (g->adj[u+1][v] == 0) {
        rotaciona_antihorario(g, &direcao);
        printf("w\n"); // anda pa frente
        fflush(stdout);
        scanf("%d", &result);
        g->adj[u+1][v] = 1; // virado pro sul
        if (result == 2) { // encontrou o objetivo
          return;
        }
        busca_profundidade(g, u+1, v, direcao); // sul
      }
      else {
        return;
      }
    }
    else if (direcao == 3) {
      if (g->adj[u][v-1] == 0) {
        rotaciona_antihorario(g, &direcao);
        printf("w\n"); // anda pa frente
        fflush(stdout);
        scanf("%d", &result);
        g->adj[u][v-1] = 1; // virado pro oeste
        if (result == 2) { // encontrou o objetivo
          return;
        }
        busca_profundidade(g, u, v-1, direcao); // oeste
      }
      else {
        return;
      }
    }
    return;
  }

  if (tras) {
    if (direcao == 0) {
      if (g->adj[u-1][v] == 0) {
        rotaciona_antihorario(g, &direcao);
        rotaciona_antihorario(g, &direcao);
        printf("w\n"); // anda pa frente
        fflush(stdout);
        scanf("%d", &result);
        g->adj[u-1][v] = 1; // visita a coordenada
        if (result == 2) { // encontrou o objetivo
          return;
        }
        busca_profundidade(g, u-1, v, direcao); // norte
      }
      else {
        return;
      }
    }
    else if (direcao == 1) {
      if (g->adj[u][v+1] == 0) {
        rotaciona_antihorario(g, &direcao);
        rotaciona_antihorario(g, &direcao);
        printf("w\n"); // anda pa frente
        fflush(stdout);
        scanf("%d", &result);
        g->adj[u][v+1] = 1; // virado pro leste
        if (result == 2) { // encontrou o objetivo
          return;
        }
        busca_profundidade(g, u, v+1, direcao); // leste
      }
      else {
        return;
      }
    }
    else if (direcao == 2) {
      if (g->adj[u+1][v] == 0) {
        rotaciona_antihorario(g, &direcao);
        rotaciona_antihorario(g, &direcao);
        printf("w\n"); // anda pa frente
        fflush(stdout);
        scanf("%d", &result);
        g->adj[u+1][v] = 1; // virado pro sul
        if (result == 2) { // encontrou o objetivo
          return;
        }
        busca_profundidade(g, u+1, v, direcao); // sul
      }
      else {
        return;
      }
    }
    else if (direcao == 3) {
      if (g->adj[u][v-1] == 0) {
        rotaciona_antihorario(g, &direcao);
        rotaciona_antihorario(g, &direcao);
        printf("w\n"); // anda pa frente
        fflush(stdout);
        scanf("%d", &result);
        g->adj[u][v-1] = 1; // virado pro oeste
        if (result == 2) { // encontrou o objetivo
          return;
        }
        busca_profundidade(g, u, v-1, direcao); // oeste
      }
      else {
        return;
      }
    }
    return;
  }
}

stackRato s[225];
int stackPointer = -1;

int main() {
  // coords *c = malloc(sizeof)
  grafo *g = inicializa_grafo(29);
  g->adj[14][14] = 1; // posiçao que o rato começa
  // printf("%d\n", g->adj[0][0]);
  // printf("%d\n", g->adj[0][1]);
  busca_profundidade(g, 14, 14, 0);
}