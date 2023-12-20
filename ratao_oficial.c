#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MATRIX_SIZE 200
#define SIZE 40

// Structs
typedef struct
{
    int x;
    int y;
} Coordenada;

typedef struct
{
    bool f;
    bool d;
    bool e;
    bool t;
} direcoesParede;

typedef struct vertice_matriz
{
    bool visitado;
    Coordenada pai;
    bool parede;
    direcoesParede direcoes;
} Vertice_matriz;

Vertice_matriz *labirinto[MATRIX_SIZE][MATRIX_SIZE];

// Funções de movimentação
int girarEsquerda(int direcao)
{
    printf("l\n");
    fflush(stdout);
    int resultado;
    scanf("%d", &resultado);
    return (direcao - 1) % 4;
}
int girarDireita(int direcao)
{
    printf("r\n");
    fflush(stdout);
    int resultado;
    scanf("%d", &resultado);
    return (direcao + 1) % 4;
}
int moverFrente()
{
    printf("w\n");
    fflush(stdout);
    int resultado;
    scanf("%d", &resultado);
    return resultado;
}
// Funções de reconhecimento
void marcarVisitado(Coordenada atual)
{
    labirinto[atual.x][atual.y]->visitado = true;
}
void marcarPai(Coordenada atual, Coordenada anterior)
{
    labirinto[atual.x][atual.y]->pai = anterior;
}
void marcarParede(Coordenada atual, int direcao)
{
    if (direcao == 0)
    {
        labirinto[atual.x][atual.y]->direcoes.f = true;
    }
    else if (direcao == 1 || direcao == -3)
    {
        labirinto[atual.x][atual.y]->direcoes.d = true;
    }
    else if (direcao == 2 || direcao == -2)
    {
        labirinto[atual.x][atual.y]->direcoes.t = true;
    }
    else if (direcao == 3 || direcao == -1)
    {
        labirinto[atual.x][atual.y]->direcoes.e = true;
    }
}
bool caminhoVisitado(Coordenada prox)
{
    return labirinto[prox.x][prox.y]->visitado;
}
bool paredeVisitada(Coordenada prox, int direcao)
{
    if (direcao == 0)
    {
        return labirinto[prox.x][prox.y]->direcoes.f;
    }
    else if (direcao == 1 || direcao == -3)
    {
        return labirinto[prox.x][prox.y]->direcoes.d;
    }
    else if (direcao == 2 || direcao == -2)
    {
        return labirinto[prox.x][prox.y]->direcoes.t;
    }
    else if (direcao == 3 || direcao == -1)
    {
        return labirinto[prox.x][prox.y]->direcoes.e;
    }
}
int totalParedesVisitadas(Coordenada atual)
{
    int qtdParedesVisitadas = 0;
    if (labirinto[atual.x][atual.y]->direcoes.f)
    {
        qtdParedesVisitadas++;
    }
    if (labirinto[atual.x][atual.y]->direcoes.d)
    {
        qtdParedesVisitadas++;
    }
    if (labirinto[atual.x][atual.y]->direcoes.e)
    {
        qtdParedesVisitadas++;
    }
    if (labirinto[atual.x][atual.y]->direcoes.t)
    {
        qtdParedesVisitadas++;
    }
    return qtdParedesVisitadas;
}
bool todosVizinhosVisitados(Coordenada atual, int direcao)
{
    //fprintf(stderr, "inicio\n");
    //fprintf(stderr,"Atual: %d, %d\n", atual.x, atual.y);
    //fprintf(stderr,"Direção: %d\n", direcao);
    //fprintf(stderr,"Paredes: f-%d, d-%d, t-%d, e-%d\n", labirinto[atual.x][atual.y]->direcoes.f, labirinto[atual.x][atual.y]->direcoes.d, labirinto[atual.x][atual.y]->direcoes.t, labirinto[atual.x][atual.y]->direcoes.e);
    int caminhosVisitados = 0;
    int paredesVisitadas = totalParedesVisitadas(atual);
    Coordenada direcoesCaminhos[4] = {
        (Coordenada){-1, 0}, //0
        (Coordenada){0, 1}, //1
        (Coordenada){1, 0}, //2
        (Coordenada){0, -1}};//3

    int aux[4] = {0, 1, 2, 3};
    for (int i = 0; i < 4; i++)
    {
        Coordenada auxCaminho = {atual.x + direcoesCaminhos[i].x, atual.y + direcoesCaminhos[i].y};
    
    if(!paredeVisitada(atual, aux[i])) {
        //printf("Caminho analisado: %d, %d\n", auxCaminho.x, auxCaminho.y);
        //printf("Direcao: %d\n", aux[i]);
        if (caminhoVisitado(auxCaminho))
        {
            // printf("Caminho visitado: %d, %d\n", auxCaminho.x, auxCaminho.y);
            caminhosVisitados++;
        }}
    }
    //fprintf(stderr, "Caminhos: %d. Paredes: %d\n", caminhosVisitados, paredesVisitadas);
    //fprintf(stderr, "Total de direções visitadas: %d\n", caminhosVisitados + paredesVisitadas);
    //fprintf(stderr, "fim\n");
    if (caminhosVisitados + paredesVisitadas == 4)
    {
        return true;
    }
    else
    {
        return false;
    }
}
Coordenada proximaCoordenada(Coordenada atual, int direcao)
{
    Coordenada proxima = atual;
    if (direcao == 0)
    {
        proxima.x -= 1;
    }
    else if (direcao == 1 || direcao == -3)
    {
        proxima.y += 1;
    }
    else if (direcao == 2 || direcao == -2)
    {
        proxima.x += 1;
    }
    else if (direcao == 3 || direcao == -1)
    {
        proxima.y -= 1;
    }
    return proxima;
}
int apontarParaOPai(Coordenada atual, int direcao)
{
    Coordenada pai = labirinto[atual.x][atual.y]->pai;
    Coordenada prox = proximaCoordenada(atual, direcao);
    fprintf(stderr, "Pai: (%d, %d). Prox:(%d, %d)\n", pai.x, pai.y, prox.x, prox.y);
    fprintf(stderr, "X é diferente? %d\n", pai.x != prox.x);
    fprintf(stderr, "Y é diferente? %d\n", pai.y != prox.y);
    fprintf(stderr, "Socorro? %d\n", (prox.x != pai.x) && (prox.y != pai.y));

    while (!((prox.x == pai.x) && (prox.y == pai.y)))
    {
        fprintf(stderr, "entrei\n");
        direcao = girarEsquerda(direcao);
        fprintf(stderr, "Girando para esquerda:\n");
        fprintf(stderr, "Direção:%d\n", direcao);
        prox = proximaCoordenada(atual, direcao);
        fprintf(stderr, "Estou apontando para: (%d, %d)\n", prox.x, prox.y);
    }
    return direcao;
}
// Buscas

void sobeNaDFS(Coordenada atual, int direcao)
{
    fprintf(stderr, "entrou na sobenadfs\n");
    int direcaoPai = apontarParaOPai(atual, direcao);
    fprintf(stderr, "passou da apontarparaopai\n");
    int chegouNaOrigem = moverFrente(); // 1 se não chegou, 2 se chegou
    if (chegouNaOrigem == 2) {
        fprintf(stderr, "chegou na origem\n");
        return;
    }
    sobeNaDFS(atual, direcaoPai);
}
void buscaProfundidade(Coordenada atual, int direcao, Coordenada * posicaoFinal, int * direcaoFinal)
{
    int resultado;
    while (!todosVizinhosVisitados(atual, direcao))
    {
        //fprintf(stderr, "Coordenada atual: %d, %d\n", atual.x, atual.y);
        Coordenada prox = proximaCoordenada(atual, direcao);
        // Coordenada proxParede = proximaParede(atual, direcao);
        if (!caminhoVisitado(prox) && !paredeVisitada(prox, direcao))
        {
            resultado = moverFrente();
            if (resultado == 2)
            {
                marcarVisitado(prox);
                marcarPai(prox, atual);
                *posicaoFinal = proximaCoordenada(atual, direcao);
                *direcaoFinal = direcao;
                return;
            }

            else if (resultado == 1)
            {
                //fprintf("Coordenada caminho: %d, %d\n", prox.x, prox.y);
                marcarVisitado(prox);
                marcarPai(prox, atual);
                fprintf("prox %d %d", prox.x, prox.y);
                fprintf("atual %d %d", atual.x, atual.y);
                buscaProfundidade(prox, direcao, posicaoFinal, direcaoFinal);
                return;
            }
            else if (resultado == 0)
            {
                //fprintf(stderr, "Achei uma parede\n");
                marcarParede(atual, direcao);
                direcao = girarDireita(direcao);
            }
        }
        else
        {
            direcao = girarDireita(direcao);
        }
    }
    //fprintf(stderr, "Todos caminhos já são conhecidos... Voltando\n");
    Coordenada pai = labirinto[atual.x][atual.y]->pai;
    direcao = apontarParaOPai(atual, direcao);
    moverFrente();
    buscaProfundidade(pai, direcao, posicaoFinal, direcaoFinal);
}
// BFS
struct queue
{
    int items[SIZE];
    int front;
    int rear;
};

int main()
{
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            labirinto[i][j] = malloc(sizeof(Vertice_matriz));
            labirinto[i][j]->visitado = false;
            labirinto[i][j]->parede = false;
        }
    }
    Coordenada posicaoFinal;
    int direcao = 0, direcaoFinal;
    Coordenada meioDaMatriz = {MATRIX_SIZE / 2, MATRIX_SIZE / 2};
    marcarVisitado(meioDaMatriz);
    buscaProfundidade(meioDaMatriz, direcao, &posicaoFinal, &direcaoFinal); // encontra o objetivo
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            if (labirinto[i][j]->visitado == true) {
                fprintf(stderr, "%d", 1);
            }
            else {
                fprintf(stderr, "%d", 0);
            }
            
        }
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "antes da dfs\n");
    fprintf(stderr, "%d %d\n", posicaoFinal.x, posicaoFinal.y);
    Coordenada pai = labirinto[posicaoFinal.x][posicaoFinal.y]->pai;
    fprintf(stderr, "%d %d", pai.x, pai.y);
    /* fprintf("%d", apontarParaOPai(pai, direcaoFinal)); */
    sobeNaDFS(posicaoFinal, direcaoFinal);
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            free(labirinto[i][j]);
        }
    }
    return 0;
}