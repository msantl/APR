#include "Matrica.hpp"

#include <cstdio>
#include <memory>

using namespace std;

int main(int argc, char **argv) {
  Matrica a = Matrica();
  Matrica b = Matrica();

  a.loadFromFile("a.txt");
  b.loadFromFile("b.txt");

  a.print();
  b.print();

  Matrica c = a + b;

  c.print();

  return 0;
}
