#pragma once

#include "LUDecomposition.h"
#include "CppUnitTest.h"

namespace UnitTest
{
	template<typename ArrayType, size_t Lines, size_t Columns>
	void AreEqual(const CPAR::Matrix<ArrayType, Lines, Columns>& expected, const CPAR::Matrix<ArrayType, Lines, Columns>& actual, double tolerance = 0.00001)
	{
		using namespace Microsoft::VisualStudio::CppUnitTestFramework;

		for (size_t i = 0; i < Lines; ++i)
		{
			for (size_t j = 0; j < Columns; ++j)
			{
				Assert::AreEqual(expected[i][j], actual[i][j], tolerance);
			}
		}
	}
}