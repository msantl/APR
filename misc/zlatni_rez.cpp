#include <cstdio>

using namespace std;

const double k = 0.618;

#define sqr(x) ((x)*(x))

double f(double x) {
    return sqr(x - 4);
}

int main(int argc, char **argv) {
    double a, b, c, d, EPS;
    scanf("%lf%lf%lf", &a, &b, &EPS);

    c = b - k * (b - a);
    d = a + k * (b - a);

    printf("%.3lf %.3lf %.3lf %.3lf\n", a, c, d, b);

    while (b - a > EPS) {
        if (f(c) < f(d)) {
            b = d; d = c; c = b - k * (b - a);
        } else {
            a = c; c = d; d = a + k * (b - a);
        }

        printf("%.3lf %.3lf %.3lf %.3lf\n", a, c, d, b);
    }

    printf("%.3lf\n", (a + b) / 2.);

    return 0;
}

