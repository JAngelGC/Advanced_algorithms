#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <limits.h>
#include <iterator>
#include <map>
#include <limits>
#include <sstream>
#include <string>

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

    cout << closestNode << endl;
}

// Shortest possible route to connect all neighborhoods
// Input: (list) adjecency list of neighborhoods
// Output: Shortest possible route that visits each neighborhoods exactly once
// Time Complexity: O(V^2)
void tspCable(vector<vector<int>> graph)
{
    int sizeGraph = graph.size();

    // Initialize nodesVisited
    map<int, bool> nodesVisited;
    for (int i = 0; i < sizeGraph; i++)
        nodesVisited[i] = false;

    int curNode = 0;
    int nextNode = 1;

    vector<vector<int>> bestPath;
    nodesVisited[curNode] = true;

    int counter = 0;
    while (counter < sizeGraph - 1)
    {
        int bestNextNode = numeric_limits<int>::max();
        for (int i = 0; i < sizeGraph; i++)
        {
            // check for the cheapest neighborhood
            if ((curNode != i) && (graph[curNode][i] < bestNextNode) && (nodesVisited[i] == false))
            {
                bestNextNode = graph[curNode][i];
                nextNode = i;
            }
        }

        // push that neighborhood to the best path and mark it as visited
        vector<int> edge;
        edge.push_back(curNode + 1);
        edge.push_back(nextNode + 1);
        bestPath.push_back(edge);

        nodesVisited[nextNode] = true;
        curNode = nextNode;
        counter++;
    }

    // from the last node, return back to the

    // printing shortest path
    for (int i = 0; i < sizeGraph - 1; i++)
    {
        cout << "(" << bestPath[i][0] << ", " << bestPath[i][1] << ")";
    }

    cout << endl;
}

// Shortest possible route
// Input: (list) adjecency list of neighborhoods
// Output: Shortest possible route that visits each neighborhoods exactly once and returns to the start
// Time Complexity: O(V^2)
void tsp(vector<vector<int>> graph)
{
    map<int, string> myMap;
    myMap[1] = "A";
    myMap[2] = "B";
    myMap[3] = "C";
    myMap[4] = "D";
    myMap[5] = "E";
    myMap[6] = "F";
    myMap[7] = "G";
    myMap[8] = "H";
    myMap[9] = "I";
    myMap[10] = "J";

    int sizeGraph = graph.size();

    // Initialize nodesVisited
    map<int, bool> nodesVisited;
    for (int i = 0; i < sizeGraph; i++)
        nodesVisited[i] = false;

    int curNode = 0;
    int nextNode = 1;

    vector<int> bestPath;
    bestPath.push_back(curNode + 1);
    nodesVisited[curNode] = true;

    int counter = 0;
    while (counter < sizeGraph - 1)
    {
        int bestNextNode = numeric_limits<int>::max();
        for (int i = 0; i < sizeGraph; i++)
        {
            // check for the cheapest neighborhood
            if ((curNode != i) && (graph[curNode][i] < bestNextNode) && (nodesVisited[i] == false))
            {
                bestNextNode = graph[curNode][i];
                nextNode = i;
            }
        }

        // push that neighborhood to the best path and mark it as visited
        bestPath.push_back(nextNode + 1);
        nodesVisited[nextNode] = true;
        curNode = nextNode;
        counter++;
    }

    // from the last node, return back to the
    bestPath.push_back(0 + 1);

    // printing shortest path
    for (auto x : bestPath)
        cout << myMap[x] << " -> ";
    cout << endl;
}

// Get max data flow from any two neigborhoods (Backtracking)
// Input:  (int) max data flow, (int) current visited neighborhood,
//         (int) max data flow for a specific path, (set) visited neighborhoods,
//         (list) list of data flow between two neighborhoods,
//         (list) adjecency list of neighborhoods
// Time Complexity: O(V*(V+E))
void maxDataFlow(int &maxData, int currentNode, int lastNode, int currentMaxFlow, unordered_set<int> &visited, vector<vector<int>> &weights, unordered_map<int, vector<int>> &adjlist)
{
    visited.insert(currentNode);
    if (currentNode == lastNode)
    {
        // reaching the last neighborhood
        maxData = max(maxData, currentMaxFlow);
    }
    else
    {
        for (int neighbour : adjlist.at(currentNode))
        {
            if (visited.find(neighbour) == visited.end())
            {
                // The max data flow of a path is limited by the slowest node in the network (Bottleneck)
                int newMaxFlow = min(currentMaxFlow, weights[currentNode][neighbour]);
                maxDataFlow(maxData, neighbour, lastNode, newMaxFlow, visited, weights, adjlist);
            }
        }
    }

    // When reaching last visited Node, backtrack
    visited.erase(currentNode);
}

int main()
{

    int n;
    cin >> n;

    vector<vector<int>> graph;
    vector<vector<int>> weights;
    unordered_map<int, vector<int>> adjlist;

    // Reading distances between neighborhoods
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

    // Reading data flow between neighborhoods
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

    // THIRD QUESTION
    int maxData = 0;
    unordered_set<int> visited;
    maxDataFlow(maxData, 0, n - 1, INT_MAX, visited, weights, adjlist);

    // FOURTH QUESTION
    string str;
    int x, y;
    char sep;
    int numberCentrals;
    vector<Point> centrals;
    vector<Point> newCentrals;

    // // Ubicacion de centrales existentes
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

    // Ubicacion de nuevas centrales
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

    // OUTPUT
    cout << endl;
    cout << "---PRINTING OUTPUT---" << endl;

    // FIRST QUESTION
    tspCable(graph);
    cout << endl;

    // SECOND QUESTION
    tsp(graph);
    cout << endl;

    // THIRD QUESTION
    cout << maxData << endl
         << endl;

    // FOURTH QUESTION
    for (int i = 0; i < newCentrals.size(); i++)
    {
        closestCentral(centrals, newCentrals[i]);
    }

<<<<<<< HEAD
    // 0,0
    // 400,400
}
=======
    return 0;
}
>>>>>>> 41f7d99 (Actividad integral 2 finished)
