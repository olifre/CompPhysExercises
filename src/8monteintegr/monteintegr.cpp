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
  return 1./sqrt(2*M_PI)*exp(-y*y/2.);
}

int main(int argc, char **argv) {
  // Variables for Step-Integration: 
  int steps=1000000;
  double minrange=-2;
  double maxrange=2;
  double complrange=fabs(minrange)+fabs(maxrange);
  double integral=0;
  double ehsq=0, eh=0;
  double temp;

  // Variables for Monte-Carlo-Integration: 
  int counts=1000000;
  srandom(1);
  
  for (double pos=minrange; pos<=maxrange; pos+=(double) complrange/steps) {
    integral+=intfunc(pos);
    //std::cout << pos << std::endl;
  }
  std::cout << "Result by simple step-integration: " << 4*integral/steps << std::endl;

  integral=0;
  for (int i=0; i<counts; i++) {
    temp=intfunc(minrange+(complrange*fabs(snormrand())));
    integral+=temp;
    ehsq+=temp*temp;
  }
  std::cout << "Result by snormrand() (standard normal) Monte-Carlo: " << 4*integral/counts << std::endl;
  eh=integral/counts*4;
  ehsq/=counts*4;
  std::cout << "With (E(h^2)): " << ehsq << std::endl;
  std::cout << "With (E(h))^2: " << eh*eh << std::endl;  
  std::cout << "So the variance is: " << ehsq-eh*eh << std::endl;
  
  eh=0;
  ehsq=0;
  integral=0;
  for (int i=0; i<counts; i++) {
    integral+=intfunc(minrange+(complrange*random()/(RAND_MAX)));
  }
  integral*=4;
  eh=integral/counts;
  ehsq/=counts*4;
  std::cout << "With (E(h^2)): " << (ehsq) << std::endl;
  std::cout << "With (E(h))^2: " << (eh*eh) << std::endl;  
  std::cout << "So the variance is: " << (ehsq-eh*eh) << std::endl;
  std::cout << "Result by random() (uniform) Monte-Carlo: " << integral/counts << std::endl;
  
  return 0;
}
