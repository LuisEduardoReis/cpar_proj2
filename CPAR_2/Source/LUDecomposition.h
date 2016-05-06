#pragma once

#include <array>

namespace CPAR
{
	template<typename ArrayType, size_t Lines, size_t Columns>
	using Matrix = std::array<std::array<ArrayType, Columns>, Lines>;

	template<typename ArrayType, size_t Size>
	void MatrixMultiply(const Matrix<ArrayType, Size, Size>& matrix1, const Matrix<ArrayType, Size, Size>& matrix2, Matrix<ArrayType, Size, Size>& output)
	{
		std::memset(output.data(), 0, Size*Size*sizeof(ArrayType));

		for (size_t i = 0; i < Size; ++i)
		{
			for (size_t j = 0; j < Size; ++j)
			{
				for (size_t k = 0; k < Size; ++k)
				{
					output[i][j] += matrix1[i][k] * matrix2[k][j];
				}
			}
		}
	}

	template<typename ArrayType, size_t Size>
	void Decompose(const Matrix<ArrayType, Size, Size>& matrix, Matrix<ArrayType, Size, Size>& l, Matrix<ArrayType, Size, Size>& u, Matrix<ArrayType, Size, Size>& p)
	{
		// Find pivot:
		{
			for (size_t i = 0; i < Size; ++i)
			{
				for (size_t j = 0; j < Size; ++j)
				{
					p[i][j] = (i == j);
				}
			}

			for (size_t i = 0; i < Size; ++i)
			{
				size_t maxJ = i;

				for (size_t j = i; j < Size; ++j)
				{
					if (std::fabs(matrix[j][i]) > std::fabs(matrix[maxJ][i]))
						maxJ = j;
				}

				if (maxJ != i)
				{
					for (size_t k = 0; k < Size; ++k)
					{
						auto temp = p[i][k];
						p[i][k] = p[maxJ][k];
						p[maxJ][k] = temp;
					}
				}
			}
		}

		std::memset(l.data(), 0, Size*Size*sizeof(ArrayType));
		std::memset(u.data(), 0, Size*Size*sizeof(ArrayType));

		Matrix<ArrayType, Size, Size> matrixPrime;
		MatrixMultiply(p, matrix, matrixPrime);

		for (size_t i = 0; i < Size; ++i)
			l[i][i] = 1.0;

		for (size_t i = 0; i < Size; ++i)
		{
			for (size_t j = 0; j < Size; ++j)
			{
				if(j <= i)
				{
					double sum = 0.0;
					for (size_t k = 0; k < j; ++k)
					{
						sum += l[j][k] * u[k][i];
					}
					u[j][i] = matrixPrime[j][i] - sum;
				}
				if(j >= i)
				{
					double sum = 0.0;
					for (size_t k = 0; k < i; ++k)
					{
						sum += l[j][k] * u[k][i];
					}
					l[j][i] = (matrixPrime[j][i] - sum) / u[i][i];
				}
			}
		}
	}
}
