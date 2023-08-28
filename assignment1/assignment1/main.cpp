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
  if (n1.size() < n2.size()) {
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
    carry = curr_sum / base;
    curr_sum %= base;
    sum = to_string(curr_sum) + sum;
  }

  // Adding remaining carry
  if (carry != 0) {
    sum = to_string(carry) + sum;
  }

  while (sum[0] == '0' && sum.size() > 1) {
    sum = sum.substr(1);
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
    int curr_total = n1[i] - n2[i];

    total = to_string(curr_total) + total;
  }
  while (total[0] == '0' && total.size() > 1) {
    total = total.substr(1);
  }
  return total;
}

string karatsuba_mult(string n1, string n2, int base) {
  // Base case
  string final = "0";
  if (n1.length() == 1 && n2.length() == 1) {
    // cout <<"n1: " << n1 <<" n2: "<<n2[0]-'0'<<endl;
    for (int i = 0; i < n2[0] - '0'; i++) {
      final = school_add(final, n1, base);
    }
    // cout <<"final: "<<final<<endl;
    return final;
  }

  // Get larger of two numbers (n1 is larger of the two)
  if (n1.length() < n2.length()) {
    swap(n1, n2);
  }

  // pad
  int difference = n1.length() - n2.length();
  for (int i = 0; i < difference; i++) {
    n2 = "0" + n2;
  }

  int n = max(n1.size(), n2.size());

  int mid = n / 2;

  // seperate strings
  string a = n1.substr(0, n - mid);
  string b = n1.substr(n - mid);
  string c = n2.substr(0, n - mid);
  string d = n2.substr(n - mid);

  // a+b and c+d
  string ab = school_add(a, b, base);
  // cout << "ab: " << ab << endl;
  string cd = school_add(c, d, base);

  // find ac
  string ac = karatsuba_mult(a, c, base);
  // find bd
  string bd = karatsuba_mult(b, d, base);
  // find (a+b)(c+d)
  string middle = karatsuba_mult(ab, cd, base);

  // find ad+bc
  string z0 = school_sub(middle, ac, base);
  string z1 = school_sub(z0, bd, base);

  // add zeros ac
  for (int i = 0; i < mid*2; i++) {
    ac.push_back('0');
  }
  // add zeros z1
  for (int i = 0; i < mid; i++) {
    z1.push_back('0');
  }

  // cout << "a: " << a << endl;
  // cout << "b: " << b << endl;
  // cout << "c: " << c << endl;
  // cout << "d: " << d << endl;
  // cout << "cd: " << cd << endl;
  // cout << "ac: " << ac << endl;
  // cout << "bd: " << bd << endl;
  // cout << "abANDcd: " << abANDcd << endl;
  // cout << "ad+bc: " << z1 << endl;
  // cout << "ac after 0: " << ac << endl;
  // cout << "z1 after 0: " << z1 << endl;

  string temp_sum = school_add(ac, bd, base);
  string sum = school_add(temp_sum, z1, base);

  while (sum[0] == '0' && sum.size() > 1) {
    sum = sum.substr(1);
  }
  // cout << "sum after 0: " << sum << endl;

  return sum;
};

int main() {
  string n1, n2;
  int base = 0;
  cin >> n1 >> n2 >> base;
  string sum = school_add(n1, n2, base);
  string prod = karatsuba_mult(n1, n2, base);
  cout << sum << " " << prod << " " << 0;
}
