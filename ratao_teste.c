#include <stdio.h>
#include <stdbool.h>

#define TAMANHO_MATRIZ 200

int labirinto[TAMANHO_MATRIZ][TAMANHO_MATRIZ] = {0};
int posicaoX = TAMANHO_MATRIZ / 2;
int posicaoY = TAMANHO_MATRIZ / 2;

typedef struct {
    int x;
    int y;
} Coordenada;

bool ehValida(int x, int y) {
    return x >= 0 && x < TAMANHO_MATRIZ && y >= 0 && y < TAMANHO_MATRIZ;
}

bool foiVisitada(int x, int y) {
    return labirinto[x][y] == 2;
}

void marcarVisitada(int x, int y) {
    labirinto[x][y] = 2;
}

void girarEsquerda() {
    printf("l\n");
    fflush(stdout);
    int resultado;
    scanf("%d", &resultado);
}

void girarDireita() {
    printf("r\n");
    fflush(stdout);
    int resultado;
    scanf("%d", &resultado);
}

int moverFrente() {
    printf("w\n");
    fflush(stdout);
    int resultado;
    scanf("%d", &resultado);
    return resultado;
}

bool dfs(int x, int y) {
    if (!ehValida(x, y) || foiVisitada(x, y)) {
        return false;
    }

    marcarVisitada(x, y);

    if (moverFrente() != 0) {
        return true; 
    }

    girarEsquerda();
    if (dfs(x, y + 1)) return true;

    girarDireita();
    if (dfs(x, y - 1)) return true;

    girarDireita();
    girarDireita();
    moverFrente();

    return false;
}

int main() {
    dfs(posicaoX, posicaoY);

    return 0;
}