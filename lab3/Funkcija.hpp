#pragma once

#include <vector>

class Funkcija {
    protected:
        std::vector<double> _p;
    public:
        Funkcija();

        void setOffsetVector(std::vector<double> &p);

        virtual double operator() (std::vector<double> x) = 0;
};

class Funkcija_F3 : public Funkcija {
    public:
        double operator() (std::vector<double> x);
};

class Funkcija_F4 : public Funkcija {
    public:
        double operator() (std::vector<double> x);
};

class Funkcija_F6 : public Funkcija {
    public:
        double operator() (std::vector<double> x);
};

class Funkcija_F7 : public Funkcija {
    public:
        double operator() (std::vector<double> x);
};

