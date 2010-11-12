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
  long int a, m, num;
  double randx,randy,randz;
  long int xi=1;
  if (argc!=4) {
    std::cerr << "Expecting parameters 'a m num' on terminal." << std::endl;
    std::cerr << "Instead, I received " << argc << " parameters." << std::endl;
    std::cerr << "Please call me with: '" << argv[0] << " a m num'" << std::endl;
    return -1;
  } else { 
    //std::cout << argv[0] << std::endl;
    a = atol(argv[1]);
    m = atol(argv[2]);
    num = atol(argv[3]);
    std::cout << "Using a: " << a << std::endl;
    std::cout << "Using m: " << m << std::endl;
    std::cout << "Generating " << num << " points." << std::endl;
  }

  f = new TFile("randoms.root","NEW");

  std::ofstream f2;
  f2.open("randoms.dat" ) ;

  tree = new TTree("srtree","RANDU() points");
  
  tree->Branch("randnumx",&randx,"randx/D");
  tree->Branch("randnumy",&randy,"randy/D");
  tree->Branch("randnumz",&randz,"randz/D");
  
  do {
    randx=randu(a,m,xi);
    randy=randu(a,m,randx);
    randz=randu(a,m,randy);
    xi=(int) randx;
    randx/=m;
    randy/=m;
    randz/=m;
    tree->Fill();
    f2 << randx << "\t" << randy << "\t" << randz << std::endl;
    num--;
  } while (num != 0);
  tree->Write();
  f->Close();
  f2.close();
  return 0;
}
