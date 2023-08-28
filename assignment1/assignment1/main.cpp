#include <algorithm>
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

    if (curr_sum == 2 && base == 2) {
      curr_sum = 10;
    }
    sum = to_string(curr_sum) + sum;
  }

  return sum;
};

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
    int curr_total = (n1[i] - '0') - (n2[i] - '0');

    total = to_string(curr_total) + total;
  }

  return total;
}

string karatsuba_mult(string n1, string n2, int base) {
  // Base case
  string final = "0";

  if (n1.length() <= 4 && n2.length() <= 4) {
    for (int i = 0; i < stoi(n2, nullptr, base); i++) {
      final = school_add(final, n1, base);
    }
    return final;
  }

  // Get larger of two numbers (n1 is larger of the two)
  if (n1.length() < n2.length()) {
    swap(n1, n2);
  }

  int difference = n1.length() - n2.length();
  for (int i = 0; i < difference; i++) {
    n2 = "0" + n2;
  }
  // seperate strings
  string a = n1.substr(0, n1.length() / 2);
  cout << "a " << a << endl;
  string b = n1.substr(n1.length() / 2);
  cout << "b " << b << endl;
  string c = n2.substr(0, n2.length() / 2);
  cout << "c " << c << endl;
  string d = n2.substr(n2.length() / 2);
  cout << "d " << d << endl;

  // a+b and c+d
  string ab = school_add(a, b, base);
  cout << "ab " << ab << endl;
  string cd = school_add(c, d, base);
  cout << "cd " << cd << endl;

  // find ac
  string ac = karatsuba_mult(a, c, base);
  cout << "ac " << ac << endl;

  // find bd
  string bd = karatsuba_mult(b, d, base);
  cout << "bd " << bd << endl;

  // find (a+b)(c+d)
  string abANDcd = karatsuba_mult(ab, cd, base);
  cout << "abANDcd " << abANDcd << endl;

  // find ad+bc
  string z0 = school_sub(abANDcd, ac, base);
  string z1 = school_sub(z0, bd, base);

  // add zeros ac
  for (int i = 0; i < ceil(float(n1.length()) / 2) * 2; i++) {
    ac.push_back('0');
  }
  cout << "ac: " << ac << endl;
  // add zeros z1
  for (int i = 0; i < ceil((float)n1.length() / (float)2); i++) {
    z1.push_back('0');
  }
  cout << "z1: " << z1 << endl;

  string temp_sum = school_add(ac, bd, base);
  string sum = school_add(temp_sum, z1, base);

  while (sum[0] == '0') {
    sum = sum.substr(1);
  }

  return sum;
};

int main() {
  string n1, n2;
  int base = 0;
  cout << "Sample input: ";
  cin >> n1 >> n2 >> base;
  string sum = school_add(n1, n2, base);
  string sub = school_sub(n1, n2, base);
  string prod = karatsuba_mult(n1, n2, base);
  // cout << n1 << " " << n2 << " " << 0 << "\n";
  cout << sum << " " << prod << " " << 0 << "\n";
}
