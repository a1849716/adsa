#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct edge {
  int i, j, cost;
  bool exists;
  edge() {}
  edge(int i, int j, int cost, bool exists) {
    this->i = i;
    this->j = j;
    this->cost = cost;
    this->exists = exists;
  }
};

class UnionFind {
  int parent[55], seniority[55];

 public:
  int Find(int i) {
    if (parent[i] != i) {
      parent[i] = Find(parent[i]);
    }
    return parent[i];
  }
  void MakeSet(int i) {
    parent[i] = i;
    seniority[i] = 0;
  }

  void Link(int i, int j) {
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
    int root_i = Find(i);
    int root_j = Find(j);

    if (root_i != root_j) {
      cout << "Union(" << i << ", " << j << "): Link(" << root_i << ", "
           << root_j << ")" << endl;
      Link(root_i, root_j);
      return true;
    }
    cout << "Already in the same set. i: " << i << " j: " << j << endl;
    return false;
  }
};

bool cmp(const edge& a, const edge& b) {
  if (a.exists && !b.exists) {
    return true;
  } else if (!a.exists && b.exists) {
    return false;
  } else if (a.exists && b.exists) {
    return a.cost > b.cost;
  }
  return a.cost < b.cost;
}

class country_cities {
 private:
  vector<vector<int> > country;
  vector<vector<char> > build;
  vector<vector<char> > destroy;

 public:
  country_cities(){};
  country_cities(vector<vector<int> > country, vector<vector<char> > build,
                 vector<vector<char> > destroy) {
    this->country = country;
    this->build = build;
    this->destroy = destroy;
  };

  int cost(char ch) {
    if ('A' <= ch && ch <= 'Z')
      return ch - 'A';
    else
      return ch - 'a' + 26;
  }

  int getCost(vector<vector<int> > country, vector<vector<char> > build,
              vector<vector<char> > destroy) {
    vector<edge> Roads;
    int n = country.size();
    for (int i = 0; i < n; i++)
      for (int j = 0; j < i; j++)
        if (country[i][j] == 1)
          Roads.push_back(edge(i, j, cost(destroy[i][j]), true));
        else
          Roads.push_back(edge(i, j, cost(build[i][j]), false));
    UnionFind S;
    for (int i = 0; i < n; i++) {
      S.MakeSet(i);
    }
    vector<edge>::iterator vit;
    int total_cost = 0;

    sort(Roads.begin(), Roads.end(), cmp);
    for (vit = Roads.begin(); vit != Roads.end(); vit++) {
      cout << "evaluating road from: " << vit->i << " to: " << vit->j
           << " with cost: " << vit->cost << endl;
      if (S.Find(vit->i) != S.Find(vit->j)) {
        S.Union(vit->i, vit->j);
        if (country[vit->i][vit->j] == 0) {
          total_cost += vit->cost;
          cout << "road from: " << vit->i << " to: " << vit->j << " is added"
               << endl;

        } else {
          cout << "Road from " << vit->i << " to " << vit->j
               << " already exists." << endl;
        }
      } else {
        if (country[vit->i][vit->j] == 1) {
          cout << "road from: " << vit->i << " to: " << vit->j << " is removed"
               << endl;
          total_cost += vit->cost;
        }
      }
    }
    return total_cost;
  }
};

vector<vector<int> > parseCity(const string& str) {
  vector<vector<int> > matrix;
  stringstream ss(str);
  string token;

  while (getline(ss, token, ',')) {
    vector<int> row;
    for (char c : token) {
      row.push_back(c - '0');
    }
    matrix.push_back(row);
  }

  return matrix;
}

vector<vector<char> > parseCosts(const string& str) {
  vector<vector<char> > matrix;
  stringstream ss(str);
  string token;

  while (getline(ss, token, ',')) {
    vector<char> row(token.begin(), token.end());
    matrix.push_back(row);
  }

  return matrix;
}

int main() {
  string input;
  getline(cin, input);
  stringstream ss(input);
  string citymatrix, buildmatrix, destroymatrix;
  getline(ss, citymatrix, ' ');
  getline(ss, buildmatrix, ' ');
  getline(ss, destroymatrix);
  vector<vector<int> > country = parseCity(citymatrix);
  vector<vector<char> > build = parseCosts(buildmatrix);
  vector<vector<char> > destroy = parseCosts(destroymatrix);

  class country_cities test(country, build, destroy);
  int index = 0;
  /*cout << "Country Matrix:" << endl;
  for (const auto& row : country) {
    cout << "row " << index << " :";
    for (int val : row) {
      cout << val << ' ';
    }
    index++;
    cout << endl;
  }
  index = 0;
  cout << "Build Matrix:" << endl;
  for (const auto& row : build) {
    cout << "row " << index << " :";
    for (char val : row) {
      cout << val << ' ';
    }
    index++;
    cout << endl;
  }
  index = 0;
  cout << "Destroy Matrix:" << endl;
  for (const auto& row : destroy) {
    cout << "row " << index << " :";
    for (char val : row) {
      cout << val << ' ';
    }
    index++;
    cout << endl;
  }*/
  int result = test.getCost(country, build, destroy);
  cout << result << endl;

  return 0;
}