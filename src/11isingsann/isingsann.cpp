#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

#define N 25
#define J 1

double hamiltonian(int lattice[N][N])  {
  int sum=0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      sum+=lattice[i][j]*lattice[(i+1)%N][j];
      sum+=lattice[i][j]*lattice[i][(j+1)%N];
      sum+=lattice[i][j]*lattice[(i-1+N)%N][j];
      sum+=lattice[i][j]*lattice[i][(j-1+N)%N];
    }
  }
  return -1./2.*J*sum;
}

int printLattice(int lattice[N][N]) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j)	{
      //std::cout << ((lattice[i][j] == 1) ? "+" : "-") << " ";
      std::cout << ((lattice[i][j] == 1) ? "\033[0;35mU\033[0m" : "\033[0;34mD\033[0m") << " ";
      //std::cout << ((lattice[i][j] == 1) ? "+" : "-") << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "Energy: " << hamiltonian(lattice) << std::endl;;
}

int randLattice(int lattice[N][N]) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j)	{
      lattice[i][j]=((1.0*random()/(RAND_MAX+1.))>0.5) ? -1 : 1;
    }
  }
}

int flipSpinR(int lattice[N][N], double *T, int k) {
  int i=(N*1.0*random()/(RAND_MAX+1.));
  int j=(N*1.0*random()/(RAND_MAX+1.));
  double oldHam=hamiltonian(lattice);
  double newHam, deltaH;
  deltaH=oldHam;
  lattice[i][j]*=-1;
  newHam=hamiltonian(lattice);
  deltaH=newHam-deltaH;
  //std::cout << "Flipped, Delta H: " << deltaH << std::endl;
  double p=std::min(1.,exp(-deltaH / (*T)));
  //std::cout << "p=" << p << std::endl;
  if ((1.0*random()/(RAND_MAX+1.)) <= p) {
    //std::cout << "Taken." << std::endl;
    (*T)=1/log(k);
    deltaH=newHam;
  } else {
    //std::cout << "Not taken." << std::endl;
    lattice[i][j]*=-1;
    deltaH=oldHam;
  }
}

int flipSpins(int lattice[N][N], double *T, int k) {
  //int i=(N*1.0*random()/(RAND_MAX+1.));
  //int j=(N*1.0*random()/(RAND_MAX+1.));
  double oldHam=hamiltonian(lattice);
  double newHam, deltaH;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      deltaH=oldHam;
      lattice[i][j]*=-1;
      newHam=hamiltonian(lattice);
      deltaH=newHam-deltaH;
      //std::cout << "Flipped, Delta H: " << deltaH << std::endl;
      double p=std::min(1.,exp(-deltaH / (*T)));
      //std::cout << "p=" << p << std::endl;
      if ((1.0*random()/(RAND_MAX+1.)) <= p) {
	//std::cout << "Taken." << std::endl;
	(*T)=1/log(k);
	deltaH=newHam;
      } else {
	//std::cout << "Not taken." << std::endl;
	lattice[i][j]*=-1;
	deltaH=oldHam;
      }
    }
  }
}

int main(int argc, char **argv) {
  int lattice[N][N];
  int iter=1000000;
  int printstep=100;
  int nanoseconds=100000;
  timespec sleepPeriod = { 0, nanoseconds };
  timespec unusedPeriod;

  srandom(1);
  
  double T=1;
  randLattice(lattice);

  for (int k = 0; k < iter; ++k) {
    if (k%printstep==0) {
      nanosleep(&sleepPeriod, &unusedPeriod);
      system("clear");
      std::cout << "Iteration: " << k << std::endl;
      printLattice(lattice);
    }
    flipSpinR(lattice,&T,k);
    if (k%printstep==0) 
      std::cout << "Temperature: " << T << std::endl;
  }
  

  return 0;
}
