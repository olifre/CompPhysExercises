#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {
  double mypi=0;
  double a,b;
  int inside=0, outside=0;
  srandom(10);
  
  int iter=1E8;
  for (int i = 0; i < iter; ++i) {
    a=(10*rand()/(RAND_MAX+1.0));
    b=(10*rand()/(RAND_MAX+1.0));
    if (a*a+b*b<=100) {
      inside+=1;
      outside+=1;
    } else {
      outside+=1;
    }
  }
  std::cout << 4.*inside/outside << std::endl;
  
  return 0;
}
