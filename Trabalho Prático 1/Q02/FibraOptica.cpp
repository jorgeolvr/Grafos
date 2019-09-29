/**
 * Fibra Óptica
 * @author Jorge Allan de Castro Oliveira
 * @version 1 05/2018
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define inf 100000000

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS:
A estrutura cidade representa o vértíce de um Grafo.
O campo nome é uma cadeia de caracteres que guarda o nome de uma cidade.
O campo numRoteadores contém o número de roteadores candidatos.
O campo coord_x é o número que representa a abscissa do ponto.
O campo coord_y é o número que representa a ordernada do ponto.
*/
struct cidade {
    char nome[15];
    int numRoteadores;
    int roteadorInicial;
    int roteadorFinal;
    double *coord_x;
    double *coord_y;
};

/* Uma Cidade é um ponteiro para um cidade, ou seja, uma Cidade contém o endereço de uma cidade. */
typedef struct cidade *Cidade;

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS:
A estrutura grafo representa um Grafo.
O campo adj é um ponteiro para a matriz de adjacências do grafo.
O campo V contém o número de vértices e o campo A contém o número de arcos do grafo. */
struct grafo {
    int V;
    int A;
    double **adj;
};

/* Um Grafo é um ponteiro para um grafo, ou seja, um Grafo contém o endereço de um grafo. */
typedef struct grafo *Grafo;

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS:
A função iniciarMatriz() aloca uma matriz com linhas 0..r-1 e colunas 0..c-1.
Cada elemento da matriz recebe valor val. */
static double **iniciarMatriz(int r, int c, double valor) {
    double **m = (double**) malloc(r * sizeof(double *));

    for(int i = 0; i < r; i++){
        m[i] = (double*) malloc(c * sizeof(double));
    }

    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            m[i][j] = valor;
        }
    }
    return m;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS:
A função iniciarGrafo() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco. */
Grafo iniciarGrafo(int V) {
    Grafo grafo = (Grafo) malloc(sizeof *grafo);

    grafo->V = V;
    grafo->A = 0;
    grafo->adj = iniciarMatriz(V, V, inf);

    return grafo;
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS:
A função inserirArco() insere um arco v-w no grafo Grafo.
A função supõe que v e w são distintos, positivos e menores que grafo->V.
Se o grafo já tem um arco v-w, a função não faz nada. */
void inserirArco(Grafo grafo, int v, int w, double peso) {
        grafo->adj[v][w] = peso;
        grafo->adj[w][v] = peso;
        grafo->A ++;
}

/* FUNÇÃO QUE CALCULA O CAMINHO MAIS CURTO ENTRE DOIS VÉRTICES DO GRAFO:
A função Dijkstra() recebe por paramêtro um Grafo grafo.
Um inteiro s representando o vértice de início e t representando o vértice final.
Retorna a distância do menor caminho encontrado. */
double Dijkstra(Grafo grafo, int s, int t) {
    double dist[grafo->V];
    int perm[grafo->V], path[grafo->V];
    int current, i, k;
    double smalldist, newdist, dc;

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
    return dist[t];
}

/* A função novaCidade() recebe por paramêtro um char nome, int numRoteadores, int roteadorInicial, int roteadorFinal.
É uma espécie de construtor do tipo cidade onde será atribuido os dados dos locais. */
Cidade novaCidade(char nome[15], int numRoteadores, int roteadorInicial, int roteadorFinal){
    Cidade cidade = (Cidade) malloc(sizeof *cidade);
    strcpy(cidade->nome, nome);
    cidade->numRoteadores = numRoteadores;
    cidade->roteadorInicial = roteadorInicial;
    cidade->roteadorFinal = roteadorFinal;
    cidade->coord_x = (double *) malloc(numRoteadores * sizeof(double));
    cidade->coord_y = (double *) malloc(numRoteadores * sizeof(double));

    return cidade;
}

/* MÉTODO PRINCIPAL DO PROGRAMA:
A função main() é responsável pela leitura dos dados de entrada. */
int main(){
    int entrada = -1;

    while(entrada != 0){
        scanf("%d", &entrada);

        if(entrada >= 1 && entrada <= 1000) {
            Cidade cidades[entrada];
            int numRoteadores;
            int numRoteadoresTotal = 0;

            for(int i = 0; i < entrada; i++) {
                char nome[15];
                int numRoteadores;

                scanf("%s", nome);
                scanf("%d", &numRoteadores);

                if(i == 0) {
                    cidades[i] = novaCidade(nome, numRoteadores, 0, numRoteadores - 1);
                }else {
                    int roteadorInicial = cidades[i-1]->roteadorFinal + 1;
                    cidades[i] = novaCidade(nome, numRoteadores, roteadorInicial, roteadorInicial + numRoteadores - 1);
                }

                for(int j = 0; j < numRoteadores; j++) {
                    double coord_x, coord_y;

                    scanf("%lf", &coord_x);
                    scanf("%lf", &coord_y);

                    cidades[i]->coord_x[j] = coord_x;
                    cidades[i]->coord_y[j] = coord_y;
                }

                numRoteadoresTotal += numRoteadores;
            }

            Grafo grafo = iniciarGrafo(numRoteadoresTotal);

            int indices[entrada];
            for(int i = 0; i < entrada; i++) {
                indices[i] = 0;
            }

            for(int i = 0; i < entrada - 1; i++) {
                char nome1[15];
                char nome2[15];
                Cidade cidade1;
                Cidade cidade2;

                scanf("%s", nome1);
                scanf("%s", nome2);

                int j = 0;
                int cont = 0;
                while(cont < 2) {
                    if(strcmp(cidades[j]->nome, nome1) == 0 || strcmp(cidades[j]->nome, nome2) == 0) {
                        if(cont == 0) {
                            cidade1 = cidades[j];
                            cont++;
                            indices[j]++;
                        } else {
                            cidade2 = cidades[j];
                            cont++;
                            indices[j]++;
                        }
                    }
                    j++;
                }

                for(int i = 0; i < cidade1->numRoteadores; i++) {
                    for(int j = 0; j < cidade2->numRoteadores; j++) {
                        double novaDist = sqrt(pow((cidade1->coord_x[i] - cidade2->coord_x[j]),2) + pow((cidade1->coord_y[i] - cidade2->coord_y[j]),2));

                        if(novaDist < grafo->adj[cidade1->roteadorInicial + i][cidade2->roteadorInicial + j]) {
                            inserirArco(grafo, cidade1->roteadorInicial + i, cidade2->roteadorInicial + j, novaDist);
                        }
                    }
                }
            }

            int cidade1 = -1;
            int cidade2 = -1;

            for(int i = 0; i < entrada; i++) {
                if(indices[i] == 1) {
                    if(cidade1 == -1) {
                        cidade1 = i;
                    } else if(cidade2 == -1) {
                        cidade2 = i;
                    }
                }
            }

            double menorDist = inf;
            
            for(int i = cidades[cidade1]->roteadorInicial; i <= cidades[cidade1]->roteadorFinal; i++) {
                for(int j = cidades[cidade2]->roteadorInicial; j <= cidades[cidade2]->roteadorFinal; j++) {
                    double dist = Dijkstra(grafo, i, j);
                    if(dist < menorDist){
                        menorDist = dist;
                    }
                }
            }
            printf("%.1f\n", menorDist);
        }
    }
}
