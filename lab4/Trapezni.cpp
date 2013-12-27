#include "Trapezni.hpp"

using namespace std;

Matrica Trapezni::computeNextValue(Matrica xk, Matrica A, double T) {
    Matrica I = Matrica::getIdentityMatrix(A.getRows(), A.getCols());
    T = T / 2.;

    return !(I - A * T) * (I + A * T) * xk;
}
