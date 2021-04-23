#include "ArgumentManager.h"
#include "Comparator.h"
#include "Graph.h"
#include "Partition.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>

using std::cout;    using std::endl;

typedef typename Graph<int>::Vertex Vertex;
typedef typename Graph<int>::Edge Edge;

typedef typename Partition<int>::Position Position;

std::string quality = "Good";
int time;
std::vector<int> locations;

template <typename T>
void BFS(const Graph<T>& G, Vertex* s) {
    for (Vertex* v : G.V) {
        v->color = WHITE;
        v->d = -1;
        v->pre = nullptr;
    }
    s->color = GRAY;
    s->d = 0;
    s->pre = nullptr;
    queue<Vertex*> Q;
    Q.push(s);
    while (!Q.empty()) {
        Vertex* u = Q.front(); Q.pop();
        vector<Edge*> I = u->incidentEdges();
        // max adjacent vertices of vertex u > 2
        if (I.size() > 2) locations.push_back(**u);
        for (size_t i = 0; i < I.size(); i++) {
            Vertex* v = I[i]->opposite(u);
            if (v->color == WHITE) {
                v->color = GRAY;
                v->d = u->d + 1;
                v->pre = u;
                Q.push(v);
            }
        }
        u->color = BLACK;
        //cout << **u << " -> ";
    }
}

template <typename T>
void printPath(const Graph<T>& G, Vertex* s, Vertex* v) {
    if (v == s)
        cout << **s << " ";
    else if (v->pre == nullptr)
        cout << "no path ";
    else {
        printPath(G, s, v->pre);
        cout << **v << " ";
    }
}

template <typename T>
void DFS(const Graph<T>& G) {
    for (Vertex& v : G.V) {
        v.color = WHITE;
        v.pre = nullptr;
    }
    time = 0;
    for (Vertex& v : G.V) {
        if (v.color == WHITE)
            DFS(G, v);
    }
}

template <typename T>
void DFSVisit(const Graph<T>& G, Vertex* u) {
    time += 1;
    u->d = time;
    u->color = GRAY;
    vector<Edge*> I = u->incidentEdges();
    for (size_t i = 0; i < I.size(); i++) {
        Vertex* v = I[i]->opposite(u);
        if (v->color == WHITE) {
            v->pre = u;
            DFSVisit(G, v);
        }
    }
    u->color = BLACK;
    time += 1;
    u->f = time;
}

template <typename T>
vector<Edge*> kruskal(const Graph<T>& G) {
    vector<Edge*> MST;
    Partition<Vertex*> P;
    // Partition all vertices
    for (size_t i = 0; i < G.V.size(); i++) {
        P.makeSet(G.V[i]);
    }
    // Sort edges from least to most weight
    priority_queue<Edge*, vector<Edge*>, Comparator<T>> pque;
    for (size_t i = 0; i < G.E.size(); i++)
        pque.push(G.E[i]);
    // Search edges
    while (!pque.empty()) {
        Edge* e = pque.top(); pque.pop();
        vector<Vertex*> in = e->endVertices();
        if (P.findSet(in[0]) != P.findSet(in[1])) {
            MST.push_back(e);
            P.makeUnion(in[0], in[1]);
        }
    }
    return MST;
}

int main(int argc, char** argv) {
    ArgumentManager am(argc, argv);
    std::ifstream ifs(am.get("input"));
    std::ofstream ofs(am.get("output"));

    Graph<int> G;

    int n;
    ifs >> n;
    for (int i = 0; i < n; i++) {
        G.insertVertex(i);
    }
    std::string input;
    std::stringstream ss;
    int u, v, w;
    while (std::getline(ifs, input)) {
        if (input.size() == 0) continue;
        ss.clear();
        ss << input;
        ss >> u >> v >> w;
        G.insertEdge(G.V[u], G.V[v], w);
    }

    // Case 1 (all vertices are connected?)
    BFS(G, G.V[0]);
    bool connected = true;
    for (Vertex* v : G.V) {
        if (v->color == WHITE) {
            connected = false;
            break;
        }
    }
    ofs << "1. " << (connected ? "Yes" : "No") << "\n";
    
    if (connected) {
        // Case 2 (adjacent vertices/locations)
        ofs << "2. ";
        int l = locations.size();
        if (l > 0) {
            ofs << "Yes (";
            for (size_t i = 0; i < l - 1; i++) {
                ofs << "Location " << locations[i] << ", ";
            }
            ofs << "Location " << locations[l-1] << ")\n";
        }
        else {
            ofs << "No\n";
            quality = "Fair";
        }

        // Case 3 (MST & SPT)
        ofs << "3. ";
        BFS(G, G.V[4]);
        cout << **G.V[4] << " " << **G.V[0] << endl;
        printPath(G, G.V[0], G.V[4]);
        // MST
        vector<Edge*> MST = kruskal(G);
        int total_weight = 0;
        for (size_t i = 0; i < MST.size(); i++)
            total_weight += MST[i]->weight;
        ofs << "(MST=" << total_weight << ", ";
        
    }
    else {
        quality = "Bad";
    }

    // Vertex* v0 = G.insertVertex(0);
    // Vertex* v1 = G.insertVertex(1);
    // Vertex* v2 = G.insertVertex(2);
    // Vertex* v3 = G.insertVertex(3);
    // Vertex* v4 = G.insertVertex(4);
    // Edge* e1 = G.insertEdge(v0, v1, 5);
    // Edge* e2 = G.insertEdge(v0, v2, 3);
    // Edge* e3 = G.insertEdge(v1, v2, 7);
    // Edge* e4 = G.insertEdge(v1, v3, 9);
    // Edge* e5 = G.insertEdge(v2, v4, 3);
    // Edge* e6 = G.insertEdge(v3, v4, 4);

    //printPath(G, G.V[2], G.V[3]);

    ofs << quality;

    ofs.flush();
    ofs.close();
    ifs.close();
    return 0;
}