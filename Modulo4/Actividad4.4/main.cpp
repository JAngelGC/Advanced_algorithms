#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void randomizedBinarySearch(vector<int> nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;
    bool found = false;

    while (left <= right)
    {
        // random number inclusive
        int randNum = rand() % (right - left + 1) + left;

        if (nums[randNum] == target)
        {
            cout << "El elemento esta presente en el indice: " << randNum << endl;
            found = true;
            break;
        }

        if (nums[randNum] > target)
            right = randNum - 1;

        else
            left = randNum + 1;
    }
    if (!found)
        cout << "El elemento no esta presente en el arreglo" << endl;
}

int main()
{
    int target;
    string tmp;
    string input;

    // Input target value
    getline(cin, tmp);
    target = stoi(tmp);

    // Input vector values
    vector<int> nums;
    getline(cin, input);

    // Parse input into vector of ints
    stringstream ss(input);
    string token;
    while (getline(ss, token, ','))
    {
        nums.push_back(stoi(token));
    }

    randomizedBinarySearch(nums, target);

    return 0;
}
