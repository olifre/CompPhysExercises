#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>

TFile *f;
TTree *tree;

double snormrand() {
  int i=0;
  double snorm=0;
  for (i=0; i<12; i++) {
    snorm+=(1.0*random()/(RAND_MAX));
  }
  snorm -= 1./6.;
  return snorm;
}

int main(int argc, char **argv) {
  int count=1000000;
  double srandnum;
  srandom(1);

  f = new TFile("randoms.root","NEW");
  
  tree = new TTree("srtree","SRAND() distribution");
  
  tree->Branch("randnums",&srandnum,"randnum/D");
  
  do {
    srandnum = snormrand();
    //std::cout << snormrand() << std::endl;
    tree->Fill();
    count--;
  } while (count != 0);
  tree->Write();
  f->Close();
}
