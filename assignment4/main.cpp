#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct road {
  int i, j, cost;
  bool exist;
  road(int i, int j, int cost, bool exist) {
    this->i;
    this->j;
    this->cost;
    this->exist;
  }
};
class Union_Find {
 public:
  int parent[40], seniority[40];

  int find(int i) {
    if (parent[i] != i) {
      parent[i] = find(parent[i]);
    } else {
      return i;
    }
  }

  void link(int i, int j) {
    if (seniority[i] < seniority[j])
      parent[i] = j;
    else {
      parent[j] = i;
      if (seniority[i] == seniority[j]) {
        seniority[i]++;
      }
    }
  }

  bool Union(int i, int j) {
    int init_i = find(i);
    int init_j = find(j);

    if (init_i != init_j) {
      link(init_i, init_j);
      return true;
    }
    return false;
  }
};

int find_cost(char str) {
  int temp = str;
  if (temp >= 97) {
    return temp - 97 + 26;
  } else if (temp <= 90) {
    return temp - 66 + 26;
  }
}

vector<vector<char>> parseChar(string& str) {
  vector<vector<char>> array;
  stringstream ss(str);
  string temp;

  while (getline(ss, temp, ',')) {
    vector<char> row;
    array.push_back(row);
  }
  return array;
}

void input(string str) {
  string temp;
  stringstream ss(str);
  string cities, build, destroy;
  getline(ss, cities, ' ');
  getline(ss, build, ' ');
  getline(ss, destroy, ' ');
  vector<vector<char>> city = parseChar(cities);
  vector<vector<char>> buildCost = parseChar(build);
  vector<vector<char>> destroyCost = parseChar(destroy);
}

int main() {}