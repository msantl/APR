#pragma once

#include <vector>

class Jedinka {
    private:
        std::vector<double> _b;
        int _dimension;
        int _lower_bound, _upper_bound;
        int _precision;

    public:
        Jedinka();
        Jedinka(int dimension, int precision, int lower_bound, int upper_bound);

        ~Jedinka();

        double getFloatByIndex(int index) const;
        void setFloatByIndex(int index, double value);

        int getDimension(void) const;
        int getDG(void) const;
        int getGG(void) const;
};


