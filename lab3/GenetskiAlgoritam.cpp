#include "GenetskiAlgoritam.hpp"

#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

static vector< double > JedinkaToVector(const Jedinka &j) {
    int N = j.getDimension();
    vector< double > ret(N);

    for (int i = 0; i < N; ++i) {
        ret[i] = j.getFloatByIndex(i);
    }
    return ret;
}

static void selekcija(vector< Jedinka >&pop, int &x, int &y, int &z) {
    int N = (int)pop.size();

    x = rand() % N;
    do { y = rand() % N; } while (x == y);
    do { z = rand() % N; } while (x == z || y == z);

    return;
}

static void krizanje(vector< Jedinka >&pop, int x, int y, int z) {
    double a = rand() / (1. * RAND_MAX);

    /* D = a X1 + (1-a) X2 */
    for (int i = 0; i < pop[z].getDimension(); ++i) {
        pop[z].setFloatByIndex(i,
                pop[x].getFloatByIndex(i) * a +
                pop[y].getFloatByIndex(i) * (1 - a));
    }

    return;
}

static void mutacija(Jedinka &jedinka, double Pm) {
    /* jednolika mutacija - slucajni broj u intervalu */
    double prob = rand() / (1. * RAND_MAX);
    if (prob < Pm) {
        for (int i = 0; i < jedinka.getDimension(); ++i) {
            double val = jedinka.getDG() + (rand() / (1. * RAND_MAX)) * (jedinka.getGG() - jedinka.getDG());
            jedinka.setFloatByIndex(i, val);
        }
    }

    return;
}

vector<double> GenetskiAlgoritam(int population, double Pm, int dimension, int precision, int lower_bound, int upper_bound, Funkcija &f, int ITER) {
    /* stvori populaciju */
    vector< Jedinka > populacija(population);

    for (int i = 0; i < population; ++i) {
        populacija[i] = Jedinka(dimension, precision, lower_bound, upper_bound);
    }

    Jedinka best = populacija[0];  double best_value = f(JedinkaToVector(best));

    /* evaluiraj populaciju */
    for (vector< Jedinka >::iterator it = populacija.begin(); it != populacija.end(); ++it ) {
        double temp_value = f(JedinkaToVector(*it));
        if (temp_value < best_value) {
            best_value = temp_value;
            best = *it;
        }
    }

    do {
        int a, b, c;
        /* odaberi slucajno 3 jedinke */
        selekcija(populacija, a, b, c);

        double val_a = f(JedinkaToVector(populacija[a]));
        double val_b = f(JedinkaToVector(populacija[b]));
        double val_c = f(JedinkaToVector(populacija[c]));
        if (val_a >= val_b && val_a >= val_c) swap(a, c);
        if (val_b >= val_a && val_b >= val_c) swap(b, c);

        /* umjesto c u populaciju stavi krizaj(a, b) */
        krizanje(populacija, a, b, c);

        /* mutiraj novu jedinku */
        mutacija(populacija[c], Pm);

        /* evaluiraj novu jedinku */
        double temp_value = f(JedinkaToVector(populacija[c]));
        if (temp_value < best_value) {
            best_value = temp_value;
            best = populacija[c];

            /* ispisi trenutno najbolju jedinku */
            for (int i = 0; i < best.getDimension(); ++i) {
                fprintf(stderr, "%.5lf ", best.getFloatByIndex(i));
            }   fprintf(stderr, " = %.5lf\n", best_value);
        }
    } while (ITER--);

    /* vrati najbolju jedinku */
    return JedinkaToVector(best);
}
