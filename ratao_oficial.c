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
    //fprintf(stderr, "Pai: (%d, %d). Prox:(%d, %d)\n", pai.x, pai.y, prox.x, prox.y);
    //fprintf(stderr, "X é diferente? %d\n", pai.x != prox.x);
    //fprintf(stderr, "Y é diferente? %d\n", pai.y != prox.y);
    //fprintf(stderr, "Socorro? %d\n", (prox.x != pai.x) && (prox.y != pai.y));

    while (!((prox.x == pai.x) && (prox.y == pai.y)))
    {
        //fprintf(stderr, "entrei\n");
        direcao = girarEsquerda(direcao);
        //fprintf(stderr, "Girando para esquerda:\n");
        //fprintf(stderr, "Direção:%d\n", direcao);
        prox = proximaCoordenada(atual, direcao);
        //fprintf(stderr, "Estou apontando para: (%d, %d)\n", prox.x, prox.y);
    }
    return direcao;
}
// Buscas
void buscaProfundidade(Coordenada atual, int direcao)
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
                return;
            }

            else if (resultado == 1)
            {
                //fprintf("Coordenada caminho: %d, %d\n", prox.x, prox.y);
                marcarVisitado(prox);
                marcarPai(prox, atual);
                buscaProfundidade(prox, direcao);
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
    buscaProfundidade(pai, direcao);
}
// BFS
struct queue
{
    int items[SIZE];
    int front;
    int rear;
};
struct queue *createQueue();
void enqueue(struct queue *q, int);
int dequeue(struct queue *q);
void display(struct queue *q);
int isEmpty(struct queue *q);
void printQueue(struct queue *q);
// void bfs(struct Graph* graph, int startVertex) {
//   struct queue* q = createQueue();
//   graph->visited[startVertex] = 1;
//   enqueue(q, startVertex);
//   while (!isEmpty(q)) {
//     printQueue(q);
//     int currentVertex = dequeue(q);
//     printf("Visited %d\n", currentVertex);
//     struct node* temp = graph->adjLists[currentVertex];
//     while (temp) {
//       int adjVertex = temp->vertex;
//       if (graph->visited[adjVertex] == 0) {
//         graph->visited[adjVertex] = 1;
//         enqueue(q, adjVertex);
//       }
//       temp = temp->next;
//     }
//   }
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
    marcarVisitado(meioDaMatriz);
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