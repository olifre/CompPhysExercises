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

double H(double p) {
  return (p*p/2.);
}

double analyt(double d) {
  return (d/2.*pow(2*M_PI,d/2.));
}

// Box-Muller Polar Method:
double boxmullp() {
  // Variables for Box-Muller
  double randz1, randz2;
  double randz1r, randz2r;
  double q, p;
  
  do {
    randz1r=(2.0*random()/(RAND_MAX))-1.0;
    randz2r=(2.0*random()/(RAND_MAX))-1.0;
    
    q=randz1r*randz1r+randz2r*randz2r;
    p=sqrt(-2*log(q)/q);
    
    randz1=randz1r*p;
    randz2=randz2r*p;
  } while (2*log(q)/q>0);
  return randz1;
}

// Box-Muller Slower Polar Method:
double boxmull() {
  double randz1, randz2;
  double randz1r, randz2r;

  randz1r=(1.0*random()/(RAND_MAX));
  randz2r=(1.0*random()/(RAND_MAX));
  
  randz1=sqrt(-2*log(randz1r))*cos(2*M_PI*randz2r);
  randz2=sqrt(-2*log(randz1r))*sin(2*M_PI*randz2r);
  return randz1;
}

int main(int argc, char **argv) {
  //int counts=10000;
  double integral=0, Hsum=0;
  double simpleint;
  double simplevar;
  double impint;
  double impvar;
  double x;
  double eh=0;
  double ehsq=0;
  int d, dout=3;
  int n, nout=10000;
  double temp;
  double kappa=10;
  double analytic=0;
  srandom(1);
  
  std::ofstream outfiled;
  std::ofstream outfilen;
  outfiled.open("datad.dat");
  outfilen.open("datan.dat");

  for (d=1; d<200; d++) {
    if (d!=dout) {
      n=nout;
    } else {
      n=0;
    }
    if (d%20==0) std::cout << "Using d=" << d << std::endl;
    for (; n<=nout; ++n) {
      if (n%100==0) std::cout << "Using n=" << n << " with d=" << d << std::endl;
      analytic=analyt(d);
      
      integral=0;
      // ehsq=0;
      for (int i=0; i<n; i++) {
	Hsum=0;
	for (int j=0; j<d; j++) {
	  Hsum+=H(kappa*random()/(RAND_MAX+1.));
	}
	temp=Hsum*exp(-Hsum);
	// ehsq+=temp*temp;
	integral+=temp;
      }
      integral*=pow(2*kappa,d);
      // eh=integral/counts;
      // ehsq/=counts;
      // ehsq*=pow(2*kappa,d);
      
      if ((d==dout) && (n==nout)) {
	std::cout << "Now using simple sampling:" << std::endl;
	// std::cout << "With (E(h^2)): " << (ehsq) << std::endl;
	// std::cout << "With (E(h))^2: " << (eh*eh) << std::endl;  
	// std::cout << "So the variance is: " << (ehsq-eh*eh)/counts << std::endl;
	std::cout << "Result by random() (uniform) Monte-Carlo: " << integral/n << std::endl;
	std::cout << "And analytically: " << analytic<< std::endl;
	std::cout << "Variance: " << pow(analytic-integral/n,2) << std::endl;
	std::cout << std::endl;
      }
      
      simpleint=integral/n;
      simplevar=pow(analytic-integral/n,2);
      
      // Importance Sampling:
      if ((d==dout) && (n==nout)) {
	std::cout << "Now using importance sampling:" << std::endl;
      }
      integral=0;
      for (int i=0; i<n; i++) {
	Hsum=0;
	for (int j=0; j<d; j++) {
	  Hsum+=H(boxmull());
	}
	//std::cout << boxmull() << std::endl;
	temp=Hsum;
	// ehsq+=temp*temp;
	integral+=temp;
      }
      integral*=pow(2*M_PI,d/2.);
      if ((d==dout) && (n==nout)) {
	std::cout << "Result by importance sampling: " << integral/n << std::endl;
	std::cout << "And analytically: " << analyt(d) << std::endl;
	std::cout << std::endl;
      }
      
      impint=integral/n;
      impvar=pow(analytic-integral/n,2);
      outfilen << n << "\t" << simpleint << "\t" << simplevar << "\t" << impint << "\t" << impvar << "\t" << analytic << std::endl;
    }	
    // Output to file: 
    outfiled << d << "\t" << simpleint << "\t" << simplevar << "\t" << impint << "\t" << impvar << "\t" << analytic << std::endl;
  }
  
  outfiled.close();
  outfilen.close();
  
  return 0;
}
