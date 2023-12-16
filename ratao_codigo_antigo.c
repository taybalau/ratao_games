#include <stdio.h>
#include <stdbool.h>
#define MATRIX_SIZE 500
int labirinto[MATRIX_SIZE][MATRIX_SIZE] = {0};
int roboX = MATRIX_SIZE / 2; // Posição inicial do robô no centro do labirinto
int roboY = MATRIX_SIZE / 2;
typedef struct {
    int x;
    int y;
} Coordenada;
Coordenada coordenadasParedes[MATRIX_SIZE * MATRIX_SIZE];
Coordenada coordenadasCaminho[MATRIX_SIZE * MATRIX_SIZE];
int numParedes = 0;
int numCaminhos = 0;
void adicionarCoordenadaParede(int x, int y) {
    Coordenada coordenada = {x, y};
    coordenadasParedes[numParedes] = coordenada;
    numParedes++;
}
void adicionarCoordenadaCaminho(int x, int y) {
    Coordenada coordenada = {x, y};
    coordenadasCaminho[numCaminhos] = coordenada;
    numCaminhos++;
}
bool paredeVisitada(int x, int y) {
    for (int i = 0; i < numParedes; i++) {
        if (coordenadasParedes[i].x == x && coordenadasParedes[i].y == y) {
            return true;
        }
    }
    return false;
}
bool caminhoVisitado(int x, int y) {
    for (int i = 0; i < numCaminhos; i++) {
        if (coordenadasCaminho[i].x == x && coordenadasCaminho[i].y == y) {
            return true;
        }
    }
    return false;
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
    printf("m\n");
    fflush(stdout);
    int resultado;
    scanf("%d", &resultado);
    return resultado;
}
int main() {
    int paredeX, paredeY;
    int direcaoParede = 0; 
    bool encontrouObjetivo = false;
    adicionarCoordenadaCaminho(250, 250);
    
    while (!encontrouObjetivo) {
        int proximoX = roboX, proximoY = roboY;
        printf("Caminho atual: %d, %d\n", proximoX, proximoY);
        
        if (direcaoParede == 0) {
            proximoX++;
        } else if (direcaoParede == 1 || direcaoParede == -3 ) { 
            proximoY--;
        } else if (direcaoParede == 2 ) {
            proximoX--;
        } else if (direcaoParede == 3 || direcaoParede == -1 ) {
            proximoY++;
        } 
        if (paredeVisitada(proximoX, proximoY)) {
            girarDireita(); 
            direcaoParede = (direcaoParede + 1) % 4;
            continue;
        } else {
            int proximoX = roboX, proximoY = roboY;
            
            if (direcaoParede == 0) {
                proximoX += 2;
            } else if (direcaoParede == 1 || direcaoParede == -3 ) {
                proximoY -= 2;
            } else if (direcaoParede == 2) {
                proximoX -= 2;
            } else if (direcaoParede == 3 || direcaoParede == -1) {
                proximoY += 2;
            }
            if (caminhoVisitado(proximoX, proximoY)) {
                girarDireita(); 
                direcaoParede = (direcaoParede + 1) % 4;
                continue;
            }
        }
        
        int resultadoMovimento = moverFrente();
        
        if (resultadoMovimento == 1) {
            int proximoX = roboX, proximoY = roboY;
            
            if (direcaoParede == 0) {
                proximoX += 2;
            } else if (direcaoParede == 1 || direcaoParede == -3 ) {
                proximoY -= 2;
            } else if (direcaoParede == 2) {
                proximoX -= 2;
            } else if (direcaoParede == 3 || direcaoParede == -1) {
                proximoY += 2;
            }
            
            roboX = proximoX;
            roboY = proximoY;
            
            printf("Caminho percorrido: %d, %d\n", proximoX, proximoY);
            adicionarCoordenadaCaminho(proximoX, proximoY);
        } else if (resultadoMovimento == 0) {
            labirinto[proximoX][proximoY] = 1;
            printf("Parede visitada: %d, %d\n", proximoX, proximoY);
            adicionarCoordenadaParede(proximoX, proximoY);
            girarDireita();
            direcaoParede = (direcaoParede + 1) % 4;
        } else if (resultadoMovimento == 4) {
            encontrouObjetivo = true;
            int resultado;
            scanf("%d", &resultado);
        }
    }
    return 0;
}