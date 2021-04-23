#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

using std::vector;

enum Color {
    WHITE = 0,
    GRAY = 1,
    BLACK = 2
};

template<typename T>
class Graph {
public:
    class Vertex {
    private:
        typedef typename Graph<T>::Edge Edge;
        typedef int Position;
    public:
        Vertex(const Graph<T>& G, const T& elem);
        T& operator*() { return elem; }
        vector<Edge*> incidentEdges();

    public:
        const Graph<T>& G;
        vector<Edge*> I;
        Position p;
        T elem;
        // BFS settings
        Color color;
        Vertex* pre;
        int d;
        // DFS settings
        int f;
        // Kruskal settings

    };

public:
    class Edge {
    private:
        typedef typename Graph<T>::Vertex Vertex;
        typedef int Position;
    public:
        Edge(const Graph<T>& G, Vertex* v, Vertex* w, int weight);
        T& operator*() { return weight; }
        vector<Vertex*> endVertices();
        Vertex* opposite(Vertex* v);

    public:
        const Graph<T>& G;
        Position p;
        Position pv;
        Position pw;
        Vertex* v;
        Vertex* w;
        int weight;
    };

public:
    Vertex* insertVertex(const T& elem);
    Edge* insertEdge(Vertex* v, Vertex* w, int weight);

public:
    vector<Vertex*> V;
    vector<Edge*> E;
};

// Vertex
template <typename T>
Graph<T>::Vertex::Vertex(const Graph<T>& G, const T& elem) : G(G) {
    this->elem = elem;
}

template <typename T>
vector<typename Graph<T>::Edge*> Graph<T>::Vertex::incidentEdges() {
    return I;
}

// Edge
template <typename T>
Graph<T>::Edge::Edge(const Graph<T>& G, Vertex* v, Vertex* w, int weight) : G(G) {
    this->v = v;
    this->w = w;
    this->weight = weight;
}

template <typename T>
vector<typename Graph<T>::Vertex*> Graph<T>::Edge::endVertices() {
    vector<Vertex*> res;
    res.push_back(v);
    res.push_back(w);
    return res;
}

template <typename T>
typename Graph<T>::Vertex* Graph<T>::Edge::opposite(Vertex* v) {
    return (this->v == v ? w : this->v);
}

// Graph
template <typename T>
typename Graph<T>::Vertex* Graph<T>::insertVertex(const T& elem) {
    Vertex* v = new Vertex(*this, elem);
    v->p = V.size();
    V.push_back(v);
    return v;
}

template <typename T>
typename Graph<T>::Edge* Graph<T>::insertEdge(Vertex* v, Vertex* w, int weight) {
    Edge* e = new Edge(*this, v, w, weight);
    e->p = E.size();
    E.push_back(e);

    // Add to vertex incidence collection
    e->pv = (v->I).size();
    e->pw = (w->I).size();
    (v->I).push_back(e);
    (w->I).push_back(e);
    return e;
}

#endif