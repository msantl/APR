#include "Matrica.hpp"

#include <cstdio>
#include <cstring>
#include <memory>

using namespace std;

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Unesite dodatni parametar (LU ili LUP) za odabir dekompozicije\n");
    return 1;
  }

  Matrica A = Matrica();
  Matrica b = Matrica();

  A.loadFromFile("a.txt");
  b.loadFromFile("b.txt");

  A.print("Matrica A");
  b.print("Vektor b");

  try {
    /* rijesavanje sustava A x = b*/

    if (strcmp(argv[1], "LUP") == 0) {
      A.LUP_decomposition(b);
      A.print("LUP dekompozicija");
    } else {
      A.LU_decomposition();
      A.print("LU dekompozicija");
    }

    Matrica y = A.forward_supstitution(b);
    Matrica x = A.backward_supstitution(y);

    b.print("Vektor b");
    y.print("Vektor y");
    x.print("Vektor x");

  } catch(const char *msg) {
    puts(msg);
  }

  return 0;
}
