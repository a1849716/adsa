#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int minCost() {}

int prim(vector<int>){

};

vector<vector<char> > parseChar(string& str) {
  vector<vector<char> > array;
  stringstream ss(str);
  string temp;
  int i = 0;
  while (getline(ss, temp, ',')) {
    vector<char> row(temp.begin(), temp.end());
    array.push_back(row);
  }
  return array;
}

void input(string str) {
  string temp;
  stringstream ss(str);
  string cities, build, destroy;
  getline(ss, cities, ' ');
  cout << cities << endl;
  getline(ss, build, ' ');
  cout << build << endl;
  getline(ss, destroy, ' ');
  cout << destroy << endl;
  vector<vector<char> > city = parseChar(cities);
  vector<vector<char> > buildCost = parseChar(build);
  vector<vector<char> > destroyCost = parseChar(destroy);
  /*
  int index = 0;
  cout << "Build Matrix:" << endl;
  for (const auto& row : city) {
    cout << "row " << index << " :";
    for (char val : row) {
      cout << val << ' ';
    }
    index++;
    cout << endl;
  }

  index = 0;
  cout << "Build Matrix:" << endl;
  for (const auto& row : buildCost) {
    cout << "row " << index << " :";
    for (char val : row) {
      cout << val << ' ';
    }
    index++;
    cout << endl;
  }

  index = 0;
  cout << "Build Matrix:" << endl;
  for (const auto& row : destroyCost) {
    cout << "row " << index << " :";
    for (char val : row) {
      cout << val << ' ';
    }
    index++;
    cout << endl;
  }
  */
}

int main() {
  string cmd;
  getline(cin, cmd);
  input(cmd);
}