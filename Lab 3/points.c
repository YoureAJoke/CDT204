#include <iostream>
#include <time.h>

typedef float pnt[3];

void count(pnt const* pnts, const int n, unsigned cnt[8]) {
    for (int i = 0; i < 8; ++i)
        cnt[i] = 0;
    for (int i = 0; i < n; ++i) {
        if (pnts[i][0] >= 0.0f && pnts[i][1] >= 0.0f && pnts[i][2] >= 0.0f) ++cnt[7]; else
            if (pnts[i][0] >= 0.0f && pnts[i][1] >= 0.0f && pnts[i][2] < 0.0f) ++cnt[3]; else
                if (pnts[i][0] >= 0.0f && pnts[i][1] < 0.0f && pnts[i][2] >= 0.0f) ++cnt[5]; else
                    if (pnts[i][0] >= 0.0f && pnts[i][1] < 0.0f && pnts[i][2] < 0.0f) ++cnt[1]; else
                        if (pnts[i][0] < 0.0f && pnts[i][1] >= 0.0f && pnts[i][2] >= 0.0f) ++cnt[6]; else
                            if (pnts[i][0] < 0.0f && pnts[i][1] >= 0.0f && pnts[i][2] < 0.0f) ++cnt[2]; else
                                if (pnts[i][0] < 0.0f && pnts[i][1] < 0.0f && pnts[i][2] >= 0.0f) ++cnt[4]; else
                                    ++cnt[0];
    }

    for (int i = 0; i < 8; i++) {
        printf("octant-%d -> %d\n", i, cnt[i]);
    }
}


//LÖSNING
void solution(pnt const* pnts, const int n, unsigned cnt[8]) {
    for (int i = 0; i < 8; ++i)
        cnt[i] = 0;

    for (int i = 0; i < n; i++) {
        int x = (((int)pnts[i][0]) >> 31) & 1;
        int y = (((int)pnts[i][1]) >> 30) & 2;
        int z = (((int)pnts[i][2]) >> 29) & 4;

        x = x ^ 1 << (1 - 1);
        y = y ^ 1 << (2 - 1);
        z = z ^ 1 << (3 - 1);

        int index = x + y + z;

        ++cnt[index];
    }
}



//RANDOM GENERATE
double rand_double()
{
    return ((double)rand() / (double)RAND_MAX);
}

float rand_double_interval(double a, double b) {
    return (float)rand_double() * (b - a) + a;
}


//GENERATE ARRAY
void generate_array(pnt* pnts, int n) {
    for (int i = 0; i < n; i++) {
        pnts[i][0] = rand_double_interval(-1.0, 1.0);
        pnts[i][1] = rand_double_interval(-1.0, 1.0);
        pnts[i][2] = rand_double_interval(-1.0, 1.0);
    }
}

int main()
{
    srand(time(0));

    //TEST POINT
    pnt point1 = { -1.0, -1.0, -1.0 };


    //TEST
    pnt testp[3];

    //RESULT FOR SKELOTON FUNCTION
    unsigned result_array[8];

    //TEST SOLUTION
    solution(&point1, 1, result_array);
    

    //PRINT RESULT
    for (int i = 0; i < 8; i++) {
        printf("octant-%d -> %d\n", i, result_array[i]);
    }

    /*
    //RESULT FOR SOLUTION
    int result[8] = {0,0,0,0,0,0,0,0};

    //RUN SKELTION
    count(&test, 1, test1);

    //NEWLINES
    printf("\n\n");

    //MOVE MSB TO INDEX 1, 2, 3
    int x = (((int)test[0]) >> 31) & 1;
    int y = (((int)test[1]) >> 30) & 2;
    int z = (((int)test[2]) >> 29) & 4;

    //FLIP BITS
    x = x ^ 1 << (1 - 1);
    y = y ^ 1 << (2 - 1);
    z = z ^ 1 << (3 - 1);

    //PRINT VALUES
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("z = %d\n", z);

    //CALCULATE SUM TO USE AS INDEX
    int sum = x + y + z;

    //ADD 1 TO CORECT OCTANT
    ++result[sum];

    //PRINT POINTS IN OCTANTS
    for (int i = 0; i < 8; i++) {
        printf("octant-%d -> %d\n", i, result[i]);
    }
    */
}

/*
1. Octant I: x,y,z are all positive.
2. Octant II: x is negative; y and z are positive.
3. Octant III: x and y are negative, z is positive.
4. Octant IV: x and z are positive, y is negative.
5. Octant V: x and y are positive, z is negative.
6. Octant VI: y is positive, x and z are negative.
7. Octant VII: x,y,z, are all negative.
8. Octant VIII: x is positive, y and z are negative.
*/
