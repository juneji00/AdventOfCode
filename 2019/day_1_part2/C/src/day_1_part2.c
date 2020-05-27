/*
 ============================================================================
 Name        : day_1_part2.c
 Author      : PS
 Version     :
 Copyright   : N/A
 Description : Day 1: The Tyranny of the Rocket Equation.

 Calculate the total fuel requirement to launch a rocket.

 Fuel(x) = round( x / 3 ) - 2 , where x = module mass

 NOTE: part 2 accounts for the mass of fuel

 Answer = sum of Fuel(x) for all inputs
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define 	IN_FILENAME		"module_mass.txt"
#define		OUT_FILENAME	"solution.txt"
#define		ARRAY_SIZE		100

int main(void) {

	/*
	 * open i/o files
	 */

	FILE *input_fp, *output_fp;

	input_fp = fopen(IN_FILENAME, "r");
	output_fp = fopen(OUT_FILENAME, "w");

	// error check
	if (input_fp == NULL) {
		printf("Error reading input file\n");
		exit(EXIT_FAILURE);
	}

	if (output_fp == NULL) {
		printf("Error opening output file\n");
		exit(EXIT_FAILURE);
	}

	/*
	 * perform calculation and print results
	 */

	uint32_t fuel[ARRAY_SIZE];
	int32_t mass = 0;
	int32_t initialMass;
	uint32_t TotalFuel = 0;
	uint32_t i = 0;

	printf("Fuel Calculation Table\n"
			"*********************************************************\n"
			"ITEM\t\tMASS\t\tFUEL\t\tSUBTOTAL\n"
			"*********************************************************\n");

	fprintf(output_fp, "Fuel Calculation Table\n"
			"*********************************************************\n"
			"ITEM\t\tMASS\t\tFUEL\t\tSUBTOTAL\n"
			"*********************************************************\n");
	while (fscanf(input_fp, "%d", &mass) != EOF) {
		initialMass = mass;

		int32_t j = 0;
		while ((mass = (mass / 3) - 2) > 0) {
			// add additional element to fuel array
			fuel[j] = mass;
			j++;
		}

		int32_t array_size = j;
		for (j = 0; j < array_size; ++j) {
			// add up all elements of TotalFuel array
			TotalFuel += fuel[j];
		}

		i += 1;
		printf("%d\t\t%d\t\t%d\t\t%d\n", i, initialMass, fuel[0], TotalFuel);
		fprintf(output_fp, "%d\t\t\t%d\t\t%d\t\t%d\n", i, initialMass, fuel[0],
				TotalFuel);
	}

	printf("\nTotal fuel is %d\n", TotalFuel);
	fprintf(output_fp, "\nTotal fuel is %d\n", TotalFuel);

	while (fscanf(input_fp, "%d", &mass) != EOF) {

		for (i = 0; i < 100; ++i) {
			printf("%d\t", mass);
		}

	}

	fclose(input_fp);  // close files
	fclose(output_fp);

	return EXIT_SUCCESS;
}
