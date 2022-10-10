#include <iostream>
using namespace std;
#include <vector>
#include <limits.h>
#include <algorithm>

// Dijkstra ------------------------------------------------
// ---------------------------------------------------------

// Funcion que encuentra el nodo con menor costo en distancia
// Entrada: arreglo de nodos visitados sptSet, arreglo de distancias, numero de nodos
// Salida: indice del nodo
// Tiempo de Complejidad: O(n), donde n es el número de nodos
int findLowesCostNode(bool sptSet[], int distances[], int numNodes)
{

    int minValue = INT_MAX;
    int minIndex;

    for (int i = 0; i < numNodes; i++)
    {
        if (sptSet[i] == false && distances[i] <= minValue)
        {
            minValue = distances[i];
            minIndex = i;
        }
    }
    return minIndex;
}

// Funcion que encuentra el camino mas corto de un nodo source a todos los vertices
// Entrada: grafo como matriz de adyacencias, nodo source, numero de nodos
// Salida: nada (imprime la respuesta)
// Tiempo de Complejidad: O(n^2), donde n es el número de nodos
void dijkstra(vector<vector<int>> graph, int src, int numNodes)
{

    // Represents the set of vertices included in SPT
    bool sptSet[numNodes];

    // Represents distance from source to each node
    int distances[numNodes];

    // fill the arrays
    for (int i = 0; i < numNodes; i++)
    {
        sptSet[i] = false;
        distances[i] = INT_MAX;
    }
    distances[src] = 0;

    // Find shortest distance for each node from source
    for (int i = 0; i < numNodes - 1; i++)
    {

        // Find the index of the node with the lowest cost and which it is not in sptSet
        int idxNodeLowesCost = findLowesCostNode(sptSet, distances, numNodes);
        sptSet[idxNodeLowesCost] = true;

        // Update values of its adjacent vertices
        for (int j = 0; j < numNodes; j++)
        {

            // update if:  current node at position j
            // the node is not in sptSet, not visited yet
            // there is an edge between nodeLowestCost and current
            // the sum of distances of idxNodeLowesCost + graph[idxNodeLowesCost][j] is smaller than the current distances of node in j
            if (sptSet[j] == false &&
                graph[idxNodeLowesCost][j] != 0 &&
                graph[idxNodeLowesCost][j] != -1 &&
                distances[idxNodeLowesCost] + graph[idxNodeLowesCost][j] < distances[j])
            {

                if (distances[idxNodeLowesCost] == INT_MAX || graph[idxNodeLowesCost][j] == INT_MAX)
                {
                    continue;
                }
                else
                {

                    distances[j] = distances[idxNodeLowesCost] + graph[idxNodeLowesCost][j];
                }
            }
        }
    }

    // Print distance from source to each node
    for (int i = 0; i < numNodes; i++)
    {
        if (abs(distances[i]) == INT_MAX)
        {
            cout << "node " << src + 1 << " to node " << i + 1 << " : " << -1 << endl;
        }
        else
        {
            cout << "node " << src + 1 << " to node " << i + 1 << " : " << distances[i] << endl;
        }
    }
}

// Floyd ---------------------------------------------------
// ---------------------------------------------------------

void print(vector<vector<int>> array)
{
    cout << "Floyd:" << endl;
    for (int i = 0; i < array.size(); i++)
    {
        for (int j = 0; j < array.size(); j++)
        {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

/*
Funcion que calcla la distancia mas corta entre parejas
de nodos en un grafo dirigido, utilizando el algoritmo
de Floyd
Entrada: Una matrix NxN que representa el peso de un arco entre
los vértices i y j.
Salida: Nulo
Tiempo de Complejidad: O(n^3), donde n es el número de vertices en el grafo
*/
void floyds(vector<vector<int>> &original_array)
{

    /*
    Implementación con Programacion Dinamica. Para calcular la matriz de distancia para el
    vértice k, se debe conocer la matriz de distancia del vértice k-1
    */
    for (int k = 0; k < original_array.size(); k++)
    {
        for (int i = 0; i < original_array.size(); i++)
        {
            for (int j = 0; j < original_array.size(); j++)
            {
                /*

                El valor -1 como peso de un arco, representa que no hay nodo entre los vértices
                */
                if (original_array[i][k] == -1 || original_array[k][j] == -1)
                {
                    original_array[i][j] = original_array[i][j];
                }
                else if (original_array[i][j] == -1)
                {
                    original_array[i][j] = original_array[i][k] + original_array[k][j];
                }
                else
                {
                    // A[i,j] = min(a[])
                    original_array[i][j] = min(original_array[i][j], original_array[i][k] + original_array[k][j]);
                }
            }
        }
    }
}

int main()
{

    // Dijkstra ------------------------------------------------
    int numOfNodes;
    cin >> numOfNodes;

    vector<vector<int>> myGraph(numOfNodes, vector<int>(numOfNodes));
    for (int i = 0; i < numOfNodes; i++)
    {
        for (int j = 0; j < numOfNodes; j++)
        {
            int val;
            cin >> val;
            myGraph[i][j] = val;
        }
    }

    cout << "Dijkstra:" << endl;
    for (int i = 0; i < numOfNodes; i++)
        dijkstra(myGraph, i, numOfNodes);
    cout << endl;

    // Floyd ------------------------------------------------
    floyds(myGraph);
    print(myGraph);

    return 0;
}

// 0 4 -1 -1 -1 -1 -1 8 -1
// 4 0 8 -1 -1 -1 -1 11 -1
// -1 8 0 7 -1 4 -1 -1 2
// -1 -1 7 0 9 14 -1 -1 -1
// -1 -1 -1 9 0 -1 -1 -1 -1
// -1 -1 4 14 -1 0 2 -1 -1
// -1 -1 -1 -1 -1 2 0 1 6
// 8 11 -1 -1 -1 -1 1 0 7
// -1 -1 2 -1 -1 -1 6 7 0
