#pragma once

#include <vector>

class Jedinka {
    private:
        std::vector< unsigned int > _b;
        int _length;
        int _dimension;
        int _lower_bound, _upper_bound;
        int _precision;

        unsigned int _convert_to_binary(double num) const;
        double _convert_to_float(int num) const;

    public:
        Jedinka();
        Jedinka(int dimension, int precision, int lower_bound, int upper_bound);

        unsigned int getBinaryByIndex(int index) const;
        double getFloatByIndex(int index) const;

        void setBinaryByIndex(int index, unsigned int value);
        void setFloatByIndex(int index, double value);

        int getDimension(void) const;
        int getLength(void) const;
};


