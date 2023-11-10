#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
public:
    Graph(int vertices);
    void addEdge(int from, int to);
    vector<vector<int>> tarjanSCC();

private:
    int vertices;
    vector<vector<int>> adj;
    vector<int> disc;   
    vector<int> low;    
    vector<bool> onStack;  
    stack<int> s;
    int time;

    void SCC(int v, vector<vector<int>>& scc);
};

Graph::Graph(int vertices) {
    this->vertices = vertices;
    adj.resize(vertices);
    disc.resize(vertices, -1);
    low.resize(vertices, -1);
    onStack.assign(vertices, false);
    time = 0;
}

void Graph::addEdge(int from, int to) {
    adj[from].push_back(to);
}

vector<vector<int>> Graph::tarjanSCC() {
    vector<vector<int>> scc; 
    for (int i = 0; i < vertices; ++i) {
        if (disc[i] == -1) {
            SCC(i, scc);
        }
    }
    return scc;
}

void Graph::SCC(int v, vector<vector<int>>& scc) {
    disc[v] = low[v] = ++time;
    s.push(v);
    onStack[v] = true;

    for (int neighbor : adj[v]) {
        if (disc[neighbor] == -1) {
            SCC(neighbor, scc);
            low[v] = min(low[v], low[neighbor]);
        }
        else if (onStack[neighbor]) {
            low[v] = min(low[v], disc[neighbor]);
        }
    }

    if (low[v] == disc[v]) {
        vector<int> component;
        int popped;
        do {
            popped = s.top();
            s.pop();
            onStack[popped] = false;
            component.push_back(popped);
        } while (popped != v);

        scc.push_back(component);
    }
}

int main() {
    int vertices = 8;
    Graph g(vertices);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 3);
    g.addEdge(5, 4);
    g.addEdge(6, 5);
    g.addEdge(7, 6);
    g.addEdge(6, 7);

    vector<vector<int>> scc = g.tarjanSCC();

    cout << "Strongly Connected Components:\n";
    for (const vector<int>& component : scc) {
        for (int vertex : component) {
            cout << vertex << " ";
        }
        cout << endl;
    }

    return 0;
}
