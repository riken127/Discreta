#include <limits.h>
#include <malloc.h>
#include <stdio.h>
#define NUM_VERTICES 18 // Número de vértices no grafo
/**
 * @brief Encontra o vértice não visitado com a menor distância.
 *
 * @param distance Array que contém as distâncias dos vértices.
 * @param visited Array que indica quais os vértices que foram visitados.
 * @return int Índice do vértice não visitado com a menor distância.
 */
int minDistance(int *distance, int *visited);
/**
 * @brief Imprime o caminho percorrido a partir do vértice inicial até o vértice
 * atual.
 *
 * @param parent Array contendo os pais de cada vértice no caminho mínimo
 * @param j Vértice atual a ser impresso.
 */
void printPath(int *parent, int j);
/**
 * @brief Imprime a solução do algoritmo para cada vértice da origem.
 *
 * @param distance Array que contém as distâncias mínimas de um vértice de
 * origem para os outros vértices.
 * @param parent Array que contém os pais de cada vérticce no caminho mínimo.
 * @param source  Vértice da origem.
 */
void printSolution(int *distance, int *parent, int source);

/**
 * @brief Executa o algoritmo de dijkstra para encontrar os caminhos mais curtos
 * a partir de de um vértice de origem em um grafo.
 *
 * @param graph Grafo ponderado representado com uma matriz de adjacência .
 * @param source Vértice de origem a partir do qual os caminhos mais curtos
 * serão encontrados.
 */
void dijkstra(int **graph, int source);

int main() {
  int **graph = (int **)malloc(NUM_VERTICES * sizeof(int *));

  for (int i = 0; i < NUM_VERTICES; i++) {
    graph[i] = (int *)malloc(NUM_VERTICES * sizeof(int));
  }

  graph[0] = (int[]){0, 0, 0, 0, 0, 80, 0, 0, 0, 0, 0, 0, 70, 0, 0, 0, 0, 100};
  graph[1] = (int[]){0, 0, 0, 0, 0, 0, 80, 170, 0, 0, 0, 0, 0, 0, 135, 0, 0, 0};
  graph[2] = (int[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50, 0, 0, 50, 100, 0};
  graph[3] = (int[]){0, 0, 0, 0, 0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 140, 0};
  graph[4] =
      (int[]){0, 0, 0, 0, 0, 160, 0, 0, 100, 0, 0, 80, 0, 200, 0, 0, 0, 0};
  graph[5] =
      (int[]){80, 0, 0, 0, 160, 0, 0, 0, 180, 70, 0, 0, 0, 0, 0, 0, 0, 80};
  graph[6] =
      (int[]){0, 80, 0, 0, 0, 0, 0, 0, 0, 0, 150, 100, 0, 120, 0, 0, 0, 0};
  graph[7] = (int[]){0, 170, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 260, 0, 0, 0};
  graph[8] =
      (int[]){0, 0, 0, 200, 100, 160, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 150, 80};
  graph[9] = (int[]){0, 0, 0, 0, 0, 70, 0, 0, 0, 0, 130, 0, 0, 0, 0, 0, 0, 0};
  graph[10] =
      (int[]){0, 0, 0, 0, 0, 0, 150, 0, 0, 130, 0, 0, 0, 70, 50, 0, 0, 0};
  graph[11] =
      (int[]){0, 0, 0, 0, 80, 0, 100, 0, 0, 0, 0, 0, 0, 150, 0, 0, 0, 0};
  graph[12] =
      (int[]){70, 0, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 80, 120, 0};
  graph[13] =
      (int[]){
        0, 0, 0, 0, 200, 0, 120, 0, 0, 0, 70, 150, 0, 0, 0, 0, 0, 0};
  graph[14] =
      (int[]){0, 135, 0, 0, 0, 0, 0, 260, 0, 0, 50, 0, 0, 0, 0, 0, 0, 0};
  graph[15] = (int[]){0, 0, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 80, 0, 0, 0, 0, 0};
  graph[16] =
      (int[]){0, 0, 100, 140, 0, 0, 0, 0, 150, 0, 0, 0, 120, 0, 0, 0, 0, 110};
  graph[17] =
      (int[]){100, 0, 0, 0, 0, 80, 0, 0, 80, 0, 0, 0, 0, 0, 0, 0, 110, 0};
  
  dijkstra(graph, 2);
  
  return 0;
}

int minDistance(int *distance, int *visited) {
  int min = INT_MAX, min_index;
  for (int v = 0; v < NUM_VERTICES; v++) {
    if (visited[v] == 0 && distance[v] <= min) {
      min = distance[v];
      min_index = v;
    }
  }
  return min_index;
}

void printPath(int *parent, int j) {
  if (parent[j] == -1)
    return;

  printPath(parent, parent[j]);

  printf("%d\t", j + 1);
}

void printSolution(int *distance, int *parent, int source) {
  printf("Distância do vértice %d para os outros vértices:\n", source + 1);
  for (int i = 0; i < NUM_VERTICES; i++) {
    if (i == source)
      continue;
    printf("Vértice %d - Distância: %d - Caminho:\t %d\t", i + 1, distance[i],
           source + 1);
    printPath(parent, i);
    printf("\n");
  }
}

void dijkstra(int **graph, int source) {
  source -= 1;
  int *distance = (int *)malloc(sizeof(int) * NUM_VERTICES);
  int *visited = (int *)malloc(sizeof(int) * NUM_VERTICES);
  int *parent = (int *)malloc(sizeof(int) * NUM_VERTICES);

  for (int i = 0; i < NUM_VERTICES; i++) {
    distance[i] = INT_MAX;
    visited[i] = 0;
    parent[i] = -1;
  }

  distance[source] = 0;

  for (int count = 0; count < NUM_VERTICES - 1; count++) {
    int u = minDistance(distance, visited);
    visited[u] = 1;

    for (int v = 0; v < NUM_VERTICES; v++) {
      if (!visited[v] && graph[u][v] && distance[u] != INT_MAX &&
          distance[u] + graph[u][v] < distance[v]) {
        distance[v] = distance[u] + graph[u][v];
        parent[v] = u;
      }
    }
  }

  printSolution(distance, parent, source);

  free(distance);
  free(visited);
  free(parent);
}