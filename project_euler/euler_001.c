/** 
 * Multiples of 3 or 5
 * Problem 1
 * 
 * If we list all the natural numbers below 10 that are multiples of 3
 * or 5, we get 3, 5, 6, and 9. The sum of these multiples is 23. 
 * 
 * Find the sum of all multiples of 3 or 5 below 1000.
 * 
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>


int calc_set_sum(int max_val, int mult) {
    // In general, the nth term of any sequence with starting value a
    // and common distance d can be written as:
    // a + (n - 1)d
    // Therefore, the sum to n terms of a sequence is:
    // 1/2n(2a + (n - 1)d()
    // 0.5n * ((2 * a) + ((n - 1) * d))
    // (n * a) + (0.5n * ((n - 1) * d))
    // na + ((n^2 - n) * d) / 2
    // (n * a) + ((((pow(n, 2) - n) * d) / 2)
    int n = (max_val - (max_val % mult)) / mult;
    int l = n * mult;
    int r = ((pow(n, 2) - n) * mult) / 2;
    return (l + r);
}


int get_sum(int max_val, int* mults, int mults_sz) {
    int* overlaps = malloc((mults_sz * (mults_sz - 1)) * sizeof(int));
    int c_o = 0;
    int sum = 0;
    // Find the overlaps between our multiples.
    if (mults_sz > 1) {
        for (int i = 0; i < (mults_sz - 1); ++i) {
            for (int j = 1; j < mults_sz; ++j) {
                overlaps[c_o] = mults[i] * mults[j];
                c_o++;
            }
        }
    }
    // Iterate through every multiple and add the calculation of
    // the progression to the sum.
    for (int i = 0; i < mults_sz; ++i) {
        int s = calc_set_sum(max_val, mults[i]);
        printf("Sum for %i: %i\n", mults[i], s);
        sum += s;
    }
    // Iterate through the overlaps and subtract the calculation
    // of the progression to the sum.
    for (int i = 0; i < c_o; ++i) {
        sum -= calc_set_sum(max_val, overlaps[i]);
    }
    free(overlaps);
    return sum;
}

int main() {
    int multiples[2];
    multiples[0] = 3;
    multiples[1] = 5;
    int solution = get_sum(999, multiples, 2);
    printf("Project Euler\nProblem #1\n\nAnswer: %i\n", solution);
    return 0;
}