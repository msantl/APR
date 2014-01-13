#include "Trapezni.hpp"

using namespace std;

Matrica Trapezni::computeNextValue(Matrica xk, Matrica A, Matrica B, double T) {
    Matrica I = Matrica::getIdentityMatrix(A.getRows(), A.getCols());
    double T2 = T / 2.;

    Matrica inverz = !(I - A * T2);
    Matrica R = inverz * (I + A * T2);
    Matrica S = inverz * B * T;

    return R * xk + S;
}


