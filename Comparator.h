#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "Graph.h"

template <typename T>
class Comparator {
    private:
        typedef typename Graph<T>::Edge Edge;
        typedef typename Graph<T>::Vertex Vertex;
    public:
        bool operator()(Edge* e, Edge* f) { 
            return e->weight > f->weight; 
        }
        bool operator()(Vertex* u, Vertex* v) {
            return u->d < v->d;
        }
};
#endif