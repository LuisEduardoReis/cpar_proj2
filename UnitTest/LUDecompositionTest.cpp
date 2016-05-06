#include "stdafx.h"
#include "CppUnitTest.h"
#include "LUDecomposition.h"
#include "TestUtils.h"

using namespace CPAR;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(LUDecompositionTest)
	{
	public:
		TEST_METHOD(DecompositionTest)
		{
			constexpr size_t size = 3;
			Matrix<double, size, size> matrix =
			{
					{
						{ 1, 3, 5 },
						{ 2, 4, 7 },
						{ 1, 1, 0 },
					}
			};

			Matrix<double, size, size> actualL;
			Matrix<double, size, size> actualU;
			Matrix<double, size, size> actualP;
			Decompose(matrix, actualL, actualU, actualP);

			Matrix<double, size, size> expectedL =
			{
					{
						{ 1.0, 0.0, 0.0 },
						{ 0.5, 1.0, 0.0 },
						{ 0.5, -1.0, 1.0 },
					}
			};
			Matrix<double, size, size> expectedU =
			{
				{
					{ 2.0, 4.0, 7.0 },
					{ 0.0, 1.0, 1.5 },
					{ 0.0, 0.0, -2.0 },
				}
			};
			Matrix<double, size, size> expectedP =
			{
				{
					{ 0.0, 1.0, 0.0 },
					{ 1.0, 0.0, 0.0 },
					{ 0.0, 0.0, 1.0 },
				}
			};

			AreEqual(expectedP, actualP);
			AreEqual(expectedU, actualU);
			AreEqual(expectedL, actualL);
		}
	};
}