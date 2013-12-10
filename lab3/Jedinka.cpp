#include "Jedinka.hpp"

#include <cassert>
#include <cmath>
#include <ctime>

using namespace std;

Jedinka::Jedinka() : _length (0), _dimension(0), _lower_bound(0), _upper_bound(0), _precision(0) {
}

Jedinka::Jedinka(int dimension, int precision, int lower_bound, int upper_bound) : _dimension(dimension), _precision(precision), _lower_bound(lower_bound), _upper_bound(upper_bound) {
    /* compute the dimension using precision, lower and upper bound */
    double power = 1.;
    while (precision--) power *= 10.;

    _length = ceil(log2(1 + (upper_bound - lower_bound) * power));

    /* make sure the length fits in a 32bit integer */
    assert(_length < 32);

    /* reserve space needed */
    _b.resize(dimension);

    /* create a new random unit */
    for (int i = 0; i < dimension; ++i) {
        double value = lower_bound + (rand() / (1. * RAND_MAX)) * (upper_bound - lower_bound);
        this->setFloatByIndex(i, value);
    }
}

int Jedinka::getBinaryByIndex(int index) const {
    assert(index >= 0 && index < _dimension);
    return _b[index];
}

double Jedinka::getFloatByIndex(int index)  const {
    assert(index >= 0 && index < _dimension);
    return this->_convert_to_float(_b[index]);
}

void Jedinka::setBinaryByIndex(int index, int value) {
    assert(index >= 0 && index < _dimension);
    _b[index] = value;
}

void Jedinka::setFloatByIndex(int index, int value) {
    assert(index >= 0 && index < _dimension);
    _b[index] = this->_convert_to_binary(value);
}

int Jedinka::getLength(void) const {
    return _length;
}

int Jedinka::getDimension(void) const {
    return _dimension;
}

int Jedinka::_convert_to_binary(double num) const {
    return ((1 << _length) - 1.) * (num - _lower_bound) / (_upper_bound - _lower_bound);
}

double Jedinka::_convert_to_float(int num) const {
    return _lower_bound + num * (_upper_bound - _lower_bound) / ((1 << _length) - 1.);
}

