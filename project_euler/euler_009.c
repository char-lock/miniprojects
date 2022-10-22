/**
 * Special Pythagorean Triplet
 * Problem 9
 * 
 * A Pythagorean triplet is a set of three natural numbers, a < b < c,
 * for which:
 * 
 * a^2 + b^2 = c^2
 * 
 * For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2
 * 
 * There exists one Pythagorean triplet for which a + b + c = 1000.
 * Find the product abc.
 * 
 */

#include <stdio.h>
#include <stdlib.h>


int find_triplet(int sum_v) {
    for (int a = 2; a < sum_v - 4; ++a) {
        for (int b = 2; b < (sum_v - 4 - a); ++b) {
            int c = sum_v - a - b;
            if (((a * a) + (b * b)) == (c * c)) {
                return (a * b * c);
            }
        } 
    }
    return 0;
}


int main() {
    printf("Project Euler\nProblem #9\n\nAnswer: %i\n", find_triplet(1000));
    return 0;
}