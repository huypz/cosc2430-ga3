#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "Graph.h"

template <typename T>
class Comparator {
    private:
        typedef typename Graph<T>::Edge Edge;
    public:
        bool operator()(const Edge* e, const Edge* f) { 
            return e->weight > f->weight; 
        }
};
#endif