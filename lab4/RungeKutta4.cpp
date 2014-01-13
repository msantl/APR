#include "RungeKutta4.hpp"

using namespace std;

Matrica RungeKutta4::computeNextValue(Matrica xk, Matrica A, Matrica B, double T) {
    Matrica I = Matrica::getIdentityMatrix(A.getRows(), A.getCols());

    double T2 = T / 2.;

    Matrica m1 = A * xk + B ;
    Matrica m2 = A * (xk + m1 * T2) + B;
    Matrica m3 = A * (xk + m2 * T2) + B;
    Matrica m4 = A * (xk + m3 * T) + B;

    return xk + (m1 + m2 * 2 + m3 * 2 + m4) * (T / 6.);
}
