#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>




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
}

void ourSolution(pnt const* pnts, const int n, unsigned cnt[8]) {
    for (int i = 0; i < 8; ++i)
        cnt[i] = 0;

    for (int i = 0; i < n; i++) {
        
        int x = ((*(int*)&pnts[i][0]) >> 31) & 1;
        int y = ((*(int*)&pnts[i][1]) >> 30) & 2;
        int z = ((*(int*)&pnts[i][2]) >> 29) & 4;

        x = x ^ 1 << (1 - 1);
        y = y ^ 1 << (2 - 1);
        z = z ^ 1 << (3 - 1);

        int index = x + y + z;

        ++cnt[index];
    }
}

float randomFloat(float a, float b) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void generatePntsArray(pnt* pnts, int n) {
    for (int i = 0; i < n; i++) {
        pnts[i][0] = randomFloat(-1.0, 1.0);
        pnts[i][1] = randomFloat(-1.0, 1.0);
        pnts[i][2] = randomFloat(-1.0, 1.0);
    }
}

int compareResults(unsigned array1[8], unsigned array2[8]) {
    for (int i = 0; i < 8; i++) {
        if (array1[i] != array2[i])
            return 1;
    }
    return 0;
}

int main()
{
    srand(time(0));

    clock_t begin = 0, end = 0;

    double TimeSpent1 = 0.0;
    double TimeSpent2 = 0.0;

    unsigned PointsInEachOctant1[8];
    unsigned PointsInEachOctant2[8];

    pnt* points = (pnt*)malloc(sizeof(pnt) * 10000000);
    generatePntsArray(points, 10000000);

    
    begin = clock();
    count(points, 10000000, PointsInEachOctant1);
    end = clock();

    TimeSpent1 += (double)(end - begin) / CLOCKS_PER_SEC;
    

    begin = clock();
    ourSolution(points, 10000000, PointsInEachOctant2);
    end = clock();

    TimeSpent2 += (double)(end - begin) / CLOCKS_PER_SEC;


    if (compareResults(PointsInEachOctant1, PointsInEachOctant2)) {
        printf("Somthing went wrong results array are not the same.");
        return 0;
    }
    else
    {
        printf("Resultas array are the same!\n");
    }


    printf("Lab Function: %f seconds\nOur Function: %f seconds\n", TimeSpent1, TimeSpent2);
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
