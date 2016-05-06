#include "stdafx.h"
#include "CppUnitTest.h"
#include "Primes.h"

using namespace CPAR;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest
{		
	TEST_CLASS(CalculatePrimeTest)
	{
	public:
		TEST_METHOD(ConvertToNumbersTest)
		{
			constexpr size_t size = 10;
			auto primesBooleanList = make_unique<bool[]>(size);
			primesBooleanList[0] = false;	// 3
			primesBooleanList[1] = false;	// 5
			primesBooleanList[2] = false;	// 7
			primesBooleanList[3] = true;	// 9
			primesBooleanList[4] = false;	// 11
			primesBooleanList[5] = false;	// 13
			primesBooleanList[6] = true;	// 15
			primesBooleanList[7] = false;	// 17
			primesBooleanList[8] = false;	// 19
			primesBooleanList[9] = true;	// 21

			auto primes = ConvertToNumbers(primesBooleanList.get(), size);
			Assert::AreEqual(static_cast<size_t>(7), primes.size());
			
			auto prime = primes.begin();
			Assert::AreEqual(static_cast<size_t>(3), *prime++);
			Assert::AreEqual(static_cast<size_t>(5), *prime++);
			Assert::AreEqual(static_cast<size_t>(7), *prime++);
			Assert::AreEqual(static_cast<size_t>(11), *prime++);
			Assert::AreEqual(static_cast<size_t>(13), *prime++);
			Assert::AreEqual(static_cast<size_t>(17), *prime++);
			Assert::AreEqual(static_cast<size_t>(19), *prime);
		}

		TEST_METHOD(PrimeTest)
		{
			constexpr size_t maximumLimit = 50;

			shared_ptr<bool> primesBooleanList;
			size_t size;
			CalculatePrimes(maximumLimit, primesBooleanList, size, 0);
			
			auto primes = ConvertToNumbers(primesBooleanList.get(), size);
			Assert::AreEqual(static_cast<size_t>(14), primes.size());

			auto prime = primes.begin();
			Assert::AreEqual(static_cast<size_t>(3), *prime++);
			Assert::AreEqual(static_cast<size_t>(5), *prime++);
			Assert::AreEqual(static_cast<size_t>(7), *prime++);
			Assert::AreEqual(static_cast<size_t>(11), *prime++);
			Assert::AreEqual(static_cast<size_t>(13), *prime++);
			Assert::AreEqual(static_cast<size_t>(17), *prime++);
			Assert::AreEqual(static_cast<size_t>(19), *prime++);
			Assert::AreEqual(static_cast<size_t>(23), *prime++);
			Assert::AreEqual(static_cast<size_t>(29), *prime++);
			Assert::AreEqual(static_cast<size_t>(31), *prime++);
			Assert::AreEqual(static_cast<size_t>(37), *prime++);
			Assert::AreEqual(static_cast<size_t>(41), *prime++);
			Assert::AreEqual(static_cast<size_t>(43), *prime++);
			Assert::AreEqual(static_cast<size_t>(47), *prime);
		}
	};
}