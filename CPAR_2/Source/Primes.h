#pragma once

#include <list>
#include <vector>
#include <memory>
#include <cstring>

namespace CPAR
{
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

	inline void CalculatePrimes(size_t maximumLimit, std::shared_ptr<bool>& result, size_t& size, size_t ompThreads)
	{
		using namespace std;

		size = maximumLimit / static_cast<size_t>(2) - static_cast<size_t>(1);
		result = shared_ptr<bool>(new bool[size], default_delete<bool[]>());
		
		auto primes = result.get();
		memset(primes, 0, size);

		if(ompThreads == 0)
		{
			for (size_t k = 3; k*k <= maximumLimit; )
			{
				// Mark multiples in [k^2, maximumLimit]:
				for (size_t i = k*k; i <= maximumLimit; i += k)
				{
					// If even, continue:
					if (i % static_cast<size_t>(2) == static_cast<size_t>(0))
						continue;

					primes[(i - static_cast<size_t>(3)) >> static_cast<size_t>(1)] = true;
				}

				// Find lowest unmarked number:
				do { k += static_cast<size_t>(2); } while (primes[(k - static_cast<size_t>(3)) >> static_cast<size_t>(1)]);
			};
		}
		else
		{
			for (size_t k = 3; k*k <= maximumLimit; )
			{
				// Mark multiples in [k^2, maximumLimit]:
				#pragma omp parallel for num_threads(ompThreads)
				for (size_t i = k*k; i <= maximumLimit; i += k)
				{
					// If even, continue:
					if (i % 2 == 0)
						continue;

					primes[(i - 3) >> 1] = true;
				}


				// Find lowest unmarked number:
				do { k += 2; } while (primes[(k - 3) >> 1]);
			};
		}
	}
}
