#include "Jedinka.hpp"

#include <cassert>
#include <cmath>
#include <ctime>

using namespace std;

static double round_double(double val, int prec) {
    char buff[64], cmd[8];
    double ret = val;

    sprintf(cmd, "%%.%dlf", prec);
    sprintf(buff, cmd, val);
    sscanf(buff, "%lf", &ret);

    return ret;
}

Jedinka::Jedinka() :
    _dimension(0),
    _lower_bound(0),
    _upper_bound(0),
    _precision(0) {
}

Jedinka::Jedinka(int dimension, int precision, int lower_bound, int upper_bound) :
    _dimension(dimension),
    _precision(precision),
    _lower_bound(lower_bound),
    _upper_bound(upper_bound) {

    /* reserve space needed */
    _b.resize(dimension);

    /* create a new random unit */
    for (int i = 0; i < dimension; ++i) {
        double value = lower_bound + (rand() / (1. * RAND_MAX)) * (upper_bound - lower_bound);
        this->setFloatByIndex(i, value);
    }
}

Jedinka::~Jedinka() {
}

double Jedinka::getFloatByIndex(int index)  const {
    assert(index >= 0 && index < _dimension);
    return _b[index];
}

void Jedinka::setFloatByIndex(int index, double value) {
    assert(index >= 0 && index < _dimension);
    _b[index] = value;
}

int Jedinka::getDimension(void) const {
    return _dimension;
}

int Jedinka::getDG(void) const {
    return _lower_bound;
}

int Jedinka::getGG(void) const {
    return _upper_bound;
}
