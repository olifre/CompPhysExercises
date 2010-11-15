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

int main(int argc, char **argv) {
  int count=10000;
  double randz1, randz2;
  double randz1r, randz2r;
  srandom(1);

  f = new TFile("randoms.root","NEW");
  
  tree = new TTree("bmrand","Box-Muller distribution");
  
  tree->Branch("randz1",&randz1,"randz1/D");
  tree->Branch("randz2",&randz2,"randz2/D");

  std::ofstream f2;
  f2.open("randoms.dat" ) ;
  
  do {
    randz1r=(1.0*random()/(RAND_MAX));
    randz2r=(1.0*random()/(RAND_MAX));

    randz1=sqrt(-2*log(randz1r))*cos(2*M_PI*randz2r);
    randz2=sqrt(-2*log(randz1r))*sin(2*M_PI*randz2r);

    f2 << randz1 << "\t" << randz2 << std::endl;

    tree->Fill();
    count--;
  } while (count != 0);
  tree->Write();
  f->Close();
  f2.close();
  return 0;
}
