/**
 * Colônia de Formigas
 * @author Jorge Allan de Castro Oliveira
 * @version 1 05/2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define max 50
#define inf 10000000000

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS:
A estrutura graph representa um grafo.
O campo adj é um ponteiro para a matriz de adjacências do grafo.
O campo V contém o número de vértices e o campo A contém o número de arcos do grafo. */
struct graph {
    int V;
    int A;
    int **adj;
};

/* Um Graph é um ponteiro para um graph, ou seja, um Graph contém o endereço de um graph. */
typedef struct graph *Graph;

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS:
A função MatrixInit() aloca uma matriz com linhas 0..r-1 e colunas 0..c-1.
Cada elemento da matriz recebe valor val. */
static int **MatrixInit(int r, int c, int val) {
    int **m = (int **) malloc(r * sizeof(int *));

    for(int i = 0; i < r; i++) {
        m[i] = (int *) malloc(c * sizeof(int));
    }

    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            m[i][j] = val;
        }
    }
    return m;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS:
A função GraphInit() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco. */
Graph GraphInit(int V) {
    Graph G = (Graph) malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = MatrixInit(V, V, 0);
    return G;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS:
A função GraphInsertArc() insere um arco v-w no grafo G.
A função supõe que v e w são distintos, positivos e menores que grafo->V.
Se o grafo já tem um arco v-w, a função não faz nada. */
void GraphInsertArc(Graph grafo, int v, int w, int peso) {
    if(grafo->adj[v][w] == 0) {
        grafo->adj[v][w] = peso;
        grafo->adj[w][v] = peso;
        grafo->A ++;
    }
}

/* FUNÇÃO QUE CALCULA O CAMINHO MAIS CURTO ENTRE DOIS VÉRTICES DO GRAFO:
A função Dijkstra() recebe por paramêtro um Graph grafo.
Um inteiro s representando o vértice de início e t representando o vértice final.
Imprime a distância do menor caminho encontrado. */
void Dijkstra (Graph grafo, int s, int t) {
    long dist[grafo->V];
    int perm[grafo->V], path[grafo->V];
    int current, i, k;
    long smalldist, newdist, dc;

    for (i = 0; i < grafo->V; i++) {
        perm[i] = 0;
        dist[i] = inf;
    }

    perm[s] = 1;
    dist[s] = 0;
    current = s;
    k = current;

    while (current != t) {
        smalldist = inf;
        dc = dist[current];

        for (i = 0; i < grafo->V; i++) {
            if (perm[i] == 0) {
                if(grafo->adj[current][i] == 0) {
                    newdist = dc + inf;
                }else {
                    newdist = dc + grafo->adj[current][i];
                }
                if (newdist < dist[i]) {
                    dist[i] = newdist;
                    path[i] = current;
                }
                if (dist[i] < smalldist) {
                    smalldist = dist[i];
                    k = i;
                }
            }
        }
        current = k;
        perm[current] = 1;
    }
    printf("%lu ", dist[t]);
}

/* MÉTODO PRINCIPAL DO PROGRAMA:
A função main() é responsável pela leitura dos dados de entrada. */
int main() {

    int entrada = -1;

    while (entrada != 0) {
        scanf("%d", &entrada);
        Graph grafo = GraphInit(entrada);

        if(entrada >= 2 && entrada <= 100000) {
            for(int i = 1; i < entrada; i++) {
                int destino;
                int tamanho;
                scanf("%d", &destino);
                scanf("%d", &tamanho);
                if((destino >= 0 && destino <= i - 1) && (tamanho >=1 && tamanho <= 1000000000)) {
                    GraphInsertArc(grafo, i, destino, tamanho);
                }
            }

            int consulta;

            scanf("%d", &consulta);
            if(consulta >= 1 && consulta <= 100000) {
                for(int i = 0; i < consulta; i++) {
                    int inicio;
                    int fim;
                    scanf("%d", &inicio);
                    scanf("%d", &fim);
                    Dijkstra(grafo, inicio, fim);
                }
                printf("\n");
            }
        }
    }
}
