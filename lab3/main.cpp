#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <unistd.h>

#include "GenetskiAlgoritam.hpp"

using namespace std;

/* constant variables that define initial conditions of GA */
const int DIMENSION = 3;
const int PRECISION = 3;
const int DG = -100;
const int GG = 100;

/* static variables that define initial conditions of GA */
static int N = 42;
static double Pm = 0.005;
static int ITER = 10000;
static char* offset_filename = NULL;
static vector< double > offset;

void print_usage(void) {
    printf("Analiza i projektiranje racunalom - treca domaca zadaca\n");
    printf("\n");
    printf("Koristenje programa:\n");
    printf("\t-h\tispisuje upute za koristenje programa\n");
    printf("\t-n\tbroj clanova populacije (42 default)\n");
    printf("\t-p\tvjerojatnost mutacije bita (0.005 default)\n");
    printf("\t-i\tbroj iteracija postupka (10000 default)\n");
    printf("\t-x\tdatoteka koja sadrzi vektor pomaka funkcije\n");
    printf("\n");
    printf("./vjezba3 [-h] [-n N] [-p Pm] [-e I] -x <filename>\n");
    printf("\n");
    exit(0);
}

void parse_commad_line_args(int argc, char **argv) {
    int c;

    while ((c = getopt(argc, argv, "n:p:i:hx:")) != -1) {
        switch(c) {
            case 'n':
                sscanf(optarg, "%d", &N);
                break;
            case 'p':
                sscanf(optarg, "%lf", &Pm);
                break;
            case 'i':
                sscanf(optarg, "%d", &ITER);
                break;
            case 'x':
                offset_filename = (char *)malloc(strlen(optarg));
                strcpy(offset_filename, optarg);
                break;
            case '?':
                if (optopt == 'n' || optopt == 'p' ||
                    optopt == 'p' || optopt == 'x') {
                    fprintf(stderr, "Opcija -%c zahtjeva parametar\n", optopt);
                }
                /* fall through */
            case 'h':
                print_usage();
                break;
        }
    }

    if (offset_filename == NULL) {
        fprintf(stderr, "Izostavljen obavezan parametar -x\n");
        print_usage();
    } else {
        FILE *f = fopen(offset_filename, "r");

        offset = vector< double >(DIMENSION);

        for (int i = 0; i < DIMENSION; ++i) {
            fscanf(f, "%lf", &offset[i]);
        }

        fclose(f);
    }

    return;
}

void printSolutionForFunction(Funkcija &f, const char *label = NULL) {
    if (label) {
        printf("Running GA on function %s\n", label);
    }
    printf("-------------------------\n");
    vector< double > sol = GenetskiAlgoritam(N, Pm, DIMENSION, PRECISION, DG, GG, f, ITER);
    for (int i = 0; i < (int)sol.size(); ++i) {
        printf("%.2lf ", sol[i]);
    }   printf("= Solution (%.4lf)\n", f(sol));

    printf("-------------------------\n");
    return;
}

int main(int argc, char **argv) {
    srand((unsigned)time(NULL));
    parse_commad_line_args(argc, argv);

    /* Functions */
    Funkcija_F3 f3; f3.setOffsetVector(offset);
    Funkcija_F4 f4; f4.setOffsetVector(offset);
    Funkcija_F6 f6; f6.setOffsetVector(offset);
    Funkcija_F7 f7; f7.setOffsetVector(offset);

    printSolutionForFunction(f3, "f3");
    printSolutionForFunction(f4, "f4");
    printSolutionForFunction(f6, "f6");
    printSolutionForFunction(f7, "f7");

    return 0;
}

