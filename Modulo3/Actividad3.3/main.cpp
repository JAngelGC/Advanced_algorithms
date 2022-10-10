// Programa que resuelve el problema de la mochila usando programación dinámica
// Carlos Daniel Diaz Arrazate - A01734902
// Jose Angel Gonzalez Carrera - A01552274
// Carlos Eduardo Ruiz Lira - A01735706
// 02/10/2022

#include <iostream>
using namespace std;

// Complejidad temporal: O(N*W), donde N: numero de elementos y W: tamaño maximo de la mochila
// Entradas: N valores y N pesos, W peso maximo que aguanta la mochila
// Salida: Ganancia (o beneficio) óptimo
int main()
{

    // Recibiendo valores
    int N;
    cin >> N;
    int values[N + 1];
    values[0] = 0;
    for (int i = 1; i < N + 1; i++)
    {
        cin >> values[i];
    }

    // Recibiendo pessos
    int weights[N + 1];
    weights[0] = 0;
    for (int i = 1; i < N + 1; i++)
    {
        cin >> weights[i];
    }

    // Capacidad de la mochila
    int capacity;
    cin >> capacity;

    // Creacion de matriz para progra dinamica
    int mtx[N + 1][capacity + 1];
    for (int i = 0; i < N + 1; i++)
        for (int j = 0; j < capacity + 1; j++)
            mtx[i][j] = 0;

    int maxProfit = 0;

    // Recorrer la matriz
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= capacity; j++)
        {

            // Valor maximo previo de la mochila con peso maximo de j
            int prevMax = mtx[i - 1][j];
            int maxValWithCurr = 0;

            int weightCurr = weights[i];

            // Verificar que el peso quepa en la mochila
            if (j >= weightCurr)
            {
                maxValWithCurr = values[i];

                // Checar si se puede guardar algo mas en la mochila
                int remainingCapacity = j - weightCurr;
                maxValWithCurr += mtx[i - 1][remainingCapacity];
            }

            // Actualizar el valor de la matriz
            if (maxValWithCurr > prevMax)
                mtx[i][j] = maxValWithCurr;

            else
                mtx[i][j] = prevMax;

            // Actualizar el valor de la maxima ganancia
            if (mtx[i][j] > maxProfit)
                maxProfit = mtx[i][j];
        }
    }

    cout << endl;
    cout << maxProfit << endl;

    return 0;
}
