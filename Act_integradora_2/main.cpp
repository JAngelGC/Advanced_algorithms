#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <stack>

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

int maxDataFlow(unordered_map<int, vector<int>> &adjlist, unordered_map<pair<int, int>, int> &weights, int firstNode, int lastNode)
{

    int maxDataFlow = 0;

    for (int node : adjlist.at(firstNode))
    {

        if (node == lastNode)
        {
            maxDataFlow = max(maxDataFlow, weights.find(make_pair(firstNode, node)));
            continue;
        }

        unordered_set<int> visited;

        visited.insert(firstNode);
        visited.insert(node);

        stack<pair<int, int>> s;
        s.push(make_pair(node, weights.find(make_pair(firstNode, node))));

        while (!s.empty())
        {
            int currentNode = mystack.top().first;
            int currMaxFlow = mystack.top().second;

            if (currentNode == lastNode)
            {
                maxDataFlow = max(maxDataFlow, currMaxFlow);
                break;
            }

            for (int neighbour : adjlist.at(currentNode))
            {

                if (visited.find(neighbour) != visited.end())
                {
                    visited.insert(neighbour);

                    int newMaxFlow = min(currMaxFlow, weights.find(currentNode, neighbour));
                    s.push(make_pair(neighbour, newMaxFlow));
                }
            }
        }
    }

    return maxDataFlow;
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> graph;
    unordered_map<pair<int, int>, int> weights
        unordered_map<int, vector<int>>
            adjlist;

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
        for (int j = 0; j < n; j++)
        {
            int w;
            cin >> w;

            if (i != j and w != 0)
            {

                pair<int, int> edge(i, j);
                weights[edge] = w;
                adjlist[i].push_back[j];
            }
        }
    }

    int maxDataFlow = maxDataFlow(adjlist, weights, 0, n - 1);

    vector<Point> centrals;
    int numberCentrals;

    for (int i = 0; i < numberCentrals; i++)
    {
        cout << "";
    }

    centrals.push_back(Point(200, 500));
    centrals.push_back(Point(300, 100));
    centrals.push_back(Point(450, 150));
    centrals.push_back(Point(520, 480));
}