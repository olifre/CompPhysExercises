#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>

TFile *f;
TTree *tree;

#define Cr 25
#define Ca 25

double density(double x) {
  return 1./2.*exp(-sqrt(x));
}

double invdensity(double u) {
  return pow(log(2*u),2);
}

int main(int argc, char **argv) {
  int iter=100000;
  double x=0, u;

  srandom(1);

  f = new TFile("slicesample.root","NEW");

  tree = new TTree("density","slice-sampled density");
  
  tree->Branch("x",&x,"x/D");
  tree->Branch("u",&x,"u/D");
  
  for (int k = 0; k < iter; ++k) {
    u=(density(x)*random()/(RAND_MAX+1.));
    x=(invdensity(u)*random()/(RAND_MAX+1.));
    //std::cout << u << "-" << x << std::endl;
    tree->Fill();
  }

  tree->Write();
  f->Close();
  
  return 0;
}
