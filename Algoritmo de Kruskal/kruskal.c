#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NUMBER_OF_VERTICES 18
/**
 * @brief Struct Edge.
 *  [firstVertex] -- ~ / weight / ~ --> [secondVertex].
 */
typedef struct {
  int firstVertex, secondVertex;
  int weight;
} Edge;
/**
 * @brief Struct EdgeList
 *  É composta por um array de arestas e um contador.
 */
typedef struct {
  Edge *data;
  int counter;
} EdgeList;

/**
* @brief
* 1. Inicializa a lista de arestas 'edgeList' com as arestas do grafo de
entrada.
2. Ordena a lista de arestas 'edgeList' em ordem crescente de peso.
3. Inicializa o array 'belongs', que será utilizado para rastrear a qual
componente conexo um vértice pertence.
4. Coloca o counter de 'spanList' como zero.
5. Itera sobre todas as arestas em 'edgeList'.
6. Para cada aresta, verifica se os vértices de origem e destino não
pertencem ao último vértice do grafo.
7. Verifica se os vértices de origem e destino estão em componentes conexos
diferentes utilizando a função 'find' e o array 'belongs'.
8. Caso estejam em componentes conexos diferentes, adiciona a aresta em
'spanList' e aplica a união dos componentes conexos utilizando a função
'applyUnion'.
9. Ao final, libera a memória alocada para o array 'belongs'.
*
* @param edgeList lista de arestas
* @param n número de vértices
* @param graph array bidimensional em que estão presentes todos os vértices,
ligações e respetivos pesos.
* @param spanList lista de arestas que compoẽm a árvore geradora mínima.
*/
void kruskal(EdgeList *edgeList, int n, int graph[][MAX_NUMBER_OF_VERTICES],
             EdgeList *spanList);
/**
* @brief
    É responsável por retornar o indentificador do conjunto ao qual um
determinado vértice pertence. O parãmetro 'belongs' é um porteiro para o array
que armazena os identificadores dos conjuntos, e o parâmetro 'vertexNumber' é o
número do vértice para o qual desejamos obter o conjunto.
*
* @param belongs Array que armazena os indentificadores dos conjuntos.
* @param vertexNumber Número do vértice para o qual desejamos obter o conjunto.
* @return int Indentificador do conjunto ao qual pertence o vértice.
*/
int find(int *belongs, int vertexNumber);
/**
 * @brief Aplica a operação de união entre dois conjuntos.
 *
 * @param belongs Array que armazena os indentificadores dos conjuntos.
 * @param firstCluster Indentificador do primeiro conjunto.
 * @param secondCluster Indentificador do segundo conjunto.
 * @param n Número total de elemenos no array belongs.
 */
void applyUnion(int *belongs, int firstCluster, int secondCluster, int n);
/**
 * @brief Ordena a lista de arestas através do algoritmo bubble sort
 *      em ordem crescente com base no peso.
 *
 * @param edgeList edgeList Lista de arestas a ser ordernada.
 */
void sort(EdgeList *edgeList);
/**
* @brief Percorre a lista de arestas 'spanList' e imprime cada aresta,
        juntamente com o seu peso. A variável 'weight' é usada para calcular o
custo total somando os pesos de todas as arestas. No final, o custo total é
exibido na saída.
*
* @param spanList Lista de arestas
*/
void print(const EdgeList spanList);

int main() {
  EdgeList edgeList;
  EdgeList spanList;
  edgeList.data = malloc(sizeof(Edge) * MAX_NUMBER_OF_VERTICES * 3);
  spanList.data = malloc(sizeof(Edge) * MAX_NUMBER_OF_VERTICES);
  int graph[MAX_NUMBER_OF_VERTICES][MAX_NUMBER_OF_VERTICES] = {
      {0, 0, 0, 0, 0, 80, 0, 0, 0, 0, 0, 0, 70, 0, 0, 0, 0, 100},
      {0, 0, 0, 0, 0, 0, 80, 170, 0, 0, 0, 0, 0, 0, 135, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50, 0, 0, 50, 100, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 140, 0},
      {0, 0, 0, 0, 0, 160, 0, 0, 100, 0, 0, 80, 0, 200, 0, 0, 0, 0},
      {80, 0, 0, 0, 160, 0, 0, 0, 180, 70, 0, 0, 0, 0, 0, 0, 0, 80},
      {0, 80, 0, 0, 0, 0, 0, 0, 0, 0, 150, 100, 0, 120, 0, 0, 0, 0},
      {0, 170, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 260, 0, 0, 0},
      {0, 0, 0, 200, 100, 160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 150, 80},
      {0, 0, 0, 0, 0, 70, 0, 0, 0, 0, 130, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 150, 0, 0, 130, 0, 0, 0, 70, 50, 0, 0, 0},
      {0, 0, 0, 0, 80, 0, 100, 0, 0, 0, 0, 0, 0, 150, 0, 0, 0, 0},
      {70, 0, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 80, 120, 0},
      {0, 0, 0, 0, 200, 0, 120, 0, 0, 0, 70, 150, 0, 0, 0, 0, 0, 0},
      {0, 135, 0, 0, 0, 0, 0, 260, 0, 0, 50, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 80, 0, 0, 0, 0, 0},
      {0, 0, 100, 140, 0, 0, 0, 0, 150, 0, 0, 0, 120, 0, 0, 0, 0, 110},
      {100, 0, 0, 0, 0, 80, 0, 0, 80, 0, 0, 0, 0, 0, 0, 0, 110, 0}};
  int n = 18;
  int choosenNumber = 2;

  kruskal(&edgeList, n, graph, &spanList);
  print(spanList);

  free(edgeList.data);
  free(spanList.data);
  return 0;
}

void kruskal(EdgeList *edgeList, int n, int graph[][MAX_NUMBER_OF_VERTICES],
             EdgeList *spanList) {
  int *belongs;
  int i, j, firstCluster, secondCluster;
  edgeList->counter = 0;

  for (i = 0; i < n; i++) {
    for (j = 0; j < i; j++) {
      if (graph[i][j] != 0) {
        edgeList->data[edgeList->counter].firstVertex = i + 1;
        edgeList->data[edgeList->counter].secondVertex = j + 1;
        edgeList->data[edgeList->counter].weight = graph[i][j];
        edgeList->counter++;
      }
    }
  }

  sort(edgeList);

  belongs = malloc(sizeof(int) * n);

  for (i = 0; i < n; i++) {
    belongs[i] = i + 1;
  }

  spanList->counter = 0;

  for (i = 0; i < edgeList->counter; i++) {
    firstCluster = find(belongs, edgeList->data[i].firstVertex);
    secondCluster = find(belongs, edgeList->data[i].secondVertex);

    if (firstCluster != secondCluster) {
      spanList->data[spanList->counter] = edgeList->data[i];
      spanList->counter++;
      applyUnion(belongs, firstCluster, secondCluster, n);
    }
  }

  free(belongs);
}

int find(int *belongs, int vertexNumber) { return (belongs[vertexNumber - 1]); }

void applyUnion(int *belongs, int firstCluster, int secondCluster, int n) {
  int i;

  for (i = 0; i < n; i++) {
    if (belongs[i] == secondCluster) {
      belongs[i] = firstCluster;
    }
  }
}

void sort(EdgeList *edgeList) {
  int i, j;
  Edge temporaryEdge;

  for (i = 0; i < edgeList->counter - 1; i++) {
    for (j = 0; j < edgeList->counter - i - 1; j++) {
      if (edgeList->data[j].weight > edgeList->data[j + 1].weight) {
        temporaryEdge = edgeList->data[j];
        edgeList->data[j] = edgeList->data[j + 1];
        edgeList->data[j + 1] = temporaryEdge;
      }
    }
  }
}

void print(EdgeList spanList) {
  int i, cost = 0;
  for (i = 0; i < spanList.counter; i++) {
    printf("\n \t\t[%d] -> [%d]\t {%d}", spanList.data[i].firstVertex,
           spanList.data[i].secondVertex, spanList.data[i].weight);
    cost += spanList.data[i].weight;
  }

  printf("\n\n\t\t Total cost: %d.\n", cost);
}
