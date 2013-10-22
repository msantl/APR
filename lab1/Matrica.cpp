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
  return;
}

static void realloc_2d_array(double** &data, int r, int c) {
  data = (double **)realloc(data, r * sizeof(double *));

  for (int i = 0; i < r; ++i) {
    data[i] = (double *)realloc(data[i], c * sizeof(double));
  }
  return;
}

Matrica::Matrica() : _rows(0), _cols(0), _data(NULL) {
}

Matrica::Matrica(int rows, int cols) : _rows(rows), _cols(cols) {
  alloc_2d_array(_data, rows, cols);
}

Matrica::Matrica(const Matrica &rhs) {
  _rows = rhs.getRows();
  _cols = rhs.getCols();

  alloc_2d_array(_data, _rows, _cols);

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
  _rows = rhs.getRows();
  _cols = rhs.getCols();

  realloc_2d_array(_data, _rows, _cols);

  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      _data[i][j] = rhs[i][j];
    }
  }

  return *this;
}

Matrica Matrica::operator+ (const Matrica &rhs) {
  if (_rows != rhs.getRows()) throw "Zbrajanje matrica, pogresne dimenzije";
  if (_cols != rhs.getCols()) throw "Zbrajanje matrica, pogresne dimenzije";

  Matrica ret(*this);

  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      ret[i][j] += rhs[i][j];
    }
  }

  return ret;
}

void Matrica::operator+= (const Matrica &rhs) {
  if (_rows != rhs.getRows()) throw "Zbrajanje matrica, pogresne dimenzija";
  if (_cols != rhs.getCols()) throw "Zbrajanje matrica, pogresne dimenzija";

  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      _data[i][j] += rhs[i][j];
    }
  }

  return;
}

Matrica Matrica::operator- (const Matrica &rhs) {
  if (_rows != rhs.getRows()) throw "Oduzimanje matrica, pogresne dimenzija";
  if (_cols != rhs.getCols()) throw "Oduzimanje matrica, pogresne dimenzija";

  Matrica ret(*this);

  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      ret[i][j] -= rhs[i][j];
    }
  }

  return ret;
}

void Matrica::operator-= (const Matrica &rhs) {
  if (_rows != rhs.getRows()) throw "Oduzimanje matrica, pogresne dimenzija";
  if (_cols != rhs.getCols()) throw "Oduzimanje matrica, pogresne dimenzija";

  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      _data[i][j] -= rhs[i][j];
    }
  }

  return;
}

Matrica Matrica::operator* (const double a) {
  Matrica ret(*this);

  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      ret[i][j] *= a;
    }
  }

  return ret;
}

void Matrica::operator*= (const double a) {
  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      _data[i][j] *= a;
    }
  }

  return;
}

Matrica Matrica::operator* (const Matrica &rhs) {
  if (_cols != rhs.getRows()) throw "Mnozenje matrica, pogresne dimenzija";
  Matrica ret(_rows, rhs.getCols());

  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < rhs.getCols(); ++j) {
      ret[i][j] = 0;
      for (int k = 0; k < _cols; ++k) {
        ret[i][j] += _data[i][k] * rhs[k][j];
      }
    }
  }

  return ret;
}

Matrica Matrica::operator~ (void) {
  Matrica ret(_cols, _rows);

  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      ret[j][i] = _data[i][j];
    }
  }

  return ret;
}

double* Matrica::operator[] (const int row) const {
  return _data[row];
}

Matrica Matrica::forward_supstitution(const Matrica &b) {
  if (_rows != b.getRows()) throw "Supstitucija unaprijed, pogresne dimenzije";
  if (b.getCols() != 1) throw "Supstitucija unaprijed, b nije vektor";

  Matrica y(_rows, 1);

  for (int i = 0; i < _rows; ++i) {
    double sum = 0;
    for (int j = 0; j < i; ++j) {
      sum += _data[i][j] * y[j][0];
    }
    y[i][0] = b[i][0] - sum;
  }

  return y;
}

Matrica Matrica::backward_supstitution(const Matrica &y) {
  if (_rows != _cols)       throw "Supstitucija unatrag, pogresne dimenzije";
  if (_rows != y.getRows()) throw "Supstitucija unatrag, pogresne dimenzije";
  if (y.getCols() != 1)     throw "Supstitucija unatrag, y nije vektor";

  Matrica x(_rows, 1);

  for (int i = _rows - 1; i >= 0; --i) {
    double sum = 0;
    for (int j = i + 1; j < _rows; ++j) {
      sum += _data[i][j] * x[j][0];
    }
    x[i][0] = (y[i][0] - sum) / _data[i][i];
  }

  return x;
}

void Matrica::LU_decomposition(void) {
  if (_rows != _cols) throw "LU dekompozicija, pogresne dimenzije";

  for (int i = 0; i < _rows - 1; ++i) {
    for (int j = i + 1; j < _rows; ++j) {
      if (fabs(_data[i][i]) < EPS) throw "LU dekompozicija, pivot jednak nuli";
      _data[j][i] /= _data[i][i];
      for (int k = i + 1; k < _rows; ++k) {
        _data[j][k] -= _data[j][i] * _data[i][k];
      }
    }
  }

  return;
}

void Matrica::LUP_decomposition(Matrica &b) {
  if (_rows != _cols)       throw "LUP dekompozicija, pogresne dimenzije";
  if (_rows != b.getRows()) throw "LUP dekompozicija, pogresne dimenzije";
  if (b.getCols() != 1)     throw "LUP dekompozicija, pogresne dimenzije";

  for (int i = 0; i < _rows - 1; ++i) {
    int pivot = i;
    for (int j = i + 1; j < _rows; ++j) {
      if (fabs(_data[j][i]) > fabs(_data[pivot][i])) {
        pivot = j;
      }
    }

    swap(_data[i], _data[pivot]);
    swap(b[i][0], b[pivot][0]);

    for (int j = i + 1; j < _rows; ++j) {
      if (fabs(_data[i][i]) < EPS) throw "LUP dekompozicija, pivot jednak nuli";
      _data[j][i] /= _data[i][i];
      for (int k = i + 1; k < _rows; ++k) {
        _data[j][k] -= _data[j][i] * _data[i][k];
      }
    }
  }

  return;
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

void Matrica::print(const char *title, const char *filename) {
  FILE *f = stdout;

  if (filename) {
    f = fopen(filename, "w");
  } else {
    fprintf(f, "--------------------\n");
    fprintf(f, "%s\n", title);
    fprintf(f, "--------------------\n");
  }

  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      fprintf(f, "%lf ", _data[i][j]);
    }
    fprintf(f, "\n");
  }

  if (filename) {
    fclose(f);
  } else {
    fprintf(f, "--------------------\n");
  }
  return;
}

