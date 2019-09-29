/**
 * Colorindo Grafos
 * @author Jorge Allan de Castro Oliveira
 * @version 1 05/2018
 */

using namespace std;

#include <list>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* O campo grafo possui um ponteiro para as listas de adjacências.
O campo cor indica a cor de um vértice do grafo.
O campo V contém o número de vértices. */
class Grafo {
    int V;
    list<int> *grafo; 
    list<int> *cor;
public:
    Grafo(int V);
    int tamanho();
    void setCor(int v1, int cor); 
    void adicionarAresta(int v1, int v2);
};

Grafo::Grafo(int V) {
    this->V = V; //Atribuição do número de vértices
    grafo = new list<int>[V]; //Cria a lista dos vértices
    cor = new list<int>[V]; //Cria a lista das cores dos vértices
}

/* Retorna o tamanho do grafo em questão */
int Grafo::tamanho() {
  return this->V;
}

/* Adiciona uma cor nos vértices */
void Grafo::setCor(int v1, int color) {
    cor[v1].push_back(color);
}

/* A função adicionarAresta() insere um arco no grafo. */
void Grafo::adicionarAresta(int v1, int v2) {
    grafo[v1].push_back(v2);
}

/* MÉTODO PRINCIPAL DO PROGRAMA:
A função main() é responsável pela leitura dos dados de entrada. */
int main() {
    int t, n, m, p, k, nx_cor, mv_i, mv_j;     

    scanf("%d", &t);
    do {
        //Leitura de dados da entrada e criaçao do grafo
        scanf("%d %d %d %d", &n, &m, &p, &k);
        Grafo grafo(n);

        //Leitura e definição das cores dos vértices
        for (int i = 0; i < n; i++) {
          scanf("%d", &nx_cor);
          grafo.setCor(i, nx_cor);
        }

        //Leitura e inserção de vértices
        for (int i = 0; i < m; i++) {
          scanf("%d %d", &mv_i, &mv_j);
          grafo.adicionarAresta(mv_i-1, mv_j-1);
        }

        m = m + p;

        if(m == grafo.tamanho() - 1) {
           printf("Y\n");
        } else {
           printf("N");
        }
        t--;
    } while (t > 0);

    printf("\n");
    return 0;
}