#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Time complexity: O(n)
// Where: n = length of coin denominations
vector<int> changeGreedy(int target, int coins[], int size)
{

    // Create a vector to store the coin combination
    vector<int> changeCoins;

    for (int i = 0; i < size; i++)
    {
        // Check how many coins
        int coinNumber = target / coins[i];

        // Update target
        target = target - (coinNumber * coins[i]);

        // Add to the vector
        changeCoins.push_back(coinNumber);
    }

    return changeCoins;
}

// Time complexity: O(n * m^2)
// Where: m = targetChange / n = length of coin denominations
vector<int> changeDP(int target, int arr[], int sizeArr, map<int, vector<int>> &memo)
{

    // Check if we have already evaluate that target
    for (auto item : memo)
    {
        if (item.first == target)
        {
            return item.second;
        }
    }

    // Base case when there is possible a combination for that target
    if (target == 0)
    {
        // Initiliaze a vector with a flag of 0
        vector<int> vec;
        vec.push_back(0);
        return vec;
    }

    // Base case when there is no possible combination for that target
    if (target < 0)
    {
        // Initiliaze a vector with a flag of -1
        vector<int> vec;
        vec.push_back(-1);
        return vec;
    }

    // Initiliaze a vector with a flag of 0 for the shortest combination
    vector<int> shortestCombination;
    shortestCombination.push_back(-1);

    for (int i = 0; i < sizeArr; i++)
    {
        // Call recursively the function with the remainder
        int remainder = target - arr[i];
        vector<int> remainderResult = changeDP(remainder, arr, sizeArr, memo); // This will store the combination

        // Check the flag of the vector. Check if there is a possible combination
        if (remainderResult.at(0) != -1)
        {
            // Add the coin to the combination
            remainderResult.push_back(arr[i]);

            // Check the shortest combination
            if (shortestCombination.at(0) == -1 || remainderResult.size() < shortestCombination.size())
            {
                shortestCombination = remainderResult;
            }
        }
    }

    // Store the shortest combination for that target
    memo[target] = shortestCombination;
    return shortestCombination;
}

vector<int> formatCoins(int arrDenominations[], int sizeDenominations, vector<int> changeCoins)
{
    // Create a vector for the result
    vector<int> resultChange(sizeDenominations, 0);

    int i = 0; // Index for the coins
    int j = 0; // Index for the denominations

    while (i < changeCoins.size() - 1 && sizeDenominations > j)
    {

        if (arrDenominations[j] == changeCoins[i])
        {
            i++;
            resultChange[j] += 1;
        }
        else
        {
            j++;
        }
    }

    return resultChange;
}

int main()
{

    int N; // Number of denominations
    cin >> N;

    int denominations[N];
    for (int i = 0; i < N; i++)
    {
        cin >> denominations[i];
    }

    int P; // Price product
    cin >> P;

    int Q; // Money given
    cin >> Q;

    int change = P - Q;

    // Sort given denominations
    sort(denominations, denominations + N, greater<int>());

    // Greedy output
    vector<int> coinsGreedy = changeGreedy(change, denominations, N);
    for (auto c : coinsGreedy)
    {
        cout << c << " ";
    }
    cout << endl;

    // DP output
    map<int, vector<int>> memo;
    vector<int> coinsDP = changeDP(change, denominations, N, memo);
    sort(coinsDP.begin(), coinsDP.end(), greater<int>()); // Sort coinsDP

    vector<int> coinsDPFormatted = formatCoins(denominations, N, coinsDP);

    for (auto c : coinsDPFormatted)
    {
        cout << c << " ";
    }
    cout << endl;

    return 0;
}
