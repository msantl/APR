#include <cmath>

#include "Funkcija.hpp"

using namespace std;

Funkcija::Funkcija() {
}

void Funkcija::setOffsetVector(vector<double> &p) {
    _p = p;
}

/* functions defined in problem statement */

double Funkcija_F3::operator() (vector<double> x) {
    double ret = 0;
    for (int i = 0; i < x.size(); ++i) {
        ret += pow(x[i] - _p[i], 2);
    }
    return ret;
}

double Funkcija_F4::operator() (vector<double> x) {
    return
        fabs((x[0] - x[1]) * (x[0] + x[1])) +
        pow(pow(x[0], 2) + pow(x[1], 2), 0.5);
}

double Funkcija_F6::operator() (vector<double> x) {
    double ret = 0;
    int N = 3;

    for (int i = 0; i < N; ++i) {
        ret += x[i] * x[i];
    }

    return 0.5 + (pow(sin(sqrt(ret)), 2.) - 0.5) / (pow(1 + 0.001 * ret, 2.));
}

double Funkcija_F7::operator() (vector<double> x) {
    double ret = 0;
    int N = 3;

    for (int i = 0; i < N; ++i) {
        ret += x[i] * x[i];
    }

    return pow(ret, 0.25) * (pow(sin(50 * pow(ret, 0.1)), 2.) + 1.0);
}
