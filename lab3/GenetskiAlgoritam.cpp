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

static void selekcija(vector< Jedinka >&pop, int &x, int &y, int &z, Funkcija &f) {
    int N = (int)pop.size();

    double sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += f(JedinkaToVector(pop[i]));
    }

    double a = sum * (rand() / (1. * RAND_MAX));
    double b = sum * (rand() / (1. * RAND_MAX));
    double c = sum * (rand() / (1. * RAND_MAX));

    x = y = z = -1;

    for (int i = 0; i < N; ++i) {
        double temp_value = f(JedinkaToVector(pop[i]));

        if (!~x && temp_value > a) {
            x = i;
        } else {
            a -= temp_value;
        }

        if (!~y && temp_value > b) {
            y = i;
        } else {
            b -= temp_value;
        }

        if (!~z && temp_value > c) {
            z = i;
        } else {
            c -= temp_value;
        }
    }

    return;
}

static void krizanje(vector< Jedinka >&pop, int x, int y, int z) {
    int R = rand();

    /* DIJETE = AB + R(A^B) */
    for (int i = 0; i < pop[z].getDimension(); ++i) {
        int lhs = (pop[x].getBinaryByIndex(i) & pop[y].getBinaryByIndex(i));
        int rhs = (pop[x].getBinaryByIndex(i) ^ pop[y].getBinaryByIndex(i)) & R;

        pop[z].setBinaryByIndex(i, lhs | rhs);
    }

    return;
}

static void mutacija(Jedinka &jedinka, double Pm) {
    /* jednostavna mutacija - slucajna promjena jednog bita unutar kromosoma */
    for (int i = 0; i < jedinka.getDimension(); ++i) {
        for (int j = 0; j < jedinka.getLength(); ++j) {
            double prob = rand() / (1. * RAND_MAX);
            if (prob < Pm) {
                int val = jedinka.getBinaryByIndex(i);
                val ^= 1 << j;

                jedinka.setBinaryByIndex(i, val);
            }
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
        int i, j, k;
        /* odaberi slucajno 3 jedinke */
        selekcija(populacija, i, j, k, f);

        double val_i = f(JedinkaToVector(populacija[i]));
        double val_j = f(JedinkaToVector(populacija[j]));
        double val_k = f(JedinkaToVector(populacija[k]));
        /* zamijeni najgoru sa dijetetom bolje dvije */
        if (val_i > val_j && val_i > val_k) swap(i, k);
        if (val_j > val_i && val_j > val_k) swap(j, k);

        krizanje(populacija, i, j, k);

        /* mutiraj novu jedinku */
        mutacija(populacija[k], Pm);

        /* evaluiraj novu jedinku */
        double temp_value = f(JedinkaToVector(populacija[k]));
        if (temp_value < best_value) {
            best_value = temp_value;
            best = populacija[k];
        }

        /* ispisi trenutno najbolju jedinku */
        for (int i = 0; i < best.getDimension(); ++i) {
            fprintf(stderr, "%.2lf ", best.getFloatByIndex(i));
        }   fprintf(stderr, " = %.2lf\n", best_value);

    } while (ITER--);

    /* vrati najbolju jedinku */
    return JedinkaToVector(best);
}
