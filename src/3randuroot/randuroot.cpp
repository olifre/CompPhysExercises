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
    a = atoi(argv[1]);
    m = atoi(argv[2]);
    num = atoi(argv[3]);
    std::cout << "Using a: " << a << std::endl;
    std::cout << "Using m: " << m << std::endl;
    std::cout << "Generating " << num << " points." << std::endl;
  }

  f = new TFile("randoms.root","NEW");
  
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
    num--;
  } while (num != 0);
  tree->Write();
  f->Close();
  return 0;
}
