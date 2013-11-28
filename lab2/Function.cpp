#include <cmath>

#include "Function.hpp"

Function::Function() {
}

void Function::setOffsetVector(Vektor<double> &p) {
    _p = p;
}

/* functions defined in problem statement */

double Function_F1::operator() (Vektor<double> &x) {
    return 10 * pow(pow(x[0], 2) - x[1], 2) + pow(1 - x[0], 2);
}

double Function_F2::operator() (Vektor<double> &x) {
    return pow(x[0] - 4, 2) + 4 * pow(x[1] - 2, 2);
}

double Function_F3::operator() (Vektor<double> &x) {
    double ret = 0;
    for (int i = 0; i < x.size(); ++i) {
        ret += pow(x[i] - _p[i], 2);
    }
    return ret;
}

double Function_F4::operator() (Vektor<double> &x) {
    return
        fabs((x[0] - x[1]) * (x[0] + x[1])) +
        pow(pow(x[0], 2) + pow(x[1], 2), 0.5);
}
