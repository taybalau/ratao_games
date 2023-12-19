#include <stdio.h>

typedef struct {
  int x;
  int y;
  int vizinhos[4]; // posiçoes 0 1 2 e 3 para respectivamente vizinhos do norte, oeste, sul e leste (binário)
  int direcao; // 0 1 2 ou 3 para dizer se o rato tá apontando pro norte, oeste..
} stackRato;

stackRato s[225];

int main() {
  s[0].x = 1;
  printf("%d", s[0].x);
}