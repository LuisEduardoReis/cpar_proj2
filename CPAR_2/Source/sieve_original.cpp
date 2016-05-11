#include "stdlib.h"
#include <sys/time.h>
#include <iostream>
#include <vector>

using namespace std;


int main(int argc, char** argv) {		
	int range, n_omp;
	bool* list;
	size_t k, num, n, one = 1;
	timespec Time1, Time2;
	
	do {
		// Input
		if (argc >= 3) {
			range = atoi(argv[1]);
			if (argc < 3) n_omp = 0;
			else n_omp = atoi(argv[2]);
			if (range > 32) range = 32;
			if (range < 1) range = 1;
		} else {
			if (!(cin >> range)) break;
			if (!(cin >> n_omp)) break;
		}
		
			
		n = (((size_t)1) << range);
		//vector<bool> list = vector<bool>(n/2-1,false);		
		list = new bool[n/2-1];
		for(size_t i = 0; i < n/2-1; i++) list[i] = false;
		
		// Start timer
		clock_gettime(CLOCK_REALTIME, &Time1);

		// Calculate primes		
		if (n_omp == 0) {
			for(k = 3; k*k <= n;) {
				for(size_t i = k*k; i <= n; i+=k) {
					if ((i & 1) == 0) continue;
					list[(i-3)>>1] = true;
				}
				do {k+=2;} while(list[(k-3)>>1]);
			};
		} else {
			for(k = 3; k*k <= n;) {
				#pragma omp parallel for num_threads(n_omp)
				for(size_t i = k*k; i <= n; i+=k) {
					if ((i & 1) == 0) continue;
					list[(i-3)>>1] = true;
				}
				do {k+=2;} while(list[(k-3)>>1]);
			};
		}
		
		// Count primes
		num = 1;
		for(size_t i = 0; i < n/2-1; i++) {
			if (!list[i]) num++;
		}	
	
		//Stop timer
		clock_gettime(CLOCK_REALTIME, &Time2);
		
		double t1 = Time1.tv_sec + ((double)Time1.tv_nsec)/1e9;
		double t2 = Time2.tv_sec + ((double)Time2.tv_nsec)/1e9;
		
		// Output
		cout << range << " ";
		cout << n_omp << " ";
		cout << num << " ";
		cout << (t2 - t1) << endl;
			
		delete list;
	} while (argc < 3);
	

	
	return 0;
}
