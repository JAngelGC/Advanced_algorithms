#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int getMax(vector<int> v) {
    int max = -1;
    for(int i=0; i<v.size(); i++) {
        if (v[i] > max) {
            max = v[i];
        }
    }
    return max;
}

// Assign a color to a node
// Input: Node, Vector: Colors of each node, Vector: Colors of adjacent nodes
// Output: None
// Time Complexity
void setColor(int node, vector<int>& nodeColor, vector<int>& adjColors) {
    for(int i=0; i<nodeColor.size(); i++) {
        if (count(adjColors.begin(), adjColors.end(), nodeColor[i]) == 0) {
            cout << "Using color: " << nodeColor[i] << endl;
            nodeColor[node] = nodeColor[i];
            return;
        }
    }
    cout << "New color: " << getMax(nodeColor)+1 << endl;
    nodeColor[node] = getMax(nodeColor)+1;
    return;
}

void printNodes(vector<int>& nodeColor) {
    //cout << endl << "--- Nodes Colors ---" << endl;
    for(int i=0; i<nodeColor.size(); i++) {
        cout << nodeColor[i] << " ";
    }
    cout << endl;
}

void graphColor(vector<vector<int>> G) {
    vector<int> nodeColor(G[0].size(), -1);

    // First node has first color
    nodeColor[0] = 0;

    // Check colors of each adjacent node of each node
    for(int i=1; i<G[0].size(); i++) {
        cout << "---SET NODE: " << i << "---" << endl;
        vector<int> adjColors;
        for(int j=0; j<G[0].size(); j++) {
            if (G[i][j]) {
                // Store colors of adjacencies
                adjColors.push_back(nodeColor[j]);
            }
        }
        // Give new node a color
        setColor(i, nodeColor, adjColors);
        // Print color of each node
        printNodes(nodeColor);
        cout << endl;
    }
}

int main() {


    /*
    int n = 6;
    vector<vector<int>> G = {
     { 0, 1, 1, 0, 1, 0 },
     { 1, 0, 1, 1, 0, 1 },
     { 1, 1, 0, 1, 1, 0 },
     { 0, 1, 1, 0, 0, 1 },
     { 1, 0, 1, 0, 0, 1 },
     { 0, 1, 0, 1, 1, 0 }
    };
    */

    int n = 5;
    vector<vector<int>> G = {
        { 0, 0, 1, 0, 1 },
        { 0, 0, 1, 1, 1 },
        { 1, 1, 0, 1, 0 },
        { 0, 1, 1, 0, 1 },
        { 1, 1, 0, 1, 0 }
    };


    graphColor(G);


    return 0;
}
