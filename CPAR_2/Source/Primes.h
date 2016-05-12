#pragma once

#include <list>
#include <vector>
#include <memory>
#include <cstring>

#define NUM_2_MEM(n) ((n-3)>>1)
#define MEM_2_NUM(n) ((n<<1)+3)


namespace CPAR
{

	inline void CalculatePrimes(size_t limit, std::shared_ptr<bool>& result, size_t& size, size_t n_omp)
	{
		using namespace std;

		size = limit / 2 - 1;
		result = shared_ptr<bool>(new bool[size], default_delete<bool[]>());
		
		auto primes = result.get();
		for(size_t i = 0; i < size; i++) primes[i] = false;

		if(n_omp == 0)	{
			for (size_t k = 3; k*k <= limit; ) {
				// Mark multiples in [k^2, limit]:
				for (size_t i = k*k; i <= limit; i += k)	{
					// If even, continue:
					if (i & 1 == 0)	continue;

					// Mark
					primes[NUM_2_MEM(i)] = true;
				}

				// Find lowest unmarked number:
				do { k += 2; } while (primes[NUM_2_MEM(k)]);
			};			
		} else {
			for (size_t k = 3; k*k <= limit; ) {
				// Mark multiples in [k^2, limit]:
				#pragma omp parallel for num_threads(n_omp)
				for (size_t i = k*k; i <= limit; i += k)	{
					// If even, continue:
					if (i & 1 == 0)	continue;

					// Mark
					primes[NUM_2_MEM(i)] = true;
				}

				// Find lowest unmarked number:
				do { k += 2; } while (primes[NUM_2_MEM(k)]);
			};
		}
	}
	
	inline std::list<size_t> ConvertToNumbers(const bool* primes, size_t size)
	{
		using namespace std;

		auto output = list<size_t>();
		output.push_back(2);

		for (size_t i = 0; i < size; ++i)
		{
			if (!primes[i])
				output.push_back((i * 2) + 3);
		}

		return output;
	}
	
	inline size_t CountPrimes(const bool* primes, size_t size) {
		
		size_t count = 1;
		for (size_t i = 0; i < size; i++) {
			if (!primes[i]) count++;
		};
		
		return count;
	}
}
