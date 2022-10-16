#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <immintrin.h>

#define N 1000

int compare_matrices(int mat1[N][N], int mat2[N][N])
{
	int i, j;
	for (i = 0; i < N; ++i) for (j = 0; j < N; ++j)
		if (mat1[i][j] != mat2[i][j])
			return 0;
	return 1;
}

void version1(int mat1[N][N], int mat2[N][N], int result[N][N])
{
	
	int i, j, k;
	//row-major order matrix multiplication
	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			//multiply each cell in mat1 row i with corresponding cell in column of mat2 column j
			for (k = 0; k < N; ++k)
				result[i][j] += mat1[i][k] * mat2[k][j];
		}
	}
}

void version2(int mat1[N][N], int mat2[N][N], int result[N][N])
{
	int i, j, k;
	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			for (k = 0; k < N; ++k)
				//each cell will be multiplied from row j mat 1 with correspondning cell column i in mat2
				result[j][i] += mat1[j][k] * mat2[k][i];
		}
	}
}

void version3(int mat1[N][N], int mat2[N][N], int result[N][N])
{
	int i, j, k;
	//each cell in mat 1 row i is involved in calculating the cells in row i result
	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			//store value of mat 1 cell into r integer to then use that to be added into result, it is more effecient.
			int r = mat1[i][j];
			
			for (k = 0; k < N; ++k)
				result[i][k] += r * mat2[j][k];
		}
	}
}

void version4(int mat1[N][N], int mat2[N][N], int result[N][N])
{
	int BLOCK = 50;

	//1 loop blocking
	/*
	for (int kk = 0; kk < N; kk += BLOCK)
	{
		for (int i = 0; i < N; ++i)
		{
			for (int k = kk; k < kk + BLOCK; ++k)
			{
				int r = mat1[i][k];
				for (int j = 0; j < N; ++j)
					result[i][j] += r * mat2[k][j];
			}
		}
	}
	*/

	//3 loop blocking
	//split into smaller blocks to reduce the working set of data then concentrate on the small blocks, this will have less cache misses.
	for (int ii = 0; ii < N; ii += BLOCK) {
		for (int jj = 0; jj < N; jj += BLOCK) {
			for (int kk = 0; kk < N; kk += BLOCK) {
				for (int i = ii; i < ii + BLOCK; i++) {
					for (int j = jj; j < jj + BLOCK; j++) {
						int r = 0;
						for (int k = kk; k < kk + BLOCK; k++) {
							r += mat1[i][k] * mat2[k][j];
						}
						result[i][j] = r + result[i][j];
					}
				}
			}
		}
	}
}

void version5(int mat1[N][N], int mat2[N][N], int result[N][N])
{
	//AVX

	//init to zero (registers)
	__m256i sum_vec = _mm256_setzero_si256();
	__m256i mat1_vec = _mm256_setzero_si256();
	__m256i mat2_vec = _mm256_setzero_si256();

	int i, j, k;
	for (i = 0; i < N; i += 8)
	{
		for (j = 0; j < N; ++j)
		{
			//take 8 from one row and insert into mat2_vec
			//sets them in reversed order the supplied values
			mat2_vec = _mm256_setr_epi32(mat2[i][j], mat2[i + 1][j], mat2[i + 2][j], mat2[i + 3][j], mat2[i + 4][j], mat2[i + 5][j], mat2[i + 6][j], mat2[i + 7][j]);
			for (k = 0; k < N; ++k)
			{
				//load integer data into the destination (register)
				mat1_vec = _mm256_loadu_si256(&mat1[k][i]);
				//matrix multiplication
				sum_vec = _mm256_add_epi32(sum_vec, _mm256_mullo_epi32(mat1_vec, mat2_vec));
				result[k][j] += _mm256_extract_epi32(sum_vec, 0) + _mm256_extract_epi32(sum_vec, 1) + _mm256_extract_epi32(sum_vec, 2) + _mm256_extract_epi32(sum_vec, 3) + _mm256_extract_epi32(sum_vec, 4) + _mm256_extract_epi32(sum_vec, 5) + _mm256_extract_epi32(sum_vec, 6) + _mm256_extract_epi32(sum_vec, 7);
				sum_vec = _mm256_setzero_si256(); 
			}
		}
	}


	//done similarly as avx but 4 values are taken instead of 8.
	//SSE
	/*
	__m128i sum_vec = _mm_setzero_si128();
	__m128i mat1_vec = _mm_setzero_si128();
	__m128i  mat2_vec = _mm_setzero_si128();
	int i, j, k;
	for (i = 0; i < N; i += 4)
	{
		for (j = 0; j < N; ++j)
		{
			mat2_vec = _mm_setr_epi32(mat2[i][j], mat2[i + 1][j], mat2[i + 2][j], mat2[i + 3][j]);
			for (k = 0; k < N; ++k)
			{
				mat1_vec = _mm_loadu_si128(&mat1[k][i]);
				sum_vec = _mm_add_epi32(sum_vec, _mm_mullo_epi16(mat1_vec, mat2_vec));
				result[k][j] += _mm_extract_epi32(sum_vec, 0) + _mm_extract_epi32(sum_vec, 1) + _mm_extract_epi32(sum_vec, 2) + _mm_extract_epi32(sum_vec, 3);
				sum_vec = _mm_setzero_si128();
			}
		}
	}*/

}

void version6(int mat1[N][N], int mat2[N][N], int result[N][N]) {

	//init to zero
	__m256i _mat1 = _mm256_setzero_si256();
	__m256i _mat2 = _mm256_setzero_si256();
	__m256i _multiply = _mm256_setzero_si256();

	/*
	int i, j, k;
	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			for (k = 0; k < N; ++k)
				result[i][k] += mat1[i][j] * mat2[j][k];
		}
	}
	*/
	int i, j, k;
	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			//load integer into register
			_mat1 = _mm256_loadu_si256(&mat1[i][j]);

			for (k = 0; k < N; ++k) {

				_mat2 = _mm256_loadu_si256(&mat2[j][k]);
				//store _mat2 * _mat1 into result matrix.

				//multiply mat1 value with mat 2 value then add into result.
				_multiply = _mm256_add_epi32(_multiply, _mm256_mullo_epi32(_mat1, _mat2));
				result[i][k] += _mm256_extract_epi32(_multiply, 0);
				_multiply = _mm256_setzero_si256();
			}

		}
	}

}

int mat_a[N][N], mat_b[N][N], mat_r[N][N], mat_ref[N][N];

void init_matrices()
{
	int i, j;
	srand(0xBADB0LL);
	for (i = 0; i < N; ++i) for (j = 0; j < N; ++j)
	{
		mat_a[i][j] = rand() % 10;
		mat_b[i][j] = rand() % 10;
		mat_r[i][j] = 0;
		mat_ref[i][j] = 0;
	}
}

int main(void)
{
	clock_t t0, t1;

	for (int i = 0; i < 5; i++) {

		init_matrices();

		//printf("Making reference matrix for error checking.\n");
		version1(mat_a, mat_b, mat_ref);

		//printf("Started your matrix multiplication.\n");

		t0 = clock();

		// Run the algorithm (uncomment the right version to compile it)
		//version1(mat_a, mat_b, mat_r);
		//version2(mat_a, mat_b, mat_r);
		//version3(mat_a, mat_b, mat_r); 
		//version4(mat_a, mat_b, mat_r); 
		version5(mat_a, mat_b, mat_r);

		t1 = clock();

		printf("Finished in %lf seconds.\n", (double)(t1 - t0) / CLOCKS_PER_SEC);
		if (!compare_matrices(mat_r, mat_ref))
			printf("Error: mat_r does not match the reference matrix!\n");
		//else
			//printf("Correct!\n");

	}

#ifdef _MSC_VER
	system("pause");
#endif

	return 0;
}
