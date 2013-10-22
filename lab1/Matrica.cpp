#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <cmath>

#include "Matrica.hpp"

using namespace std;

static void alloc_2d_array(double** &data, int r, int c) {
  data = (double **)malloc(r * sizeof(double *));

  for (int i = 0; i < r; ++i) {
    data[i] = (double *)malloc(c * sizeof(double));
  }
}

Matrica::Matrica() : _rows(0), _cols(0), _data(NULL) {
}

Matrica::Matrica(int rows, int cols) : _rows(rows), _cols(cols) {
  alloc_2d_array(_data, rows, cols);
}

Matrica::Matrica(const Matrica &rhs) {
  alloc_2d_array(_data, rhs.getRows(), rhs.getCols());

  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      _data[i][j] = rhs[i][j];
    }
  }
}

Matrica::~Matrica() {
  for (int i = 0; i < _rows; ++i) {
    free(_data[i]);
  }
  free(_data);
}

bool Matrica::operator== (const Matrica &rhs) {
  if (_rows != rhs.getRows()) return false;
  if (_cols != rhs.getCols()) return false;

  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      if (fabs(_data[i][j] - rhs[i][j]) >= EPS) {
        return false;
      }
    }
  }

  return true;
}

Matrica Matrica::operator= (const Matrica &rhs) {
  return Matrica(rhs);
}

Matrica Matrica::operator+ (const Matrica &rhs) {
  if (_rows != rhs.getRows()) throw -1;
  if (_cols != rhs.getCols()) throw -1;

  return Matrica();
}

void  Matrica::operator+= (const Matrica &rhs) {
  if (_rows != rhs.getRows()) throw -1;
  if (_cols != rhs.getCols()) throw -1;

  return;
}

Matrica Matrica::operator- (const Matrica &rhs) {
  if (_rows != rhs.getRows()) throw -1;
  if (_cols != rhs.getCols()) throw -1;

  return Matrica();
}

void Matrica::operator-= (const Matrica &rhs) {
  if (_rows != rhs.getRows()) throw -1;
  if (_cols != rhs.getCols()) throw -1;

  return;
}

Matrica Matrica::operator* (const int a) {
  return Matrica();
}

Matrica Matrica::operator* (const Matrica &rhs) {
  if (_cols != rhs.getRows()) throw -1;

  return Matrica(_rows, rhs.getCols());
}

Matrica Matrica::operator~ (void) {
  return Matrica();
}

double* Matrica::operator[] (const int row) const {
  return _data[row];
}

int Matrica::getRows(void) const { return _rows; }
int Matrica::getCols(void) const { return _cols; }

void Matrica::loadFromFile(const char *filename) {
  vector< double > temp_storage;

  FILE *f = fopen(filename, "r");

  char *buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));

  int rows = 0, cols = 0, c;

  while(fgets(buffer, BUFFER_SIZE, f) != NULL) {
    char *iter = buffer;
    double num;
    c = 0;

    do {
      while (*iter == ' ' || *iter == '\t' || *iter == '\n') ++iter;

      if (sscanf(iter, "%lf", &num) == 1) {
        temp_storage.push_back(num);
        c ++;
      }
    } while((iter = strstr(iter, " ")) != NULL);

    cols = max(c, cols);
    rows ++;

    memset(buffer, 0, BUFFER_SIZE);
  }

  free(buffer);
  fclose(f);

  _rows = rows;
  _cols = cols;

  alloc_2d_array(_data, _rows, _cols);

  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      _data[i][j] = temp_storage.at(_cols * i + j);
    }
  }

  return;
}

void Matrica::print(const char *filename) {
  FILE *f = stdout;

  if (filename) {
    f = fopen(filename, "w");
  }

  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      fprintf(f, "%lf ", _data[i][j]);
    }
    fprintf(f, "\n");
  }

  if (filename) {
    fclose(f);
  }
}

