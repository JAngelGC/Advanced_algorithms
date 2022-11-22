#include <iostream>
#include <vector>

using namespace std;

vector<long> sum_A;
vector<long> sum_B;


static void powerSetRecursive(int position, vector<long> &arr, vector<long> set, vector<int> &used) {
  if (position == set.size()) {
    long sum = 0;

    for (int i = 0; i < set.size(); i++) if (used[i]) sum += set[i];

    arr.push_back(sum);

  } else {
    // Include this element
    used[position] = 1;
    powerSetRecursive(position + 1, arr, set, used);
    // Backtrack and don't include this element
    used[position] = 0;
    powerSetRecursive(position + 1, arr, set, used);
  }
}

int main() {
  vector<long> set = {1,2,3};

  vector<long> a;
  vector<long> b;
  vector<int> used_a;
  vector<int> used_b;

  int mid = (set.size()-1)/2;

  for(int i = 0; i < mid; i++){
    a.push_back(set[i]);
    used_a.push_back(0);
  }

  for(int i = mid; i < set.size(); i++){
    b.push_back(set[i]);
    used_b.push_back(0);
  }

  powerSetRecursive(0,sum_A,a,used_a);
  powerSetRecursive(0,sum_B,b,used_b);

  for(auto num : sum_A){
    cout << num << endl;
  }
  cout << "-------"<< endl;
  for(auto num : sum_B){
    cout << num << endl;
  }
}