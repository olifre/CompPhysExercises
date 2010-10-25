#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

double doWalk(int maxLen)
{
	int x=0, y=0, i, r;
	for (i=0; i<maxLen; i++) {
		r=(random()/(RAND_MAX/4.));
		//std::cout << (4*random()/(RAND_MAX+1.0)) << std::endl;
		if (r==3) {
			x--;
			continue;
		}
		if (r==2) {
			y++;
			continue;
		}
		if (r==1) {
			x++;
			continue;
		}
		if (r==0) {
			y--;
			continue;
		}
	}
	//std::cout << x << "\t" << y << "\t" << maxlen << std::endl;
	return (sqrt(x*x+y*y));
}

int main(int argc, char **argv)
{
	int i, j;
	double dist=0;
	double tries=10000;
	int maxSteps=5000;
	for (j=0; j<=maxSteps; j++) {
		//srandom(1);
		dist=0;
		for (i=0; i<tries; i++) {
			dist+=doWalk(j);
			//std::cout << doWalk(10) << std::endl;
		}
		std::cout << j << "\t" << dist/tries << std::endl;
	}
}
