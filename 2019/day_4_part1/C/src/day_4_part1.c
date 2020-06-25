/*
 ============================================================================
 Name        : day_4_part1.c
 Author      : PS
 Date        : 6-25-20

How many different passwords within the range given in your puzzle input meet these criteria?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 300000

struct solution_s{
    int possible_numbers[SIZE];
    int len;
};

int increasing_digits(int x){
    char buffer[10];
    snprintf(buffer, 10, "%d", x);

    for (int i = 0; i < 5; i++){
        if (buffer[i] <= buffer[i+1]){
            continue;
        }else{
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int repeating_digits(int x){
    char buffer[10];
    snprintf(buffer, 10, "%d", x);

    for (int i = 0; i < 6; i++)
        if (buffer[i] == buffer[i+1])
            return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

void part1(char *input){

    // format input
    char *p = input;
    long int low, high;
    low = strtol(input, &p, 10);
    high = strtol(p+1, &p, 10);

    struct solution_s possible_solution;

    int j = 0;
    possible_solution.len = 0;
    int c, d;
    for (int i = low; i <= high; i++){
        if (!(c=repeating_digits(i)) && !(d=increasing_digits(i))){
            possible_solution.possible_numbers[j++] = i;
            possible_solution.len += 1;
        }
    }
    printf("\nNumber of possible solutions: %d", possible_solution.len);
}

int main(void) {
	char input[] = "146810-612564";
	part1(input);

	return EXIT_SUCCESS;
}
