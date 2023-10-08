/// @file
#pragma once

#include <cassert>
#include <vector>

using namespace std;

namespace aclext {
// <---
// name: Grid
struct PointDelta {
    int di, dj;
    PointDelta(int di, int dj) :
        di(di), dj(dj) { }
    PointDelta operator+(PointDelta other) const {
        return PointDelta(di + other.di, dj + other.dj);
    }
    PointDelta operator*(int c) const {
        return PointDelta(di * c, dj * c);
    }
};

const PointDelta U = { -1, 0 };
const PointDelta R = { 0, 1 };
const PointDelta D = { 1, 0 };
const PointDelta L = { 0, -1 };
const PointDelta UR = U + R;
const PointDelta DR = D + R;
const PointDelta DL = D + L;
const PointDelta UL = U + L;

struct Point {
    int i, j;
    Point(int i, int j) :
        i(i), j(j) { }
    Point operator+(PointDelta pd) const {
        return Point(i + pd.di, j + pd.dj);
    }
};

class BoundedGridSpec {
    int n, m;

public:
    using P = Point;
    BoundedGridSpec(int n, int m) :
        n(n), m(m) { }
    int size() const {
        return n * m;
    }
    bool in_grid(P p) const {
        return 0 <= p.i and p.i < n and 0 <= p.j and p.j < m;
    }
    int id(P p) const {
        assert(in_grid(p));
        return p.i * m + p.j;
    }
};

template <typename T, typename S>
class Grid {
    vector<T> array;
    S spec;

public:
    Grid(S spec) :
        array(spec.size()), spec(spec) { }
    T& operator[](const typename S::P& p) {
        return array[spec.id(p)];
    }
    const T& operator[](const typename S::P& p) const {
        return array[spec.id(p)];
    }
    bool in_grid(const typename S::P& p) const {
        return spec.in_grid(p);
    }
};
// --->
}