/** 
 * Find all sets of five five-letter words that provide unique
 * letters of the alphabet with no overlap.
 */

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef __APPLE__
#include <malloc/malloc.h>
#endif

#ifdef __linux__
#include <malloc.h>
#endif


#define SEEN_SIZE 12356631


// Comparator function to use with qsort.
int strcomp(const void* a, const void* b) {
    return ( *(char*)a - *(char*)b );
}

/**
 * Returns how many words are in the provided word list. This
 * function assumes that every word in the list will be five
 * letters.
 * 
 * Essentially, counts all non-null characters in a string and
 * divides by 5.
 *  
 */
int get_len_words(char* word_list) {
    int c_sz = 0;
    for (int i = 0; i < malloc_usable_size(word_list); ++i) {
        if (word_list[i] != '\0') {
            c_sz++;
        }
    }
    return (c_sz / 5);
}


/**
 * Loads words from the provided filename, leaving only 5-letter
 * words with no repetitions and removing any anagrams of already
 * loaded words.
 * 
 */
char* load_words(const char* filename) {
    // Allocate memory to hold our wordlist. We use an arbitrary large
    // value here to ensure there will be enough memory for the list. 
    char* word_list = malloc((6 * 100000) * sizeof(char*));
    memset(word_list, '\0', sizeof(word_list));
    // Initialise a variable to hold the count of how many words have
    // been found in the file.
    int w_c = 0;
    // Initialise where we'll store the file pointer.
    FILE *file_ptr;
    // Initialise where we'll store our log of which hashes we have
    // already seen.
    bool* seen = (bool*)malloc(SEEN_SIZE * sizeof(bool));
    memset(seen, false, sizeof(bool));
    // Open the file containing the word list that we want to load
    // and process.
    file_ptr = fopen(filename, "r");
    if (file_ptr == NULL) {
        printf("Runtime Error: Unable to open file '%s'. Exitting ...\n ", filename);
        exit(1);
    }
    // Get the first letter found in the target file.
    char t_ch = fgetc(file_ptr);
    // Allocate memory to hold the currently built word.
    char* t_w = malloc(5 * sizeof(char*));
    memset(t_w, '\0', sizeof(t_w));
    // Initialise a variable to hold the length of the current word.
    int w_sz = 0;
    // Loop through the file for every character and process
    // accordingly.
    while (t_ch != EOF) {
        // Check that the current character is not a whitespace
        // character.
        if (t_ch != ' ' && t_ch != '\n' && t_ch != '\r') {
            // If we haven't reached a letter count of 5 yet, we can
            // store the current character in our string.
            if (w_sz < 5) {
                t_w[w_sz] = t_ch;
            }
            // Regardless of the letter count, we'll go ahead and
            // increment the variable for it.
            w_sz++;
        // If we've reached a whitespace character, we can begin
        // evaluating if the current word is one worth processing
        // further.
        // First, we need to know that this word is exactly five
        // letters.
        } else if (w_sz == 5) {
            // We can go ahead and reset the word size.
            w_sz = 0;
            // Now that we know this word is five letters long, we
            // can look for if it has any duplicated letters.
            // We'll start by initialising a boolean value that tells
            // whether the word has duplicates or not.
            bool has_duplicates = false;
            // Next, we will store a temporary copy of the current word.
            char* s_w = malloc(6 * sizeof(char*));
            memset(s_w, '\0', sizeof(s_w));
            strcpy(s_w, t_w);
            // We now need to sort the letters in the temporary word
            // so that we can easily tell if there are any duplicates.
            // This will also allow us to calculate a uniform hash for
            // any anagrams later.
            qsort(s_w, 5, sizeof(char), strcomp);
            // Now that we have the letters sorted, we'll iterate
            // through to locate any duplicate letters.
            for (int i = 0; i < 4; ++i) {
                if (s_w[i] == s_w[i + 1] && s_w[i] != '\0') {
                    has_duplicates = true;
                    break;
                }
            }
            // We will only calculate the hash for this word if there
            // are no duplicate letters found.
            if (!has_duplicates) {
                int w_h = 0;
                // The hash is calculated by taking each character in
                // the word, subtracting the ordinal value of 'a' from
                // it, and adding it to the previous hash * 26.
                for (int i = 0; i < sizeof(s_w); ++i) {
                    if (s_w[i] != '\0') {
                        w_h = (w_h * 26) + (s_w[i] - 'a');
                    }
                }
                // We will only add this word to our final list if we
                // have yet to see this hash.
                if (!seen[w_h]) {
                    seen[w_h] = true;
                    for (int c = 0; c < 5; ++c) {
                        word_list[(w_c * 5) + c] = t_w[c];
                    }
                    w_c++;
                }
            }
            free(has_duplicates);
            free(s_w);
        // Finally, if this is a whitespace character, and our word is
        // not of an appropriate length, we'll just reset the word
        // length to 0.
        } else {
            w_sz = 0;
        }
        // And, finally, we can go ahead and get the next character.
        t_ch = fgetc(file_ptr);
    }
    // Allocate only the amount of memory needed to hold the words in
    // our list and return the list accordingly.
    char* w_l = malloc(w_c * 5 * sizeof(char));
    memset(w_l, '\0', sizeof(char));
    strcpy(w_l, word_list);
    free(word_list);
    free(seen);
    return w_l;
}


// Returns the position-th word from the word list.
char* get_word(char* word_list, int position) {
    char* w = malloc(6 * sizeof(char));
    memset(w, '\0', sizeof(char));
    for (int i = 0; i < 5; ++i) {
        w[i] = word_list[(position * 5) + i];
    }
    return w;
}


/** Outputs all sets as they are found to the console. */
void output_all_sets(
    int* solution_sz, bool** can_construct,
    char* word_list, int word_list_sz,
    int* masks, int mask_sz,
    int* result, int result_sz,
    int mask, int start
) {
    // Check to see if we already have a five word result.
    if (result_sz == 5) {
        // Since we already have the target result length, we can just
        // print the words to the console.
        for (int i = 0; i < 5; ++i) {
            printf(get_word(word_list, result[i]));
            printf(" ");
        }
        printf("\n");
        *solution_sz += 1;
        return;
    } 
    // Otherwise, we will iterate through to find the relevant sets
    // for the provided mask.
    for (int t_w = start; t_w < word_list_sz; ++t_w) {
        if (((mask & masks[t_w]) == masks[t_w])
        && (result_sz == 4 || can_construct[3 - result_sz][mask ^ masks[t_w]])) {
            result[result_sz] = t_w;
            output_all_sets(solution_sz, can_construct, word_list, word_list_sz, masks, mask_sz, result, result_sz + 1, mask ^ masks[t_w], t_w + 1);
            result[result_sz] = 0;
        }
    }
}


/** Sets up needed information and solves the problem. */
void solve(int* solution_sz_ptr, char* word_list, int word_list_sz) {
    // Initialises the can_construct matrix, allocating memory for
    // every possible mask we could deal with.
    // Since a mask of a word is a 26-bit integer with corresponding
    // bits flipped for the letters of the word, the maximum mask we
    // can have is (1 << 26).
    bool** can_construct = (bool**)malloc(5 * sizeof(bool*));
    for (int i = 0; i < 5; ++i) {
        can_construct[i] = (bool*)malloc(1 << 26 * sizeof(bool));
        memset(can_construct[i], false, (1 << 26 * sizeof(bool)));
    }
    // Initialise an array of integers to hold a calculated mask for
    // each word in the word list.
    int* masks = malloc(word_list_sz * sizeof(int));
    // Calculate the masks and setup can_construct[0].
    for (int i = 0; i < word_list_sz; ++i) {
        char* t_w = get_word(word_list, i);
        int mask = 0;
        for (int c = 0; c < 5; ++c) {
            mask |= 1 << (t_w[c] - 'a');
        }
        masks[i] = mask;
        can_construct[0][mask] = true;
    }
    // Build the information for each of the remaining can_construct
    // subarrays.
    for (int c = 0; c < 4; ++c) {
        // Iterate through every potential mask and check if it is
        // buildable at the current position.
        for (int m = 0; m < (1 << 26); ++ m) {
            if (can_construct[c][m]) {
                // If a set could be constructed with the current mask,
                // iterate through every word in the list and check if
                // the two masks overlap or not. If not, it's viable
                // and can be marked true in the next set.
                for (int i = 0; i < word_list_sz; ++i) {
                    if ((masks[i] & m) == 0) {
                        can_construct[c + 1][masks[i] | m] = true;
                    }
                }
            }
        }
    }
    // Setup an array to hold the resulting word positions.
    int result[5];
    memset(result, 0, 5 * sizeof(int));
    // Iterate through all of the masks and check if they are marked
    // as constructable in the 4th set.
    for (int m = 0; m < (1 << 26); ++m) {
        if (can_construct[4][m]) {
            output_all_sets(solution_sz_ptr, can_construct, word_list, word_list_sz, masks, word_list_sz, result, 0, m, 0);
        }
    }
    printf("Found %i solutions. \n", *solution_sz_ptr);
}


int main() {
    // Initialise variables to let us time the functions.
    clock_t start, end;
    double cpu_time;
    // Start the clock for load_words
    start = clock();
    // Load the words from our file.
    char* words = load_words("words_alpha.txt");
    // Stop the clock for load_words and calculate the runtime.
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Loaded %i words in %fs. \n", get_len_words(words), cpu_time);
    // Initialise a variable to hold how many solutions we found to
    // the problem.
    int s_sz = 0;
    // Start the clock for solve.
    start = clock();
    // Solve the problem and print all solutions to the console.
    solve(&s_sz, words, get_len_words(words));
    // Stop the clock for solve and calculate the runtime.
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Finished in %fs. \n", cpu_time);
    return 0;
}