#include <cstdlib>
#include <iostream>

#include "Primes.h"
#include "Profiler.h"

using namespace CPAR;
using namespace std;

int main(int argc, char** argv) 
{
	// Return if wrong number of arguments:
	if (argc < 2)
	{
		cout << "usage: range [omp_threads]" << endl;
		return -1;
	}
	
	// Parse range:
	int range = atoi(argv[1]);
	if (range > 32) range = 32;
	else if (range < 1) range = 1;

	// Define the superior limit:
	size_t maximumLimit = static_cast<size_t>(1) << static_cast<size_t>(range);

	// Parse the number of OMP Threads to use:
	size_t ompThreads = argc < 3 ? 0 : atoi(argv[2]);

	// Calculate primes
	Profiler profiler;
	vector<bool> primesBooleanList;
	size_t size;
	{
		// Start profiler:
		profiler.Start();

		// Calculate primes:
		CalculatePrimes(maximumLimit, primesBooleanList, size, ompThreads);

		// End profiler:
		profiler.End();
	}

	// Convert list of booleans to integers:
	auto primes = ConvertToNumbers(primesBooleanList, size);

	cout << "Number of primes found: " << primes.size() << endl;
	cout << "Elapsed time: " << profiler.ElapsedTime<double, ratio<1>>().count() << " seconds" << endl;
	cin.get();

	return 0;
}
