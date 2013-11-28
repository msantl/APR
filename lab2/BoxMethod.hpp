#pragma once

#include "Function.hpp"
#include "Vektor.hpp"

Vektor<double> BoxMethod(Vektor<double> x, double a, double eps, Function &f);
