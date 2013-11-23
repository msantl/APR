#include "HookeJeeves.hpp"
#include "Box.hpp"
#include "Function.hpp"

#include <cstdio>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

using namespace std;

#define sqr(x) ((x)*(x))
#define abs(x) (((x) < 0) ? (-(x)) : (x))

/* functions for which we want to find their minimum */

class F0 : public function {
    double operator() (const vector< double > &x) const {
        return sqr(x[0]) + sqr(x[1]);
    }
} f0;

class F1 : public function {
    double operator() (const vector< double > &x) const {
        return 10 * sqr(sqr(x[0]) - x[1]) + sqr(1-x[0]);
    }
} f1;

class F2 : public function {
    double operator() (const vector< double > &x) const {
        return sqr(x[0] - 4) + 4 * sqr(x[1] - 2);
    }
} f2;

class F3 : public function {
    double operator() (const vector< double > &x) const {
        double ret = 0;
        for (int i = 0; i < (int)x.size(); ++i) {
            ret += sqr(x[i] - _p[i]);
        }
        return ret;
    }
} f3;

class F4 : public function {
    double operator() (const vector< double > &x) const {
        return abs((x[0] - x[1]) * (x[0] + x[1])) + sqrt(sqr(x[0]) + sqr(x[1]));
    }
} f4;

/* helper function that reads the starting point */
void parseInputFile(char *filename, vector< double >&x, vector< double > &p ) {
    FILE *f = fopen(filename, "r");
    int n;  fscanf(f, "%d", &n);
    double d;

    for (int i = 0; i < n; ++i) {
        fscanf(f, "%lf", &d);
        x.push_back(d);
    }

    for (int i = 0; i < n; ++i) {
        fscanf(f, "%lf", &d);
        p.push_back(d);
    }

    return;
}

/* helper function that prints out the results using Hooke Jeeves method*/
void findMinimumHookeJeeves(const vector< double > &x, const vector< double > &p, const double &Dx, const double &EPS, function &f) {
    f.setOffsetVector(p);

    vector< double > res = HookeJeeves(x, Dx, EPS, f);

    for (int i = 0; i < (int)res.size(); ++i) {
        printf("%.2lf ", res[i]);
    }   printf("\n");
}

/* helper function that prints out the results using Box method*/
void findMinimumBox(const vector< double > &x, const vector< double > &p, const double &A, const double &EPS, function &f) {
    f.setOffsetVector(p);

    vector< double > res = Box(x, A, EPS, f);

    for (int i = 0; i < (int)res.size(); ++i) {
        printf("%.2lf ", res[i]);
    }   printf("\n");
}

int main(int argc, char **argv) {
    srand((time(NULL)));

    vector< double > x;
    vector< double > p;
    double Dx = 0.5, EPS = 1e-9, A = 1.3;

    if (argc < 2) {
        fprintf(stderr, "Navedite ime datoteke koja sadrzi pocetne podatke\n");
        return 1;
    }
    parseInputFile(argv[1], x, p);

    /* parse command line arguments for Dx and EPS*/
    int c;
    while ((c = getopt (argc, argv, "a:d:e:")) != -1)
        switch (c)
        {
            case 'a':
                sscanf(optarg, "%lf", &A);
                break;
            case 'd':
                sscanf(optarg, "%lf", &Dx);
                break;
            case 'e':
                sscanf(optarg, "%lf", &EPS);
                break;
            case '?':
                if (optopt == 'd' || optopt == 'e') {
                    fprintf (stderr, "Options -a, -d and -e require an argument.\n");
                } else {
                    fprintf (stderr, "Unknown option '%c'.\n", optopt);
                }
                return 1;
            default:
                continue;
        }

    /* print results for Hooke Jeeves method*/
    printf("Starting HookeJeeves with Dx=%lf and EPS=%lf\n", Dx, EPS);
    findMinimumHookeJeeves(x, p, Dx, EPS, f1);
    findMinimumHookeJeeves(x, p, Dx, EPS, f2);
    findMinimumHookeJeeves(x, p, Dx, EPS, f3);
    findMinimumHookeJeeves(x, p, Dx, EPS, f4);

    /* print results for Box method */
    printf("Starting Box with a=%lf and EPS=%lf\n", A, EPS);
    findMinimumBox(x, p, A, EPS, f2);
    findMinimumBox(x, p, A, EPS, f3);

    return 0;
}
