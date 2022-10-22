/**
 * Sum Square Difference
 * Problem 6
 * 
 * The sum of the squares of the first ten natural numbers is:
 * 
 * 1^2 + 2^2 + ... + 10^2 = 385
 * 
 * The square of the sum of the first ten natural numbers is:
 * 
 * (1 + 2 + ... + 10)^2 = 55^2 = 3025
 * 
 * Hence the difference between the sum of the squares of the first
 * ten natural numbers and the square of the sum is:
 * 
 * 3025 - 385 = 2640
 * 
 * Find the difference between the sum of the squares of the first one
 * hundred natural numbers and the square of the sum.
 * 
 */

#include <stdio.h>
#include <stdlib.h>


long sum_of_squares(int max_v) {
    long s = 0;
    for (int i = 1; i < (max_v + 1); ++i) {
        s += i * i;
    }
    return s;
}


long square_of_sum(int max_v) {
    long s = 0;
    for (int i = 1; i < (max_v + 1); ++i) {
        s += i;
    }
    s = s * s;
    return s;
}


int main() {
    long sum_s = sum_of_squares(100);
    long sq_s = square_of_sum(100);
    printf("Project Euler\nProblem 6\n\nAnswer: %ld \n", sq_s - sum_s);
    return 0;
}