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

double randu(long int a, long int m, long int x) {
  return a*x % m;
}

int main(int argc, char **argv) {
  int count=10000;
  long int randzp1, randzp2;
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
 
  randz1r=1;
  randz2r=1;

  do {
    randzp1 = randu(65539, 2147483648, randzp2);
    randzp2 = randu(65539, 2147483648, randzp1);
    
    randz1r=2.0*((double)randzp1/(2147483648))-1.0;
    randz2r=2.0*((double)randzp2/(2147483648))-1.0;
    //std::cout << randz1r << "\t" << randz2r << std::endl;

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
