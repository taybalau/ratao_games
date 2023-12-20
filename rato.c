#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MATRIX_SIZE 120

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
    direcoesParede direcoes;
} Vertice_matriz;

Vertice_matriz *labirinto[MATRIX_SIZE][MATRIX_SIZE];

// Pilha de coordenadas
typedef struct
{
    Coordenada *array;
    int tamanho;
    int capacidade;
} PilhaCoordenadas;

PilhaCoordenadas *criarPilha(int capacidade)
{
    PilhaCoordenadas *pilha = (PilhaCoordenadas *)malloc(sizeof(PilhaCoordenadas));
    pilha->array = (Coordenada *)malloc(capacidade * sizeof(Coordenada));
    pilha->tamanho = 0;
    pilha->capacidade = capacidade;
    return pilha;
}

void empilhar(PilhaCoordenadas *pilha, Coordenada coordenada)
{
    pilha->array[pilha->tamanho++] = coordenada;
}

Coordenada desempilhar(PilhaCoordenadas *pilha)
{
    return pilha->array[--pilha->tamanho];
}

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
    int caminhosVisitados = 0;
    int paredesVisitadas = totalParedesVisitadas(atual);
    Coordenada direcoesCaminhos[4] = {
        (Coordenada){-1, 0},  // 0
        (Coordenada){0, 1},   // 1
        (Coordenada){1, 0},   // 2
        (Coordenada){0, -1}}; // 3

    int aux[4] = {0, 1, 2, 3};
    for (int i = 0; i < 4; i++)
    {
        Coordenada auxCaminho = {atual.x + direcoesCaminhos[i].x, atual.y + direcoesCaminhos[i].y};

        if (!paredeVisitada(atual, aux[i]))
        {

            if (caminhoVisitado(auxCaminho))
            {
                caminhosVisitados++;
            }
        }
    }

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

int decidirRotacao(Coordenada atual, Coordenada pai)
{

    int direcao;
    // printf("atual: %d, %d. pai: %d, %d\n",atual.x, atual.y, pai.x, pai.y);
    // printf("AAAAAAAAAAA: %d", atual.x - 1);

    if (atual.x - 1 == pai.x)
    {
        direcao = 0;
        return direcao;
    }
    else if (atual.x + 1 == pai.x)
    {
        direcao = 2;
        return direcao;
    }
    else if (atual.y - 1 == pai.y)
    {
        direcao = 3;
        return direcao;
    }
    else if (atual.y + 1 == pai.y)
    {
        direcao = 1;
        return direcao;
    }
}

int apontarParaOPai(Coordenada atual, int direcao)
{
    Coordenada pai = labirinto[atual.x][atual.y]->pai;
    Coordenada prox = proximaCoordenada(atual, direcao);
    int proxDirecao;
    int diferencaX = prox.x - pai.x;
    int diferencaY = prox.y - pai.y;

    if (diferencaY == 2 || diferencaY == -2 || diferencaX == 2 || diferencaX == -2)
    {
        while (!((prox.x == pai.x) && (prox.y == pai.y)))
        {
            direcao = girarEsquerda(direcao);
            prox = proximaCoordenada(atual, direcao);
        }
    }
    else
    {

        int direcaoAux;
        proxDirecao = decidirRotacao(atual, pai);

        switch (proxDirecao)
        {
        case 1:
            direcaoAux = -3;
            break;
        case 2:
            direcaoAux = -2;
            break;
        case 3:
            direcaoAux = -1;
        default:
            break;
        }

        if (direcao == proxDirecao || direcao == direcaoAux)
        {
            return direcao;
        }
        else if (direcao == 0)
        {
            if (proxDirecao == 3)
            {
                direcao = girarEsquerda(direcao);
            }
            else if (proxDirecao == 1)
            {
                direcao = girarDireita(direcao);
            }
        }
        else if (proxDirecao == 0)
        {
            if (direcao == 3 || direcao == -1)
            {
                direcao = girarDireita(direcao);
            }
            else if (direcao == 1 || direcao == -3)
            {
                direcao = girarEsquerda(direcao);
            }
        }
        else if (direcao > 0)
        {
            if (proxDirecao > direcao)
            {
                direcao = girarDireita(direcao);
            }
            else if (proxDirecao < direcao)
            {
                direcao = girarEsquerda(direcao);
            }
        }
        else if (direcao < 0)
        {
            if (direcaoAux > direcao)
            {
                direcao = girarDireita(direcao);
            }
            else if (direcaoAux < direcao)
            {
                direcao = girarEsquerda(direcao);
            }
        }
    }
    return direcao;
}

int apontarNaPilha(Coordenada atual, int direcao, PilhaCoordenadas *pilha)
{
    Coordenada paiNaPilha = pilha->array[pilha->tamanho - 1];
    Coordenada prox = proximaCoordenada(atual, direcao);
    int proxDirecao;

    int diferencaX = prox.x - paiNaPilha.x;
    int diferencaY = prox.y - paiNaPilha.y;

    if (diferencaY == 2 || diferencaY == -2 || diferencaX == 2 || diferencaX == -2)
    {
        while (!((prox.x == paiNaPilha.x) && (prox.y == paiNaPilha.y)))
        {
            direcao = girarEsquerda(direcao);
            prox = proximaCoordenada(atual, direcao);
        }
    }
    else
    {
        proxDirecao = decidirRotacao(atual, paiNaPilha);
        int direcaoAux;

        switch (proxDirecao)
        {
        case 1:
            direcaoAux = -3;
            break;
        case 2:
            direcaoAux = -2;
            break;
        case 3:
            direcaoAux = -1;
        default:
            break;
        }

        if (direcao == proxDirecao || direcao == direcaoAux)
        {
            return direcao;
        }
        else if (direcao == 0)
        {
            if (proxDirecao == 3)
            {
                direcao = girarEsquerda(direcao);
            }
            else if (proxDirecao == 1)
            {
                direcao = girarDireita(direcao);
            }
        }
        else if (proxDirecao == 0)
        {
            if (direcao == 3 || direcao == -1)
            {
                direcao = girarDireita(direcao);
            }
            else if (direcao == 1 || direcao == -3)
            {
                direcao = girarEsquerda(direcao);
            }
        }
        else if (direcao > 0)
        {
            if (proxDirecao > direcao)
            {
                direcao = girarDireita(direcao);
            }
            else if (proxDirecao < direcao)
            {
                direcao = girarEsquerda(direcao);
            }
        }
        else if (direcao < 0)
        {
            if (direcaoAux > direcao)
            {
                direcao = girarDireita(direcao);
            }
            else if (direcaoAux < direcao)
            {
                direcao = girarEsquerda(direcao);

            }
        }
    }

    return direcao;
}

void desceNaDFS(PilhaCoordenadas *pilhaVolta, Coordenada atual, int direcao)
{

    if (pilhaVolta->tamanho == 0)
    {
        return;
    }
    else
    {
        Coordenada paiNaPilha = pilhaVolta->array[pilhaVolta->tamanho - 1];
        direcao = apontarNaPilha(atual, direcao, pilhaVolta);
        moverFrente();
        desempilhar(pilhaVolta);
        desceNaDFS(pilhaVolta, paiNaPilha, direcao);
    }
}

void sobeNaDFS(PilhaCoordenadas *pilhaVolta, Coordenada atual, int direcao, PilhaCoordenadas *pilhaIda)
{

    if (pilhaVolta->tamanho == 0)
    {
        desempilhar(pilhaIda);
        desceNaDFS(pilhaIda, atual, direcao);
        return;
    }
    else
    {
        Coordenada paiNaPilha = pilhaVolta->array[pilhaVolta->tamanho - 1];
        direcao = apontarNaPilha(atual, direcao, pilhaVolta);
        moverFrente();
        desempilhar(pilhaVolta);
        empilhar(pilhaIda, paiNaPilha);
        sobeNaDFS(pilhaVolta, paiNaPilha, direcao, pilhaIda);
    }
}
// Buscas
void buscaProfundidade(Coordenada atual, int direcao, PilhaCoordenadas *pilha, PilhaCoordenadas *pilhaIda)
{
    int resultado;
    while (!todosVizinhosVisitados(atual, direcao))
    {
        Coordenada prox = proximaCoordenada(atual, direcao);

        if (!caminhoVisitado(prox) && !paredeVisitada(prox, direcao))
        {
            resultado = moverFrente();
            if (resultado == 2)
            {
                marcarVisitado(prox);
                marcarPai(prox, atual);
                empilhar(pilhaIda, prox);
                sobeNaDFS(pilha, prox, direcao, pilhaIda);
                return;
            }

            else if (resultado == 1)
            {
                marcarVisitado(prox);
                marcarPai(prox, atual);
                empilhar(pilha, prox);
                buscaProfundidade(prox, direcao, pilha, pilhaIda);
                return;
            }
            else if (resultado == 0)
            {
                marcarParede(atual, direcao);
                direcao = girarDireita(direcao);
            }
        }
        else
        {
            direcao = girarDireita(direcao);
        }
    }
    Coordenada pai = labirinto[atual.x][atual.y]->pai;
    direcao = apontarParaOPai(atual, direcao);
    moverFrente();
    desempilhar(pilha);
    buscaProfundidade(pai, direcao, pilha, pilhaIda);
}

int main()
{
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            labirinto[i][j] = malloc(sizeof(Vertice_matriz));
            labirinto[i][j]->visitado = false;
        }
    }

    PilhaCoordenadas *pilhaDeCoordenadas = criarPilha(MATRIX_SIZE * MATRIX_SIZE);
    PilhaCoordenadas *pilhaDaVitoria = criarPilha(MATRIX_SIZE * MATRIX_SIZE);

    int direcao = 0;
    Coordenada meioDaMatriz = {MATRIX_SIZE / 2, MATRIX_SIZE / 2};
    marcarVisitado(meioDaMatriz);
    empilhar(pilhaDeCoordenadas, meioDaMatriz);
    buscaProfundidade(meioDaMatriz, direcao, pilhaDeCoordenadas, pilhaDaVitoria);
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            free(labirinto[i][j]);
        }
    }
    return 0;
}
