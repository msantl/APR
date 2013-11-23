#include "Vector.hpp"

#include <vector>

using namespace std;

vector< double > mul(double c, const vector< double > &x) {
    vector< double > ret = x;
    for (int i = 0; i < (int)x.size(); ++i) {
        ret[i] *= c;
    }
    return ret;
}

vector< double > sub(const vector< double > &x, const vector< double > &y) {
    vector< double > ret = x;
    for (int i = 0; i < (int)x.size(); ++i) {
        ret[i] -= y[i];
    }
    return ret;
}

vector< double > asub(const vector< double > &x, const vector< double > &y) {
    vector< double > ret = x;
    for (int i = 0; i < (int)x.size(); ++i) {
        ret[i] -= y[i];
        if (ret[i] < 0) ret[i] = -ret[i];
    }
    return ret;
}

vector< double > add(const vector< double > &x, const vector< double > &y) {
    vector< double > ret = x;
    for (int i = 0; i < (int)x.size(); ++i) {
        ret[i] += y[i];
    }
    return ret;
}

bool lt(const vector< double > &x, double c) {
    for (int i = 0; i < (int)x.size(); ++i) {
        if (x[i] >= c) return false;
    }
    return true;
}
