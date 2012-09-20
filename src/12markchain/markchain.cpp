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

double ljPot(double r) {
  return Cr/pow(r,12)-Ca/pow(r,6)+r*r;
}

double takeCondition(double oldP, double newP) {
  return std::min(1.,exp(-(ljPot(newP)-ljPot(oldP))));
}

int main(int argc, char **argv) {
  int iter=10000000;
  double px=1, py;
  double stepsize=0.1;

  srandom(1);

  f = new TFile("markchain.root","NEW");

  tree = new TTree("ljones","Lennard-Jones Potential");
  
  tree->Branch("configs",&px,"config/D");
  
  for (int k = 0; k < iter; ++k) {
    py=px+stepsize*(1.0*random()/(RAND_MAX+1.)-0.5);
    if ((1.0*random()/(RAND_MAX+1.)) < takeCondition(px,py)) {
      px=py;
    }
    tree->Fill();
  }

  tree->Write();
  f->Close();
  
  return 0;
}
