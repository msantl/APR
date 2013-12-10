#pragma once

#include "Jedinka.hpp"
#include "Funkcija.hpp"

#include <vector>

std::vector<double> GenetskiAlgoritam(int population, double Pm, int dimension, int precision, int lower_bound, int upper_bound, Funkcija &f, int ITER);
