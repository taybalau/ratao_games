#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MATRIX_SIZE 200

typedef struct
{
    int x;
    int y;
} Coordenada;

typedef struct vertice_matriz
{
    bool visitado;
    Coordenada pai;
    bool parede;
} Vertice_matriz;

Vertice_matriz *labirinto[MATRIX_SIZE][MATRIX_SIZE];

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

void marcarVisitado(Coordenada atual)
{
    labirinto[atual.x][atual.y]->visitado = true;
}

void marcarPai(Coordenada atual, Coordenada anterior)
{
    labirinto[atual.x][atual.y]->pai = anterior;
}

void marcarParede(Coordenada atual)
{
    labirinto[atual.x][atual.y]->parede = true;
}

bool caminhoVisitado(Coordenada prox)
{
    return labirinto[prox.x][prox.y]->visitado;
}

bool paredeVisitada(Coordenada prox)
{
    return labirinto[prox.x][prox.y]->parede;
}

bool todosVizinhosVisitados(Coordenada atual)
{
    //printf("Inicio:\n");
    int caminhosVisitados = 0;
    int paredesVisitadas = 0;
    Coordenada direcoesParede[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    Coordenada direcoesCaminho[4] = {{-2, 0}, {0, 2}, {2, 0}, {0, -2}};

    for (int i = 0; i < 4; i++)
    {
        Coordenada auxParede = {atual.x + direcoesParede[i].x, atual.y + direcoesParede[i].y};
        // printf("Parede vizinha: %d, %d\n", auxParede.x, auxParede.y);
        Coordenada auxCaminho = {atual.x + direcoesCaminho[i].x, atual.y + direcoesCaminho[i].y};
        // printf("Caminho vizinha: %d, %d\n", auxCaminho.x, auxCaminho.y);
        if (paredeVisitada(auxParede))
        {
            // printf("Parede visitada: %d, %d\n", auxParede.x, auxParede.y);
            paredesVisitadas++;
        }
        else if (caminhoVisitado(auxCaminho))
        {
            // printf("Caminho visitado: %d, %d\n", auxCaminho.x, auxCaminho.y);
            caminhosVisitados++;
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
        proxima.x -= 2;
    }
    else if (direcao == 1 || direcao == -3)
    {
        proxima.y += 2;
    }
    else if (direcao == 2)
    {
        proxima.x += 2;
    }
    else if (direcao == 3 || direcao == -1)
    {
        proxima.y -= 2;
    }

    return proxima;
}

Coordenada proximaParede(Coordenada atual, int direcao)
{
    Coordenada proxima = atual;

    if (direcao == 0)
    {
        proxima.x--;
    }
    else if (direcao == 1 || direcao == -3)
    {
        proxima.y++;
    }
    else if (direcao == 2)
    {
        proxima.x++;
    }
    else if (direcao == 3 || direcao == -1)
    {
        proxima.y--;
    }

    return proxima;
}

int voltarParaOPai(Coordenada atual, int direcao)
{
    Coordenada pai = labirinto[atual.x][atual.y]->pai;
    Coordenada prox = proximaCoordenada(atual, direcao);

    int diferencaX = prox.x - pai.x;
    int diferencaY = prox.y - pai.y;

    if (diferencaX == 4 || diferencaX == -4 || diferencaY == 4 || diferencaY == -4)
    {
        girarDireita(direcao);
        girarDireita(direcao);
        direcao = (direcao + 1) % 4;
        direcao = (direcao + 1) % 4;
    }
    else if ((prox.x != pai.x) && (prox.y != pai.y))
    {
        if (prox.x < pai.x)
        {
            girarDireita(direcao);
            direcao = (direcao - 1) % 4;
        }
        else
        {
            girarEsquerda(direcao);
            direcao = (direcao + 1) % 4;
        }
    }

    return direcao;

}

void buscaProfundidade(Coordenada atual, int direcao)
{
    int resultado;
    while (!todosVizinhosVisitados(atual))
    {
        //printf("Coordenada atual: %d, %d\n", atual.x, atual.y);
        Coordenada prox = proximaCoordenada(atual, direcao);
        Coordenada proxParede = proximaParede(atual, direcao);

        if (!caminhoVisitado(prox) && !paredeVisitada(proxParede))
        {
            resultado = moverFrente();
            if (resultado == 2)
            {
                return;
            }
            else if (resultado == 1)
            {
                // printf("Coordenada caminho: %d, %d\n", prox.x, prox.y);
                marcarVisitado(prox);
                marcarPai(prox, atual);
                buscaProfundidade(prox, direcao);
                return;
            }
            else if (resultado == 0)
            {
                // printf("Achei uma parede: %d, %d\n", proxParede.x, proxParede.y);
                marcarParede(proxParede);
                direcao = girarDireita(direcao);
            }
        }
        else
        {
            direcao = girarDireita(direcao);
        }
    }
    
    Coordenada pai = labirinto[atual.x][atual.y]->pai;
    direcao = voltarParaOPai(atual, direcao);
    moverFrente();
    buscaProfundidade(pai, direcao);
}

// void buscaEmLargura(){
    
// }

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

    int direcao = 0;
    Coordenada meioDaMatriz = {MATRIX_SIZE / 2, MATRIX_SIZE / 2};
    buscaProfundidade(meioDaMatriz, direcao);

    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            free(labirinto[i][j]);
        }
    }

    return 0;
}
