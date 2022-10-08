#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 1000

// Compare the matrices mat1 and mat2, and return 1 if they are equal,
// 0 otherwise
int compare_matrices(int mat1[N][N], int mat2[N][N])
{
	int i, j;
	for (i = 0; i < N; ++i) for (j = 0; j < N; ++j)
	if (mat1[i][j] != mat2[i][j])
		return 0;
	return 1;
}

// The first version of the algorithm. Computes result = mat1 * mat2.
void version1(int mat1[N][N], int mat2[N][N], int result[N][N])
{
	int i, j, k;
	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
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
				result[j][i] += mat1[k][i] * mat2[j][k];
		}
	}
}

void version3(int mat1[N][N], int mat2[N][N], int result[N][N])
{
	int i, j, k;

	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			for (k = 0; k < N; ++k)
				result[i][k] += mat1[i][j] * mat2[j][k];
		}
	}

	/*
	* Example printing out indexes
	for(int i = 0; i < 2; ++i){
        
        for(int j = 0; j <2; ++j){
            printf("i:%d, j:%d\n", i, j);
            
            for(int k = 0; k < 2; ++k){
                printf("    x:%d, y:%d\n", j, k);
                printf("    result x:%d, y:%d\n", i, k);
            }
        }
    }
	*/
}

void version4(int mat1[N][N], int mat2[N][N], int result[N][N])
{
	//Fill your code here 
}

void version5(int mat1[N][N], int mat2[N][N], int result[N][N])
{
	//Fill your code here 
}
// The matrices. mat_ref is used for reference. If the multiplication is done correctly,
// mat_r should equal mat_ref.
int mat_a[N][N], mat_b[N][N], mat_r[N][N], mat_ref[N][N];

// Call this before performing the operation (and do *not* include the time to
// return from this function in your measurements). It fills mat_a and mat_b with
// random integer values in the range [0..9].
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

	// Initialize the matrices
	init_matrices();
	

	// Check that mat_r is correct. For this the reference matrix mat_ref is computed
	// using the basic() implementation,
	printf("Making reference matrix for error checking.\n");
	version1(mat_a, mat_b, mat_ref);

	printf("Started your matrix multiplication.\n");

	// Take the time
	t0 = clock();

	// Run the algorithm (uncomment the right version to compile it)
	//version1(mat_a, mat_b, mat_r);
	//version2(mat_a, mat_b, mat_r);
	//version3(mat_a, mat_b, mat_r); 
	//version4(mat_a, mat_b, mat_r); 
	//version5(mat_a, mat_b, mat_r); 

	// Take the time again
	t1 = clock();

	printf("Finished in %lf seconds.\n", (double)(t1 - t0) / CLOCKS_PER_SEC);
	//  and then mat_r is compared to mat_ref.
	if (!compare_matrices(mat_r, mat_ref))
		printf("Error: mat_r does not match the reference matrix!\n");
	else
		printf("Correct!\n");

	// If using Visual Studio, do not close the console window immediately
#ifdef _MSC_VER
	system("pause");
#endif

	return 0;
}
