#include "Trapezni.hpp"

using namespace std;

static Matrica r(double tk) {
    return Matrica(2, 1);
}

Matrica Trapezni::computeNextValue(Matrica xk, Matrica A, Matrica B, double T, double tk) {
    Matrica I = Matrica::getIdentityMatrix(A.getRows(), A.getCols());
    double T2 = T / 2.;
    double tk_1 = tk + T;

    Matrica inverz = !(I - A * T2);
    Matrica R = inverz * (I + A * T2);
    Matrica S = inverz * B * T2;

    return R * xk + S * (r(tk) + r(tk_1));
}


