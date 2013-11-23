#include "HookeJeeves.hpp"

#include "Vector.hpp"
#include "Function.hpp"

using namespace std;

vector< double > HookeJeeves(vector< double > x, double Dx, double EPS, function &F) {
    vector< double > xb, xp, xn;
    xb = xp = x;

    do {
        /* explore */
        xn = xp;
        for (int i = 0; i < (int)x.size(); ++i) {
            xn[i] += Dx;
            if (F(xp) < F(xn)) {
                xn[i] -= 2*Dx;
                if (F(xp) < F(xn)) {
                    xn[i] += Dx;
                }
            }
        }

        /* find new point */
        if (F(xn) < F(xb)) {
            xp = sub(mul(2, xn), xb);
            xb = xn;
        } else {
            xp = xb;
            Dx /= 2.;
        }

    } while (Dx > EPS);

    return xb;
}

