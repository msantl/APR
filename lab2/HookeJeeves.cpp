#include "HookeJeeves.hpp"

Vektor<double> HookeJeeves(Vektor<double> x, double dx, double eps, Function &f) {
    Vektor<double> Xb, Xp, Xn;
    Xp = Xb = x;

    int n = x.size();

    do {
        /* explore */
        Xn = Xp;
        for (int i = 0; i < n; ++i) {
            Xn[i] += dx;
            if (f(Xn) > f(Xp)) {
                Xn[i] -= 2 * dx;
                if (f(Xn) > f(Xp)) {
                    Xn[i] += dx;
                }
            }
        }
        /* determine new point */
        if (f(Xn) < f(Xb)) {
            Xp = Xn * 2 - Xb;
            Xb = Xn;
        } else {
            Xp = Xb;
            dx /= 2.;
        }

    } while(dx > eps);

    return Xb;
}
