#include <bits/stdc++.h>
using namespace std;

class Point
{
public:
    int x;
    int y;
};

// Comparar dos puntos en base a su coordenada en x para hacer un sort
int compareX(const void *a, const void *b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->x - p2->x);
}

// Comparar dos puntos en base a su coordenada en y para hacer un sort
int compareY(const void *a, const void *b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->y - p2->y);
}

// Calcular distancia minima entre dos puntos
// Input: Point, Point
// Output: Distancia entre dos puntos
// Time complexity: O(1)
float hypotenuseDistance(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

// Calcular distancia minima entre puntos
// Input: Arreglo de puntos y tamaño n del mismo
// Output: Distancia minima entre los puntos
// Time complexity: O(n^2)
float bruteForce(Point P[], int n)
{
    float min = FLT_MAX;
    for (int i = 0; i < n; ++i)
    {

        for (int j = i + 1; j < n; ++j)
        {
            if (hypotenuseDistance(P[i], P[j]) < min)
            {

                min = hypotenuseDistance(P[i], P[j]);
            }
        }
    }
    return min;
}

// Encontrar numero mas pequeño entre dos
// Input: Dos float
// Output: Numero mas pequeño
// Time complexity: O(1)
float min(float x, float y)
{
    if (x < y)
        return x;
    else
        return y;
}

// Encontrar distancia mas pequeña entre un arreglo de puntos
// Input: Arreglo de puntos, tamaño del arreglo, distancia minima hasta el momento
// Output: Distancia mas pequeña entre los puntos
// Time complexity: O(n)
float stripClosest(Point strip[], int size, float d)
{
    float min = d;
    qsort(strip, size, sizeof(Point), compareY);

    // Obtener  el punto más cercano al punto medio al calcular la hipotenusa más corta
    // a la linea vertical media
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (hypotenuseDistance(strip[i], strip[j]) < min)
                min = hypotenuseDistance(strip[i], strip[j]);

    return min;
}

// Funcion recursiva para encontrar la distancia mas pequeña entre puntos
// Input: Arreglo de puntos ordenados en base a coordenada x / tamaño del arreglo n
// Output: Distancia mas pequeña entre puntos
// Time complexity: O(1)
float calcClosest(Point P[], int n)
{
    // Cuando haya menos de 3 puntos, se usa fuerza bruta para encontrar la distancia minima
    if (n <= 3)
        return bruteForce(P, n);

    int mid = n / 2;
    Point midPoint = P[mid];

    // Llamar recursivamente a la funcion para dividirla en dos subarreglos
    // Guardar la distancia minima de cada subarreglo
    float dl = calcClosest(P, mid);
    float dr = calcClosest(P + mid, n - mid);

    // Distancia mas pequeña entre ambos lados
    float d = min(dl, dr);

    // Generar un arreglo de puntos cuya distancia en x sea menor a la distancia minima guardada
    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (abs(P[i].x - midPoint.x) < d)
        {
            strip[j] = P[i], j++;
        }
    }

    // Encontrar los puntos màs cercanos a la franja vertical media
    // Calcular distancia más corta
    return min(d, stripClosest(strip, j, d));
}

float getClosest(Point P[], int n)
{
    // Ordenar puntos en base a la coordenada en x
    qsort(P, n, sizeof(Point), compareX);

    return calcClosest(P, n);
}

int main()
{
    int n;
    int x;
    int y;
    string str;
    char separator;

    getline(cin, str);
    n = stoi(str);
    Point P[n];

    // Leer entrada
    for (int i = 0; i < n; i++)
    {
        getline(cin, str);
        stringstream ss(str);
        ss >> x;
        ss >> separator;
        ss >> y;
        P[i] = {x, y};
    }

    // Obtener la distancia más corta
    cout << "The smallest distance is " << getClosest(P, n) << endl;
    return 0;
}
