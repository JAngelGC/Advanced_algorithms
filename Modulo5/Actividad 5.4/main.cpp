// Program that calculates the subset with the maximun sum less or equal to an integer S
// Carlos Daniel Diaz Arrazate - A01734902
// Jose Angel Gonzalez Carrera - A01552274
// Carlos Eduardo Ruiz Lira - A01735706

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//Vectors that store the sum of the subsets 
vector<unsigned long long int> sum_A;
vector<unsigned long long int> sum_B;


// Calculate sums of every subset (Power set) in an array with backtracking
// Input: int, vector<unsigned long long int>, vector<unsigned long long int>, vector<int>
// Output: None
// Time complexity: O(2^n)
static void powerSetRecursive(int position, vector<unsigned long long int> &arr, vector<unsigned long long int> set, vector<int> &used) {
  if (position == set.size()) {
    unsigned long long int sum = 0;

    for (int i = 0; i < set.size(); i++) if (used[i]) sum += set[i];

    arr.push_back(sum);

  } else {
    // Include this element
    // The "used" vector works works as a Bitmask to know which elements of the set are included in the combination
    used[position] = 1;
    powerSetRecursive(position + 1, arr, set, used);
    // Backtrack and don't include this element
    used[position] = 0;
    powerSetRecursive(position + 1, arr, set, used);
  }
}

// Meet in the middle algorithm to the find the maximun subset
// Input: unsigned long long int, int, unsigned long long int
// Output: unsigned long long int
// Time complexity: O(2^(n/2)n).

unsigned long long int meetIntheMiddle(vector<unsigned long long int> set,int size, unsigned long long int s) {
  vector<unsigned long long int> a,b;
  vector<int> used_a,used_b;
  
  //split set in half
  
  int mid = (size-1)/2;

  for(int i = 0; i < mid; i++){
    a.push_back(set.at(i));
    used_a.push_back(0);
  }

  for(int i = mid; i < size; i++){
    b.push_back(set.at(i));
    used_b.push_back(0);
  }

  //generate sum combinations
  powerSetRecursive(0,sum_A,a,used_a);
  powerSetRecursive(0,sum_B,b,used_b);

  //sort both subsets
  sort(sum_A.begin(), sum_A.end());
  sort(sum_B.begin(),sum_B.end());

  //perfom binary search
  int left = 0;
  int right = size-1;
  unsigned long long int sum = 0;

  while(left < sum_A.size() && right >= 0){
    //the sum should be less or equal to target s
    if(sum_A[left] + sum_B[right] <= s) {
      //get maximum sum
      sum = max(sum,sum_A[left] + sum_B[right]);
      left++;
    } else {
      right--;
    }
  }

  return sum;
}


int main() {
  int size;
  vector<unsigned long long int> set;
  unsigned long long int s;

  cin >> size;
  
  for(int i = 0; i < size; i++){
    unsigned long long int num;
    cin >> num;
    set.push_back(num);
  }

  cin >> s;

  cout << meetIntheMiddle(set,size,s) << endl;

  return 0;
}