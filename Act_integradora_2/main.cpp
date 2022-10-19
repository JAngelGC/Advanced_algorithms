#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <limits.h>

using namespace std;

struct Point
{
    int x;
    int y;

    Point(int pX, int pY)
    {
        x = pX;
        y = pY;
    }
};

// Get distance between two points
// Input: Int, int, int, int
// Output: Float
// Time Complexity: O(1)
float getDistance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

// Get central closes to a point
// Input: Vector of centrals, point
// Output: Index of central
// Time Complexity: O(N)
void closestCentral(vector<Point> centrals, Point point)
{
    // Random distance to be able to compare distances
    // cout << "Size: " << centrals.size() << endl;
    float newDistance;
    int closestNode = 0;
    float minDistance = centrals[0].x * centrals[0].y;
    for (int i = 0; i < centrals.size(); i++)
    {
        newDistance = getDistance(point.x, point.y, centrals[i].x, centrals[i].y);
        // cout << centrals[i].x << "," << centrals[i].y << " = " << newDistance << endl;
        // cout << "    " << newDistance << " < " << minDistance << " ? ";
        if (newDistance < minDistance)
        {
            closestNode = i;
            minDistance = newDistance;
        }
    }

    cout << "Closest node: " << closestNode << " with values: " << centrals[closestNode].x << ", " << centrals[closestNode].y << endl;
    // return closestNode;
}

void maxDataFlow(int &maxData, int currentNode, int lastNode, int currentMaxFlow, unordered_set<int> &visited, vector<vector<int>> &weights, unordered_map<int, vector<int>> &adjlist)
{
    visited.insert(currentNode);
    if (currentNode == lastNode)
    {
        maxData = max(maxData, currentMaxFlow);
    }
    else
    {
        for (int neighbour : adjlist.at(currentNode))
        {
            if (visited.find(neighbour) == visited.end())
            {
                int newMaxFlow = min(currentMaxFlow, weights[currentNode][neighbour]);
                maxDataFlow(maxData, neighbour, lastNode, newMaxFlow, visited, weights, adjlist);
            }
        }
    }
    visited.erase(currentNode);
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> graph;
    vector<vector<int>> weights;
    unordered_map<int, vector<int>> adjlist;

    for (int i = 0; i < n; i++)
    {
        vector<int> row;
        for (int j = 0; j < n; j++)
        {
            int val;
            cin >> val;
            row.push_back(val);
        }
        graph.push_back(row);
    }

    for (int i = 0; i < n; i++)
    {

        vector<int> row;
        for (int j = 0; j < n; j++)
        {
            int w;
            cin >> w;
            if (i != j and w != 0)
                adjlist[i].push_back(j);

            row.push_back(w);
        }
        weights.push_back(row);
    }

    int maxData = 0;
    unordered_set<int> visited;
    maxDataFlow(maxData, 0, n - 1, INT_MAX, visited, weights, adjlist);

    cout << maxData << endl;

    // Cemtral mas cercana a nuevos nodos
    string str;
    int x, y;
    char sep;
    int numberCentrals;
    vector<Point> centrals;
    vector<Point> newCentrals;

    // Ubicacion de centrales
    cin >> numberCentrals;
    for (int i = 0; i < numberCentrals; i++)
    {
        cin >> str;
        str = str.substr(1, str.size() - 2);
        stringstream ss(str);
        ss >> x;
        ss >> sep;
        ss >> y;
        centrals.push_back(Point(x, y));
    }

    // Nuevas centrales
    cin >> numberCentrals;
    for (int i = 0; i < numberCentrals; i++)
    {
        cin >> str;
        str = str.substr(1, str.size() - 2);
        stringstream ss(str);
        ss >> x;
        ss >> sep;
        ss >> y;
        newCentrals.push_back(Point(x, y));
    }

    // Calcular central mas cercana para cada nodo
    for (int i = 0; i < newCentrals.size(); i++)
    {
        closestCentral(centrals, newCentrals[i]);
    }

    // centrals.push_back(Point(200, 500));
    // centrals.push_back(Point(300, 100));
    // centrals.push_back(Point(450, 150));
    // centrals.push_back(Point(520, 480));

    // 0,0
    // 400,400
}