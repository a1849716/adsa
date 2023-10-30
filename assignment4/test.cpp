#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Structure to represent an edge with its cost
struct Edge {
    int u, v, cost;
};

// Custom comparison function for sorting edges
bool compareEdges(const Edge& a, const Edge& b) {
    return a.cost < b.cost;
}

// Function to find the root of a set using path compression
int find(vector<int>& parent, int x) {
    if (parent[x] == x)
        return x;
    parent[x] = find(parent, parent[x]);
    return parent[x];
}

// Function to perform union of two sets using union by rank
void unionSets(vector<int>& parent, vector<int>& rank, int u, int v) {
    int rootU = find(parent, u);
    int rootV = find(parent, v);

    if (rootU != rootV) {
        if (rank[rootU] < rank[rootV])
            swap(rootU, rootV);
        parent[rootV] = rootU;
        if (rank[rootU] == rank[rootV])
            rank[rootU]++;
    }
}

// Function to calculate the minimal cost for road network reconstruction
int reconstructRoadNetwork(const vector<string>& country, const vector<string>& build, const vector<string>& destroy) {
    int N = country.size();
    vector<Edge> edges;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            char c = country[i][j];
            if (c == '1') {
                char build_cost = build[i][j];
                int cost = build_cost - 'A'; // Convert character to cost
                edges.push_back(Edge());
                edges.back().u = i;
                edges.back().v = j;
                edges.back().cost = cost;
            }
            else {
                char destroy_cost = destroy[i][j];
                int cost = destroy_cost - 'A'; // Convert character to cost
                edges.push_back(Edge());
                edges.back().u = i;
                edges.back().v = j;
                edges.back().cost = -cost;
            }
        }
    }

    sort(edges.begin(), edges.end(), compareEdges);

    vector<int> parent(N);
    vector<int> rank(N, 0);
    for (int i = 0; i < N; i++) {
        parent[i] = i;
    }

    int totalCost = 0;
    int components = N;

    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int cost = edges[i].cost;

        int rootU = find(parent, u);
        int rootV = find(parent, v);

        if (rootU != rootV) {
            unionSets(parent, rank, u, v);
            totalCost += abs(cost);
            components--;
        }

        if (components == 1)
            break;
    }

    return totalCost;
}

int main() {
    vector<string> country;
    country.push_back("000");
    country.push_back("000");
    country.push_back("000");

    vector<string> build;
    build.push_back("ABD");
    build.push_back("BAC");
    build.push_back("DCA");

    vector<string> destroy;
    destroy.push_back("ABD");
    destroy.push_back("BAC");
    destroy.push_back("DCA");

    int result = reconstructRoadNetwork(country, build, destroy);
    cout << "Minimal cost for road network reconstruction: " << result << endl;

    return 0;
}
