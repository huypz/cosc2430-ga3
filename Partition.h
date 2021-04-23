#ifndef PARTITION_H
#define PARTITION_H

#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class Partition {
    public:
        class Position {
            public:
                T& operator*() { return elem; }
                friend class Partition;
            public:
                Position(const T& elem);
                T elem;
                Position* p;
                int n;
        };
    public:
        Position* makeSet(const T& elem);
        Position* makeUnion(Position* A, Position* B);
        Position* makeUnion(T A, T B);
        Position* findSet(Position* pos);
        Position* findSet(T e);

    public:
        std::vector<Position*> sequences;

};

// Position
template <typename T>
Partition<T>::Position::Position(const T& elem) {
    this->elem = elem;
    p = this;
    n = 1;
}

// Partition
template <typename T>
typename Partition<T>::Position* Partition<T>::makeSet(const T& elem) {
    Position* root = new Position(elem);
    sequences.push_back(root);
    return root;
}

template <typename T>
typename Partition<T>::Position* Partition<T>::makeUnion(Position* A, Position* B) {
    if (A->n < B->n) {
        A->p = &(*B);
        B->n += A->n;
        return B;
    }
    else {
        B->p = &(*A);
        A->n += B->n;
        return A;
    }
}

template <typename T>
typename Partition<T>::Position* Partition<T>::makeUnion(T A, T B) {
    Position* APos = findSet(A);
    Position* BPos = findSet(B);
    return makeUnion(APos, BPos);
}

template <typename T>
typename Partition<T>::Position* Partition<T>::findSet(Position* pos) {
    if (pos->p == &(*pos))
        return pos;
    else
        return (pos->p = findSet(pos->p));
}

template <typename T>
typename Partition<T>::Position* Partition<T>::findSet(T e) {
    Position* ePos = nullptr;
    for (size_t i = 0; i < sequences.size(); i++) {
        Position* p = sequences[i];
        if (**p == e) ePos = p;
        if (ePos != nullptr) break;
    }
    //cout << **ePos << " " << **ePos->p  << endl;
    return findSet(ePos);
}
#endif