#pragma once

#include <vector>

class function {
    protected:
        std::vector< double > _p;

    public:
        virtual double operator() (const std::vector< double > &x) const = 0;

        void setOffsetVector(const std::vector< double > &p);
};
