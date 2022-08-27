#include <iostream>
using namespace std;

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

bool isSafe(int x, int y, int M, int N, int **mtx)
{
    if (x >= 0 && x < M && y >= 0 && y < N && mtx[x][y] == 1)
    {
        return true;
    }
    return false;
}

bool solveMaze(int x, int y, int M, int N, int **mtx, int **out)
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

        // Move to the right
        if (solveMaze(x + 1, y, M, N, mtx, out))
        {
            return true;
        }

        // Move down
        if (solveMaze(x, y + 1, M, N, mtx, out))
        {
            return true;
        }

        // Move to the left
        if (solveMaze(x - 1, y, M, N, mtx, out))
        {
            return true;
        }

        // Move up
        if (solveMaze(x, y - 1, M, N, mtx, out))
        {
            return true;
        }

        // If the movement wasn't safe, the we backtrack the position as unmarked
        out[x][y] = 0;
        return false;
    }
    return false;
}

void solve(int M, int N, int **mtx)
{

    int **out = create2DArray(M, N);

    if (solveMaze(0, 0, M, N, mtx, out))
    {
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
        cout << "There is no solution possible" << endl;
    }
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

    solve(M, N, iniMtx);

    return 0;
}
