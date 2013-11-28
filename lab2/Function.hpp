#pragma once

#include "Vektor.hpp"

class Function {
    protected:
        Vektor<double> _p;
    public:
        Function();

        void setOffsetVector(Vektor<double> &p);

        virtual double operator() (Vektor<double> &x) = 0;
};

class Function_F1 : public Function {
    public:
        double operator() (Vektor<double> &x);
};

class Function_F2 : public Function {
    public:
        double operator() (Vektor<double> &x);
};

class Function_F3 : public Function {
    public:
        double operator() (Vektor<double> &x);
};

class Function_F4 : public Function {
    public:
        double operator() (Vektor<double> &x);
};

