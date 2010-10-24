#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

double snormrand() {
  int i=0;
  double snorm=0;
  for (i=0; i<12; i++) {
    snorm+=(random()/(RAND_MAX/4.));
  }
}

int main(int argc, char **argv) {
  int count=100000;
  srandom(1);
  do {
    std::cout << snormrand() << std::endl;
    count--;
  } while (count != 0);
}
