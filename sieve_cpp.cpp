#include "stdlib.h"
#include <sys/time.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	if (argc < 2) {return -1;}
		
	int range, n_omp;
	size_t k, num, n;
	bool* list;
	timespec Time1, Time2;
	
	range = atoi(argv[1]);
	if (argc < 3) n_omp = 0;
	else n_omp = atoi(argv[2]);
	if (range > 32) range = 32;
	if (range < 1) range = 1;
	
	
	// Calculate primes
	n = (1 << range);
	list = new bool[n/2-1];
	for(int i = 0; i < n/2-1; i++) list[i] = false;
	
	clock_gettime(CLOCK_REALTIME, &Time1);
	if (n_omp == 0) {
		for(k = 3; k*k <= n;) {
			for(size_t i = k*k; i <= n; i+=k) {
				list[(i-3)<<1] = true;
			}
			do {k+=2;} while(list[(k-3)<<1]);
		};
	} else {
		for(k = 3; k*k <= n;) {
			#pragma omp parallel for num_threads(n_omp)
			for(size_t i = k*k; i <= n; i+=k) {
				list[(i-3)<<1] = true;
			}
			do {k+=2;} while(list[(k-3)<<1]);
		};
	}
	clock_gettime(CLOCK_REALTIME, &Time2);
	
	double t1 = Time1.tv_sec + ((double)Time1.tv_nsec)/1e9;
	double t2 = Time2.tv_sec + ((double)Time2.tv_nsec)/1e9;
	
	// Count primes
	num = 1;
	for(size_t i = 0; i < n/2-1; i++) {
		if (!list[i]) num++;
	}	
	
	cout << num << " " << (t2 - t1) << endl;
	
	delete list;	
	return 0;
}
