#include "Box.hpp"
#include "Vector.hpp"
#include "Function.hpp"

#include <vector>
#include <cassert>
#include <ctime>
#include <cstdlib>

using namespace std;

static double Xd = -100, Xg = 100;

static bool provjeri(const vector< double > &x) {
    for (int i = 0; i < (int)x.size(); ++i) {
        /* eksplicitna */
        if (x[i] < Xd || Xg < x[i]) return false;
    }
    /* implicitna */
    if (x[0] > x[1]) return false;
    if (x[0] > 2) return false;

    return true;
}

static vector< double > sredina(const vector< vector< double > > &skup, int izdvoji = -1) {
    int n = (int)skup.size();
    vector< double > xc((int)skup[0].size());

    for (int i = 0; i < n; ++i) {
        if (i != izdvoji) xc = add(xc, skup[i]);
    }

    return mul(1. / n, xc);
}

double nextRandom() {
    return (1. * rand()) / ((RAND_MAX) + 1.);
}

vector< double > Box (vector< double > x, double A, double EPS, function &f) {
    /* provjera da li pocetna tocka zadovoljava ogranicenja */
    assert(provjeri(x));

    int N = (int)x.size();

    vector< vector< double > > skup;    skup.push_back(x);
    vector< double > xc = sredina(skup), xr;
    /* generiranje skupa od 2*n tocaka */
    for (int t = 0; t < 2*N; ++t) {
        vector< double > novi(N);
        for (int i = 0; i < N; ++i) {
            novi[i] = Xd  + nextRandom() * (Xg - Xd);
        }
        while (provjeri(novi) == false) {
            novi = mul(0.5, add(novi, xc));
        }

        skup.push_back(novi);
        xc = sredina(skup);
    }

    int M = (int)skup.size();
    double f_h1, f_h2;
    int i_h1, i_h2;

    do {
        f_h1 = f(skup[0]);  f_h2 = f(skup[1]);
        i_h1 = 0;           i_h2 = 1;

        /* nadji dvije najgore tocke u skupu */
        if (f_h2 > f_h1) {
            swap(f_h1, f_h2);
            swap(i_h1, i_h2);
        }

        for (int i = 2; i < M; ++i) {
            double f_now = f(skup[i]);
            if (f_now > f_h1) {
                f_h2 = f_h1;
                i_h2 = i_h1;

                f_h1 = f_now;
                i_h1 = i;
            } else if (f_now > f_h2) {
                f_h2 = f_now;
                i_h2 = i;
            }
        }

        /* izracun nove tocke */
        xc = sredina(skup, i_h1);
        xr = sub(mul(1+A, xc), mul(A, skup[i_h1]));

        for (int i = 0; i < N; ++i) {
            if (xr[i] < Xd) xr[i] = Xd;
            else if (xr[i] > Xg) xr[i] = Xg;
        }
        while (provjeri(xr) == false) {
            xr = mul(0.5, add(xr, xc));
        }

        if (f(xr) > f_h2) {
            xr = mul(0.5, add(xr, xc));
        }

        if (lt(asub(skup[i_h1], xc), EPS)) break;

        skup[i_h1] = xr;

    } while(1);

    int best = 0, f_best = f(skup[0]);

    for (int i = 1; i < M; ++i) {
        if (f(skup[i]) < f_best) {
            f_best = f(skup[i]);
            best = i;
        }
    }

    return skup[best];
}

