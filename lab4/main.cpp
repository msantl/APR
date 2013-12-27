#include "Matrica.hpp"

#include <cstdio>
#include <cstring>
#include <memory>

using namespace std;

int main(int argc, char **argv) {
  Matrica A = Matrica();

  A.loadFromFile("a.txt");

  A.print("Matrica A");

  try {
    Matrica B = !A;
    B.print("Inverz od A");

  } catch(const char *msg) {
    puts(msg);
  }

  return 0;
}
