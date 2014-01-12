#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <unistd.h>

#include "Matrica.hpp"
#include "Trapezni.hpp"
#include "RungeKutta4.hpp"

using namespace std;

static double T = 0, t = 0;
static int p = 1;
static char* A_filename = NULL;
static char* B_filename = NULL;
static char* x0_filename = NULL;

void print_usage(void) {
    printf("Analiza i projektiranje racunalom - cetvrta domaca zadaca\n");
    printf("\n");
    printf("Koristenje programa:\n");
    printf("\t-h\tispisuje upute za koristenje programa\n");
    printf("\t-A\tdatoteka koja sadrzi matricu A\n");
    printf("\t-B\tdatoteka koja sadrzi matricu B\n");
    printf("\t-x\tdatoteka koja sadrzi pocetne vrijednosti x\n");
    printf("\t-T\tiznos koraka integracije\n");
    printf("\t-t\tiznos vremenskog intervala za koji se provodi postupak\n");
    printf("\t-p\tgustoca ispisa (podrazumijevana vrijednost 1)\n");
    printf("\n");
    printf("./vjezba4 [-h] -A <filename> -B <filename> -x <filename> -T <value> -t <value>\n");
    printf("\n");
    exit(0);
}

void parse_commad_line_args(int argc, char **argv) {
    int c;

    while ((c = getopt(argc, argv, "hA:B:x:T:t:p:")) != -1) {
        switch(c) {
            case 'p':
                sscanf(optarg, "%d", &p);
                break;
            case 'T':
                sscanf(optarg, "%lf", &T);
                break;
            case 't':
                sscanf(optarg, "%lf", &t);
                break;
            case 'A':
                A_filename = (char *)malloc(strlen(optarg));
                strcpy(A_filename, optarg);
                break;
            case 'B':
                B_filename = (char *)malloc(strlen(optarg));
                strcpy(B_filename, optarg);
                break;
            case 'x':
                x0_filename = (char *)malloc(strlen(optarg));
                strcpy(x0_filename, optarg);
                break;
            case '?':
                if (optopt == 'h' || optopt == 'T' || optopt == 'A' ||
                    optopt == 't' || optopt == 'x' || optopt == 'p' || optopt == 'B') {
                    fprintf(stderr, "Opcija -%c zahtjeva parametar\n", optopt);
                }
                /* fall through */
            case 'h':
                print_usage();
                break;
        }
    }

    if (x0_filename == NULL) {
        fprintf(stderr, "Izostavljen obavezan parametar -x\n");
        print_usage();
    }

    if (A_filename == NULL) {
        fprintf(stderr, "Izostavljen obavezan parametar -A\n");
        print_usage();
    }

    if (B_filename == NULL) {
        fprintf(stderr, "Izostavljen obavezan parametar -B\n");
        print_usage();
    }

    if (T == 0) {
        fprintf(stderr, "Izostavljen obavezan parametar -T\n");
        print_usage();
     }

    if (t == 0) {
        fprintf(stderr, "Izostavljen obavezan parametar -t\n");
        print_usage();
     }

    return;
}
int main(int argc, char **argv) {
    char buffer[256];
    parse_commad_line_args(argc, argv);

    FILE* trapezni_plot = fopen("trapezni.plot", "w");
    FILE* runge_kutta_plot = fopen("runge_kutta.plot", "w");

    Matrica A = Matrica();
    Matrica B = Matrica();
    Matrica x0 = Matrica();

    A.loadFromFile(A_filename);
    A.print("Matrica A");

    B.loadFromFile(B_filename);
    B.print("Matrica B");

    x0.loadFromFile(x0_filename);
    x0.print("x0");

    /* Trapezni postupak */
    try {

        printf("------------------------\n");
        printf("Trapezni postupak, T = %lf, t = %lf\n", T, t);
        printf("------------------------\n");

        Matrica xk(x0);

        for (double ti = T; ti <= t; ti += T) {
            xk = Trapezni::computeNextValue(xk, A, B, T, ti);

            if (int(ti / T) % p == 0) {
                sprintf(buffer, "xk, iteracija t = %lf", ti);
                xk.print(buffer);
            }

            /* print to file */
            fprintf(trapezni_plot, "%lf", ti);
            for (int i = 0; i < xk.getRows(); ++i) {
                fprintf(trapezni_plot, "\t%lf", xk[i][0]);
            }
            fprintf(trapezni_plot, "\n");
        }

        printf("------------------------\n");
    } catch(const char *msg) {
        puts(msg);
    }

    /* Runge Kutta postupak 4. reda */
    try {

        printf("------------------------\n");
        printf("Runge Kutta postupak, T = %lf, t = %lf\n", T, t);
        printf("------------------------\n");

        Matrica xk(x0);

        for (double ti = T; ti <= t; ti += T) {
            xk = RungeKutta4::computeNextValue(xk, A, T);

            if (int(ti / T) % p == 0) {
                sprintf(buffer, "xk, iteracija t = %lf", ti);
                xk.print(buffer);
            }

            /* print to file */
            fprintf(runge_kutta_plot, "%lf", ti);
            for (int i = 0; i < xk.getRows(); ++i) {
                fprintf(runge_kutta_plot, "\t%lf", xk[i][0]);
            }
            fprintf(runge_kutta_plot, "\n");
        }

        printf("------------------------\n");
    } catch(const char *msg) {
        puts(msg);
    }

    free(A_filename);
    free(B_filename);
    free(x0_filename);

    fclose(trapezni_plot);
    fclose(runge_kutta_plot);

    return 0;
}
