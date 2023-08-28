#include <cmath>
#include <iostream>
#include <string>
using namespace std;

string school_add(string n1, string n2, int base) {
  // reverse strings
  reverse(n1.begin(), n1.end());
  reverse(n2.begin(), n2.end());

  // Get larger of two numbers (n1 is larger of the two)
  if (n1.length() < n2.length()) {
    swap(n1, n2);
  }

  // get difference and adding zero to smaller
  int difference = n1.length() - n2.length();
  for (int i = 0; i < difference; i++) {
    n2.push_back('0');
  }

  // for loop to add individual numbers
  string sum;
  int carry = 0;
  
  for (int i = 0; i < n1.length(); i++) {
    int curr_sum = (n1[i] - '0') + (n2[i] - '0') + carry;
    carry = 0;
    if (curr_sum >= base && i != (n1.length() - 1)) {
      carry = 1;
      curr_sum = curr_sum % base;
    } else {
      carry = 0;
    }

    if (curr_sum == 2 && base == 2){
      curr_sum = 10;
    }
    sum = to_string(curr_sum) + sum;
  }

  return sum;
};

int karatsuba_mult(int n1, int n2, int base) {

};

int main() {
  string n1, n2;
  int base = 0;
  cout << "Sample input: ";
  cin >> n1 >> n2 >> base;
  string sum = school_add(n1, n2, base);
  // int prod = karatsuba_mult(n1, n2, base);
  //  cout << n1 << " " << n2 << " " << 0 << "\n";
  cout << sum << " " << 0 << " " << 0 << "\n";
}
