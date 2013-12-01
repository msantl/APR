#include <vector>
#include <algorithm>
#include <ctime>

#include "BoxMethod.hpp"

using namespace std;

static const double Xd = -100, Xg = 100;

static bool check_explicit(Vektor<double> &x) {
    /* -100 <= Xi <= 100 */
    int n = x.size();
    for (int i = 0; i < n; ++i) {
        if (Xd > x[i] || x[i] > Xg) {
            return false;
        }
    }
    return true;
}

static bool check_implicit(Vektor<double> &x) {
    /* x1 - x2 <= 0 */
    if (x[0] - x[1] > 0) {
        return false;
    }

    /* x1 - 2 <= 0 */
    if (x[0] > 2) {
        return false;
    }

    return true;
}

static Vektor< double > extract_max(vector< Vektor< double > > &skup, Function &f) {
    Vektor< double > res;
    int x = 0;
    int m = (int)skup.size();

    assert(m > 0);

    for (int i = 0; i < m; ++i) {
        if (f(skup[x]) < f(skup[i])) {
            x = i;
        }
    }

    res = skup[x];
    skup.erase(skup.begin() + x);

    return res;
}

static Vektor< double > centroid(vector< Vektor< double > > &skup) {
    Vektor< double > Xc;
    int m = (int)skup.size();

    assert(m > 0);

    Xc = skup[0];
    for (int i = 1; i < m; ++i) {
        Xc += skup[i];
    }

    return Xc * (1. / m);
}

Vektor<double> BoxMethod(Vektor<double> x, double a, double eps, Function &f) {
    assert(check_explicit(x) == true);
    assert(check_implicit(x) == true);

    srand((unsigned)time(NULL));

    Vektor< double > Xc, Xr;

    int n = x.size();
    vector< Vektor< double > > skup; skup.push_back(x);
    Xc = x; /* first point is the centroid itself */

    /* generate 2*n points that satisfy both implicit and explicit restriction */
    for (int t = 0; t < 2 * n; ++t) {
        Vektor< double > X(n);
        for (int i = 0; i < n; ++i) {
            double R = (1. * rand()) / (RAND_MAX + 1.);
            X[i] = Xd + R * (Xg - Xd);
        }

        while (check_implicit(X) == false) {
            X = (X + Xc) * 0.5;
        }

        skup.push_back(X);
        Xc = centroid(skup);
    }

    /* Box method */
    Vektor< double > Xh1, Xh2;
    while (1) {
        Xh1 = extract_max(skup, f);
        Xh2 = extract_max(skup, f); skup.push_back(Xh2);

        Xc = centroid(skup); /* centroid without Xh1 */

        /* exit condition */
        if ((Xc - Xh1).abs() < eps) {
            break;
        }

        Xr = Xc * (1 + a) - Xh1 * a; /* reflection */

        /* adjust to satisfy explicit restrictions */
        for (int i = 0; i < n; ++i) {
            Xr[i] = min(Xr[i], Xg);
            Xr[i] = max(Xr[i], Xd);
        }

        /* adjust to satisfy implici restrictions */
        while (check_implicit(Xr) == false) {
            Xr = (Xr + Xc) * 0.5;
        }

        /* if it's still the worst point we move it closer to Xc*/
        if (f(Xh2) < f(Xr)) {
            Xr = (Xr + Xc) * 0.5;
        }

        skup.push_back(Xr);
    }

    /* find the best solution among 2*n */
    Xc = skup[0];

    for (int i = 1; i < 2 * n; ++i) {
        if (f(skup[i]) < f(Xc)) {
            Xc = skup[i];
        }
    }

    return Xc;
}
