#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

string school_sub(string n1, string n2, int base) {
  // Get larger of two numbers (n1 is larger of the two)

  // reverse strings
  reverse(n1.begin(), n1.end());
  reverse(n2.begin(), n2.end());

  // get difference and adding zero to smaller
  int difference = n1.length() - n2.length();
  for (int i = 0; i < difference; i++) {
    n2.push_back('0');
  }

  // for loop to add individual numbers
  string total;
  int borrowed = 0;

  for (int i = 0; i < n1.length(); i++) {
    if (borrowed == 1) {
      n1[i] = n1[i] - 1;
    }
    borrowed = 0;
    if (n1[i] < n2[i]) {
      borrowed = 1;
      n1[i] = n1[i] + base;
    }
    int curr_total = n1[i] - n2[i];

    total = to_string(curr_total) + total;
  }

  return total;
}

int main() {
  string n1, n2;
  int base = 0;
  cin >> n1 >> n2 >> base;

  string sub = school_sub(n1, n2, base);

  cout << sub << "\n";
}