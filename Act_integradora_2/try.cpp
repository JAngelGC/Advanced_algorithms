#include <iostream>
#include <vector>
#include <limits>
#include <iterator>
#include <map>

using namespace std;

void tsp(vector<vector<int>> graph)
{
    int sizeGraph = graph.size();
    cout << "SIZE GRAPH: " << sizeGraph << endl;

    map<int, bool> nodesVisited;
    for (int i = 0; i < sizeGraph; i++)
    {
        nodesVisited[i] = false;
    }

    int curNode = 0;
    int nextNode;
    vector<int> bestPath;
    bestPath.push_back(curNode + 1);
    nodesVisited[curNode] = true;

    int counter = 0;
    while (counter < sizeGraph - 1)
    {
        int bestNextNode = numeric_limits<int>::max();
        for (int i = 0; i < 4; i++)
        {
            if (curNode != i && graph[curNode][i] < bestNextNode && nodesVisited[i] == false)
            {
                bestNextNode = graph[curNode][i];
                nextNode = i;
            }
        }
        bestPath.push_back(nextNode + 1);
        nodesVisited[nextNode] = true;
        curNode = nextNode;
        counter++;
        cout << "counter: " << counter << endl;
    }

    // now we have to return to the first node

    bestPath.push_back(0 + 1);

    for (auto x : bestPath)
    {
        cout << x << " - ";
    }
    cout << endl;
}

int main()
{

    int n;
    cin >> n;

    vector<vector<int>> graph;

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

    tsp(graph);

    return 0;
}
