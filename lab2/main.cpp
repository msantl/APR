#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

#include "Vektor.hpp"
#include "Function.hpp"
#include "HookeJeeves.hpp"
#include "BoxMethod.hpp"

using namespace std;

/* global variables that determine the algorithms behaviour */
static double Dx = 0.5;
static double A = 1.3;
static double EPS = 1e-9;
static char* X0_filename = NULL;
static Vektor<double> X0, P0;

void print_usage(void) {
    printf("Analiza i projektiranje racunalom - druga domaca zadaca\n");
    printf("\n");
    printf("Koristenje programa:\n");
    printf("\t-h\tispisuje upute za koristenje programa\n");
    printf("\t-a\tdefinira faktor refleksije za postupak po Boxu\n");
    printf("\t-d\tdefinira pocetno dopusteno odstupanje prilikom izracuna nove"
            "tocke kod Hooke-Jeeves postupka\n");
    printf("\t-e\tdefinira zeljenu tocnost rjesenja\n");
    printf("\t-x\tdefinira putanju u kojoj se nalazi pocetno rjesenje\n");
    printf("\n");
    printf("./vjezba2 [-h] [-a A] [-d Dx] [-e EPS] -p X0\n");
    printf("\n");
    exit(0);
}

void parse_commad_line_args(int argc, char **argv) {
    int c;

    while ((c = getopt(argc, argv, "a:d:e:hx:")) != -1) {
        switch(c) {
            case 'a':
                sscanf(optarg, "%lf", &A);
                break;
            case 'd':
                sscanf(optarg, "%lf", &Dx);
                break;
            case 'e':
                sscanf(optarg, "%lf", &EPS);
                break;
            case 'x':
                X0_filename = (char *)malloc(strlen(optarg));
                strcpy(X0_filename, optarg);
                break;
            case '?':
                if (optopt == 'a' || optopt == 'd' ||
                    optopt == 'e' || optopt == 'x') {
                    fprintf(stderr, "Opcija -%c zahtjeva parametar\n", optopt);
                }
                /* fall through */
            case 'h':
                print_usage();
                break;
        }
    }

    if (X0_filename == NULL) {
        fprintf(stderr, "Izostavljen obavezan parametar -x\n");
        print_usage();
    } else {
        FILE *f = fopen(X0_filename, "r");
        int n; fscanf(f, "%d", &n);

        X0 = Vektor<double>(n);
        P0 = Vektor<double>(n);

        for (int i = 0; i < n; ++i) {
            fscanf(f, "%lf", &X0[i]);
        }

        for (int i = 0; i < n; ++i) {
            fscanf(f, "%lf", &P0[i]);
        }

        fclose(f);
    }
}

void printHookeJeeves(const char *label, Vektor<double> x, double dx, double eps, Function &f) {
    printf("%s: X = (", label);

    Vektor<double> sol = HookeJeeves(x, dx, eps, f);
    for (int i = 0; i < sol.size(); ++i) {
        printf("%lf, ", sol[i]);
    }

    printf(")\n");
    return;
}

void printBoxMethod(const char *label, Vektor<double> x, double a, double eps, Function &f) {
    printf("%s: X = (", label);

    Vektor<double> sol = BoxMethod(x, a, eps, f);
    for (int i = 0; i < sol.size(); ++i) {
        printf("%lf, ", sol[i]);
    }

    printf(")\n");
    return;
}

int main(int argc, char **argv) {
    parse_commad_line_args(argc, argv);

    /* prepare functions we want to find their minimum */
    Function_F1 f1; f1.setOffsetVector(P0);
    Function_F2 f2; f2.setOffsetVector(P0);
    Function_F3 f3; f3.setOffsetVector(P0);
    Function_F4 f4; f4.setOffsetVector(P0);

    /* print out the solutions using HookeJeeves method */
    printf("Postupak Hooke-Jeeves:\n");
    printf("Dx = %lf, EPS = %lf\n", Dx, EPS);
    printf("------------------------\n");
    printHookeJeeves("f1", X0, Dx, EPS, f1);
    printHookeJeeves("f2", X0, Dx, EPS, f2);
    printHookeJeeves("f3", X0, Dx, EPS, f3);
    printHookeJeeves("f4", X0, Dx, EPS, f4);

    /* print out the solutions for 2. and 3. using Box method */
    printf("Postupak po Boxu:\n");
    printf("A = %lf, EPS = %lf\n", A, EPS);
    printf("------------------------\n");
    printBoxMethod("f2", X0, A, EPS, f2);
    printBoxMethod("f3", X0, A, EPS, f3);

    // printBoxMethod("f1", X0, A, EPS, f1);
    //  printBoxMethod("f4", X0, A, EPS, f4);

    return 0;
}
