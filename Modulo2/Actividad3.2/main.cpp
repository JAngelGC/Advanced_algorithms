#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void print(vector<vector<int>> array){
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
void floyds(vector<vector<int>> &original_array){

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
                if(original_array[i][k] == -1 || original_array[k][j] == -1){
                    original_array[i][j] = original_array[i][j];
                } else if (original_array[i][j] == -1) {
                    original_array[i][j] = original_array[i][k] + original_array[k][j];
                } else {
                    // A[i,j] = min(a[])
                    original_array[i][j] = min(original_array[i][j], original_array[i][k] + original_array[k][j]);
                }               
            }
        }
    }
}

int main(){
    int n;

    cin >> n;

    vector<vector<int>> arr;

    for (int i = 0; i < n; i++)
    {
        vector<int> row;
        for (int j = 0; j < n; j++)
        {
            int val;
            cin >> val;
            row.push_back(val);
        }
        arr.push_back(row);
    }

    floyds(arr);

    print(arr);
}