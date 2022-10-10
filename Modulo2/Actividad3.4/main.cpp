#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Get maximum value in a vector
// Input: Vector
// Output: Maximum value
// Time Complexity: O(n)
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
// Time Complexity: O(n*m)
void setColor(int node, vector<int>& nodeColor, vector<int>& adjColors) {
    // Check used colors that arent used in adjacent nodes
    for(int i=0; i<nodeColor.size(); i++) {
        // If a color is avaliable then give new node that color
        if (count(adjColors.begin(), adjColors.end(), nodeColor[i]) == 0) {
            //cout << "Using color: " << nodeColor[i] << endl;
            nodeColor[node] = nodeColor[i];
            return;
        }
    }
    // All colors collide, create a new color
    //cout << "New color: " << getMax(nodeColor)+1 << endl;
    nodeColor[node] = getMax(nodeColor)+1;
    return;
}

// Prints all nodes in a vector
// Input: Vector
// Output: None
// Time Complexity: O(n)
void printNodes(vector<int>& nodeColor) {
    //cout << endl << "--- Nodes Colors ---" << endl;
    for(int i=0; i<nodeColor.size(); i++) {
        cout << "Node: " << i << ", Assigned Color: " << nodeColor[i] << endl;
    }
}

// Assign colors to a graph without repetitions in adjacent nodes
// Input: Adjacency matrix
// Output: None
// Time Complexity: O(n)
void graphColor(vector<vector<int>> G) {

    // Vector that stores the color of each node
    vector<int> nodeColor(G[0].size(), -1);

    // First node has the first color
    nodeColor[0] = 0;

    // Check colors of each adjacent node of each node
    for(int i=1; i<G[0].size(); i++) {
        //cout << "---SET NODE: " << i << "---" << endl;
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
    }
    printNodes(nodeColor);
    cout << endl;
}


int main() {


    int n;
    int tmp;
    vector<vector<int>> G;
    cin >> n;
    for(int i=0; i<n; i++) {
        vector<int> row;
        for(int j=0; j<n; j++) {
            cin >> tmp;
            row.push_back(tmp);
        }
        G.push_back(row);
    }

    graphColor(G);


    return 0;
}
