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

double f(double x) {
  return (1-cos(x))/(x*x);
}

double g(double x) {
  if (x<=1) 
    return 1./2.;
  else 
    return 1./(2.*x*x);
}

double Ginv(double y) {
  if (y<=1./2.) 
    return 2*y; 
  else
    return 1./(2.*(1-y));
}

double h(double x) {
  return x;
}

int main(int argc, char **argv) {
  // Variables for Step-Integration: 
  int steps=1000000;
  double minrange=0.0000001;
  double maxrange=1E2;
  double complrange=abs(minrange)+abs(maxrange);
  double integral=0;
  double x;
  srandom(1);
  
  for (double pos=minrange; pos<maxrange; pos+=(double) complrange/steps) {
    integral+=f(pos);
    //std::cout << pos << std::endl;
  }
  std::cout << "Result by simple step-integration: " << integral/steps << std::endl;
  
  integral=0;
  for (int i=0; i<steps; i++) {
    x=1.0*((double) random()/(RAND_MAX-1));
    //std::cout << x << std::endl;
    integral+=f(Ginv(x))/g(Ginv(x));
    //std::cout << pos << std::endl;
  }
  std::cout << "Result by simple step-integration: " << integral/steps << std::endl;

  
  
  return 0;
}
