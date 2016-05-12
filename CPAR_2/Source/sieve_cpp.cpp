#include <cstdlib>
#include <iostream>

#include "Primes.h"
#include "Profiler.h"

using namespace CPAR;
using namespace std;

int main(int argc, char** argv) 
{
	do {
		// Input
		size_t range, n_omp;
		if (argc >= 2) {
			range = atoi(argv[1]);
			
			if (argc < 3) n_omp = 0;
			else n_omp = atoi(argv[2]);
			
			if (range > 32) range = 32;
			if (range < 1) range = 1;
		} else {
			if (!(cin >> range)) break;
			if (!(cin >> n_omp)) break;
		};

		// Define the superior limit:
		size_t limit = static_cast<size_t>(1) << range;	

		// Calculate primes
		Profiler profiler;
		shared_ptr<bool> primesBooleanList;
		size_t size;
		{
			// Start profiler:
			profiler.Start();

			// Calculate primes:
			CalculatePrimes(limit, primesBooleanList, size, n_omp);

			// End profiler:
			profiler.End();
		}
		

		// Convert list of booleans to integers:
		//auto primes = ConvertToNumbers(primesBooleanList.get(), size);

		// Output
		cout << range << " ";
		cout << n_omp << " ";
		cout << CountPrimes(primesBooleanList.get(), size) << " ";
		cout << profiler.ElapsedTime<double, ratio<1>>().count();
		cout << endl;

	} while(argc < 2);

	return 0;
}
