// Smallest convex polygon - Graham's Scan
// Carlos Daniel Diaz Arrazate - A01734902
// Jose Angel Gonzalez Carrera - A01552274
// Carlos Eduardo Ruiz Lira - A01735706
#include <iostream>
#include <vector>
#include <stack>
#include <stdlib.h>

using namespace std;

struct Point
{
    int x;
    int y;

    Point()
    {
        x = 0;
        y = 0;
    }

    Point(int pX, int pY)
    {
        x = pX;
        y = pY;
    }
};

Point p0;

// A utility function to find next to top in a stack
Point nextToTop(stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

// Calcular distancia
// Input: Point, Point
// Output: Distancia entre dos puntos
// Time complexity: O(1)
int distSq(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) +
           (p1.y - p2.y) * (p1.y - p2.y);
}

// Calcular orientacion
// Input: Point, Point, Point
// Output: Orientacion
// Time complexity: O(1)
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    // Collinear
    if (val == 0)
    {
        return 0;
    }

    // Clockwise
    else if (val > 0)
    {
        return 1;
    }
    // Counterclockwise
    else
    {
        return 2;
    }
}

// Determinar que punto es mas grande en cuanto a angulo
// Input: Point, Point
// Output: Bool para determinar que punto es mas grande
// Time complexity: O(1)
int comparePoints(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    // Definir la orientacion
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        if (distSq(p0, *p2) >= distSq(p0, *p1))
        {
            return -1;
        }
        else
        {
            return 1;
        }
    if (o == 2)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

// Determinar el poligono convexo mas pequeno que contiene a todos los puntos
// Input: Vector -> points
// Output: Points -> que determinan la circuferencia del poligono
// Time complexity: O(n*log(n))
void calcularPoligono(vector<Point> coordinates)
{

    int sizeVector = coordinates.size();

    // Encontrar el punto mas bajo
    int min_y = coordinates[0].y;
    int min_index = 0;
    for (int currIndex = 1; currIndex < sizeVector; currIndex++)
    {
        int curr_y = coordinates[currIndex].y;

        // Si los valores en y son los mismos, obtener valor en x mas bajo
        if ((curr_y < min_y) || (min_y == curr_y && coordinates[currIndex].x < coordinates[min_index].x))
        {
            min_y = coordinates[currIndex].y;
            min_index = currIndex;
        }
    }

    // Colocar el punto mas bajo al inicio del vector
    Point tmp = coordinates[0];
    coordinates[0] = coordinates[min_index];
    coordinates[min_index] = tmp;

    // Ordenar los puntos dependiendo del angulo
    // Un punto es mas grande que otro si tiene un angulo mas grande que el otro
    p0 = coordinates[0];
    qsort(&coordinates[1], sizeVector - 1, sizeof(Point), comparePoints);

    int sizeModifiedVector = 1;
    for (int i = 1; i < sizeVector; i++)
    {
        // Ignorar vertices que forman una linea recta
        while (i < sizeVector - 1 && orientation(p0, coordinates[i], coordinates[i + 1]) == 0)
        {
            i++;
        }
        coordinates[sizeModifiedVector] = coordinates[i];
        sizeModifiedVector++;
    }

    stack<Point> S;
    S.push(coordinates[0]);
    S.push(coordinates[1]);
    S.push(coordinates[2]);
    // Procesar n-3 points
    for (int i = 3; i < sizeModifiedVector; i++)
    {
        // Mientras el angulo este hacias las manecillas del reloj, remover vertice previo
        while (orientation(nextToTop(S), S.top(), coordinates[i]) != 2)
            S.pop();
        S.push(coordinates[i]);
    }

    // Imprimir poligono
    while (!S.empty())
    {
        Point p = S.top();
        cout << p.x << " " << p.y << endl;
        S.pop();
    }
}

int main()
{
    vector<Point> coordinates;
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int x;
        int y;
        cin >> x >> y;
        coordinates.push_back(Point(x, y));
    }

    calcularPoligono(coordinates);

    cout << endl;
}
