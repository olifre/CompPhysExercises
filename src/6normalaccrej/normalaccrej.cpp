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
  
  tree = new TTree("accrej","Sample by Accept-Reject Algorithm");
  
  tree->Branch("randz1",&randz1,"randz1/D");
  tree->Branch("randz2",&randz2,"randz2/D");

  std::ofstream f2;
  f2.open("randoms.dat" ) ;
  
  do {
    do {
      randz1=(2.0*random()/(RAND_MAX))-1;
      randz2=(2.0*random()/(RAND_MAX))-1;
    } while (randz2 > exp(-1./2.*(randz1-1)*(randz1-1)));
	
    f2 << randz1 << "\t" << randz2 << std::endl;

    tree->Fill();
    count--;
  } while (count != 0);
  tree->Write();
  f->Close();
  f2.close();
  return 0;
}
