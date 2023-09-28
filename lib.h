#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct lista {
    int num;
    struct lista* prox;
}Lista;

typedef struct grafo{
    int v;  //quantidade de vertices
    Lista **listaAdj;
}Grafo;

void menu();
Lista* criarNo(int num);
void liberarLista(Lista* lista);
Grafo* criarGrafo(int v);
void addAresta(Grafo* grafo, int origem, int fim);
void printGrafo(Grafo* grafo);
bool temCaminhoEuleriano(Grafo *grafo);