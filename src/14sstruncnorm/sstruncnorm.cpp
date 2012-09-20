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
TTree *tree2;

double density(double x) {
  return ((x>=0) && (x <= 1)) ? exp(-pow(x+3,2)/2.) : 0;
}

double invdensity(double u) {
  return ((u>=exp(-8)) && (u <= exp(-4.5))) ? -3+sqrt(2)*sqrt(-log(u)) : 0;
}

int main(int argc, char **argv) {
  int iter=100000;
  double x=0, u;
  double x2=0, u2, u2range;

  srandom(1);

  f = new TFile("sstruncnorm.root","NEW");

  tree = new TTree("truncnorm","slice-sampled truncated normal distribution");
  tree2 = new TTree("truncnormac","accept-rejected truncated normal distribution");
  
  tree->Branch("x",&x,"x/D");
  tree->Branch("u",&u,"u/D");
  
  for (int k = 0; k < iter; ++k) {
    u=(density(x)*random()/(RAND_MAX+1.));
    x=(invdensity(u)*random()/(RAND_MAX+1.));
    //std::cout << u << "-" << x << std::endl;
    tree->Fill();
  }

  tree->Write();

  tree2->Branch("x",&x2,"x/D");
  tree2->Branch("u",&u2,"u/D");

  u2range=exp(-4.5)-exp(-8);

  for (int k = 0; k < iter; ++k) {
    do {
      x2=(1.*random()/(RAND_MAX+1.));
      u2=(u2range*random()/(RAND_MAX+1.))+exp(-8);
    } while (u2 > density(x2));
    //std::cout << u2 << "-" << x2 << std::endl;
    tree2->Fill();
  }

  tree2->Write();
  f->Close();
  
  return 0;
}
