#pragma once

#include <vector>

std::vector< double > mul(double c, const std::vector< double > &x);

std::vector< double > sub(const std::vector< double > &x, const std::vector< double > &y);

std::vector< double > asub(const std::vector< double > &x, const std::vector< double > &y);

std::vector< double > add(const std::vector< double > &x, const std::vector< double > &y);

bool lt(const std::vector< double > &x, double c);
