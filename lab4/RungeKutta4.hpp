#pragma once

#include "Matrica.hpp"

class RungeKutta4 {
    public:

    static Matrica computeNextValue(Matrica xk, Matrica A, double T);

};

