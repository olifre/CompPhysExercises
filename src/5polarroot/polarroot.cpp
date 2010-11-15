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
  double q, p;
  srandom(1);

  f = new TFile("randoms.root","NEW");
  
  tree = new TTree("polarrand","Polar distribution");
  
  tree->Branch("randz1",&randz1,"randz1/D");
  tree->Branch("randz2",&randz2,"randz2/D");

  std::ofstream f2;
  f2.open("randoms.dat" ) ;
  
  do {
    randz1r=(2.0*random()/(RAND_MAX))-1.0;
    randz2r=(2.0*random()/(RAND_MAX))-1.0;
    
    q=randz1r*randz1r+randz2r*randz2r;
    p=sqrt(-2*log(q)/q);
    
    randz1=randz1r*p;
    randz2=randz2r*p;
    
    f2 << randz1 << "\t" << randz2 << std::endl;
    
    tree->Fill();
    count--;
  } while (count != 0);
  tree->Write();
  f->Close();
  f2.close();
  return 0;
}
