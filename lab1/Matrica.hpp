#pragma once

#include <cstdio>
#include <cstring>

#define BUFFER_SIZE 1024
#define EPS         1e-9

/* static functions */
static void alloc_2d_array(double ** &data, int r, int c);

static void realloc_2d_array(double ** &data, int r, int c);

/* Matrix class */
class Matrica {
  private:
   /* private members which hold matrix size */
    int _rows, _cols;
    /* private member which holds matrix elements */
    double **_data;

  public:
    /* default constructor */
    Matrica();
    /* allocateds memory for rows x cols elements */
    Matrica(int rows, int cols);
    /* copy constructor */
    Matrica(const Matrica &rhs);
    /* destructor */
    ~Matrica();

    /* equality operator */
    bool operator== (const Matrica &rhs);

    /* assignment operator */
    Matrica operator= (const Matrica &rhs);

    /* addition operator */
    Matrica operator+ (const Matrica &rhs);
    void operator+= (const Matrica &rhs);

    /* substraction operator */
    Matrica operator- (const Matrica &rhs);
    void operator-= (const Matrica &rhs);

    /* multiplication  operator */
    Matrica operator* (const double a);
   void operator*= (const double a);

    Matrica operator* (const Matrica &rhs);

    /* transpose operator */
    Matrica operator~ (void);

    /* getter setter via [] operator */
    double* operator[] (const int row) const;

    /* forward substitution */
    Matrica forward_substitution(const Matrica &b);

    /* backward substitution */
    Matrica backward_substitution(const Matrica &y);

    /* LU decomposition */
    void LU_decomposition(void);

    /* LUP decomposition */
    void LUP_decomposition(Matrica &b);

    /* size getters */
    int getRows(void) const;
    int getCols(void) const;

    /* miscellaneous methods */
    void loadFromFile(const char *filename);
    void print(const char *title, const char *filename = NULL);
};
