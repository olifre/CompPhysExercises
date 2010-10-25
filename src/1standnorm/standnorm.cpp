#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

double snormrand() {
  int i=0;
  double snorm=0;
  for (i=0; i<12; i++) {
    snorm+=(1.0*random()/(RAND_MAX));
  }
  snorm -= 1./6.;
  return snorm;
}

int main(int argc, char **argv) {
  int count=1000000;
  srandom(1);
  do {
    std::cout << snormrand() << std::endl;
    count--;
  } while (count != 0);
}
