#include <stdio.h>

void rotaciona_antihorario(int *direcao) {
  *direcao = (*direcao-1 % 4 + 4) % 4;
}


int main() {
  int i = 12;
  rotaciona_antihorario(&i);
  printf("%d", i);
}