// Programa que resuelve un laberinto | Backtracking & Branch and bound
// Carlos Daniel Diaz Arrazate - A01734902
// Jose Angel Gonzalez Carrera - A01552274
// Carlos Eduardo Ruiz Lira - A01735706
// 28/08/2022

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Function to create a 2D array
// Time complexity: O(n*m)
// m: width of array, n: height of array
// array2D: Two-dimensional array
int **create2DArray(int M, int N)
{
    int **array2D = 0;
    array2D = new int *[M];

    for (int i = 0; i < M; i++)
    {
        array2D[i] = new int[N];

        for (int j = 0; j < N; j++)
        {
            array2D[i][j] = 0;
        }
    }

    return array2D;
}

// Function to check if there is a 1 in the position and if is in the matrix range
// Time complexity: O(1)
// x & y: position, m & n: size of matrix, mtx: matrix
// bool: if position is safe or not
bool isSafe(int x, int y, int M, int N, int **mtx)
{
    if (x >= 0 && x < M && y >= 0 && y < N && mtx[x][y] == 1)
    {
        return true;
    }
    return false;
}

//
//
// Backtracking
//
//

// Function to solve using backtracking
// Time complexity:  O(2^(n^2))
// x: position in X, y: position in Y, M: width of array, M: height of array, mtx: initial matrix, out: output matrix
// return if there is a solution
bool solveMazeBack(int x, int y, int M, int N, int **mtx, int **out)
{
    // Check if we have arrived to the destination
    if (x == M - 1 && y == N - 1 && mtx[x][y] == 1)
    {
        out[x][y] = 1;
        return true;
    }

    if (isSafe(x, y, M, N, mtx) == true)
    {

        // Check if we already have visited that position
        if (out[x][y] == 1)
            return false;

        // Mark as visited the new position
        out[x][y] = 1;

        // Move down
        if (solveMazeBack(x, y + 1, M, N, mtx, out))
            return true;

        // Move to the right
        if (solveMazeBack(x + 1, y, M, N, mtx, out))
            return true;

        // Move up
        if (solveMazeBack(x, y - 1, M, N, mtx, out))
            return true;

        // Move to the left
        if (solveMazeBack(x - 1, y, M, N, mtx, out))
            return true;

        // If the movement wasn't safe, the we backtrack the position as unmarked
        out[x][y] = 0;
        return false;
    }
    return false;
}

// Function that prints the solution if there is a solution by using backtracking
// Time complexity:  O(2^(n^2) + n*m)
// M: width of array, M: height of array, mtx: initial matrix given by the user
void solveByBacktracking(int M, int N, int **mtx)
{

    int **out = create2DArray(M, N);

    if (solveMazeBack(0, 0, M, N, mtx, out))
    {
        cout << endl;

        // Print the solution
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cout << out[i][j] << " ";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "There is no solution possible using backtracking" << endl;
    }
}

//
// Branch and bound
//
struct Node
{
    int posX;
    int posY;
    Node *prev;
};

// Function to create a node
Node *createNode(int x, int y, Node *prev)
{

    struct Node *newNode = new Node;
    newNode->posX = x;
    newNode->posY = y;
    newNode->prev = prev;

    return newNode;
}

// Function to print the answer using branch and bound
void print(struct Node *head, int M, int N)
{
    int **outMtx = create2DArray(M, N);

    while (head != NULL)
    {
        outMtx[head->posX][head->posY] = 1;
        head = head->prev;
    }

    // Print the solution
    cout << endl;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << outMtx[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
}

// Function to solve using branch and bound
// Time complexity:  O(n*m)
// M: width of array, M: height of array, mtx: initial matrix, out: output matrix, myQueue: queue to save all the possible nodes
// return if there is a solution
bool solveMazeBB(int M, int N, int **mtx, int **out, queue<Node **> myQueue)
{

    Node *arr[M * N * M];
    vector<Node *> myVector;
    int count = 0;

    while (!myQueue.empty())
    {
        struct Node *curNode = *myQueue.front();
        int posX = curNode->posX;
        int posY = curNode->posY;

        myQueue.pop(); // We pop the current node

        // Check if we have arrived to the destination
        if (posX == M - 1 && posY == N - 1 && mtx[posX][posY] == 1)
        {
            out[posX][posY] = 1;
            print(curNode, M, N);
            return true;
        }

        // Check if we already have visited that position
        if (out[posX][posY] == 1)
        {
            continue;
        }

        // Mark as visited the new position
        out[posX][posY] = 1;

        // To the right
        if (isSafe(posX + 1, posY, M, N, mtx) == true)
        {
            arr[count] = createNode(posX + 1, posY, curNode);
            myQueue.push(&arr[count]);
            count++;
        }

        // To down
        if (isSafe(posX, posY + 1, M, N, mtx) == true)
        {

            arr[count] = createNode(posX, posY + 1, curNode);
            myQueue.push(&arr[count]);
            count++;
        }

        // To the left
        if (isSafe(posX - 1, posY, M, N, mtx) == true)
        {

            arr[count] = createNode(posX - 1, posY, curNode);
            myQueue.push(&arr[count]);
            count++;
        }

        // To up
        if (isSafe(posX, posY - 1, M, N, mtx) == true)
        {

            arr[count] = createNode(posX, posY - 1, curNode);
            myQueue.push(&arr[count]);
            count++;
        }
    }

    cout << "There is no solution possible for branch and bound" << endl;
    return false;
}

// Function to initialize the solveByBB with arguments
void solveByBranchBound(int M, int N, int **mtx)
{

    int **out = create2DArray(M, N);

    queue<Node **> myQueue;
    struct Node *head = new Node;
    head->posX = 0;
    head->posY = 0;
    head->prev = NULL;

    myQueue.push(&head);

    solveMazeBB(M, N, mtx, out, myQueue);
}

int main()
{

    int M;
    cin >> M;

    int N;
    cin >> N;

    int **iniMtx = create2DArray(M, N);
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> iniMtx[i][j];
        }
    }

    solveByBacktracking(M, N, iniMtx);
    solveByBranchBound(M, N, iniMtx);

    return 0;
}
