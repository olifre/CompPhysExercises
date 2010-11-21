#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

double snormrand() {
  double snorm;
  do {
    snorm=0;
    for (int i=0; i<12; i++) {
      snorm+=(1.0*random()/(RAND_MAX-1));
    }
    snorm -= 6.;
    snorm = fabs(snorm);
  } while (snorm > 1.);

  //std::cout << fabs(snorm) << std::endl;
  return snorm;
}

double intfunc(double y) {
  return 1./(2*M_PI)*exp(-y*y/2.);
}

int main(int argc, char **argv) {
  // Variables for Step-Integration: 
  int steps=1000000;
  int minrange=-2;
  int maxrange=2;
  int complrange=abs(minrange)+abs(maxrange);
  double integral=0;

  // Variables for Monte-Carlo-Integration: 
  int counts=1000000;
  srandom(1);
  
  for (double pos=minrange; pos<maxrange; pos+=(double) complrange/steps) {
    integral+=intfunc(pos);
    //std::cout << pos << std::endl;
  }
  std::cout << "Result by simple step-integration: " << integral/steps << std::endl;

  integral=0;
  for (int i=0; i<counts; i++) {
    integral+=intfunc(minrange+(complrange*fabs(snormrand())));
  }
  std::cout << "Result by snormrand() (standard normal) Monte-Carlo: " << integral/counts << std::endl;

  integral=0;
  for (int i=0; i<counts; i++) {
    integral+=intfunc(minrange+(complrange*random()/(RAND_MAX)));
  }
  std::cout << "Result by random() (uniform) Monte-Carlo: " << integral/counts << std::endl;
  
  return 0;
}
