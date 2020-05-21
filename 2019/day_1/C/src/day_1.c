/*
 ============================================================================
 Name        : day_1.c
 Author      : PS
 Version     :
 Copyright   : N/A
 Description : Day 1: The Tyranny of the Rocket Equation.

 	 	 	   Calculate the total fuel requirement to launch a rocket.

 	 	 	   Fuel(x) = round( x / 3 ) - 2 , where x = module mass

 	 	 	   Answer = sum of Fuel(x) for all inputs
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define 	IN_FILENAME		"module_mass.txt"
#define		OUT_FILENAME	"solution.txt"

int main(void) {

	/*
	 * open input file
	 */

	FILE *input_fp, *output_fp;

	input_fp = fopen(IN_FILENAME, "r");

	// error check
	if (input_fp == NULL)
	{
		printf("Error reading input file\n");
		exit (EXIT_FAILURE);
	}

	output_fp = fopen(OUT_FILENAME, "w");

	// error check
	if (output_fp == NULL)
	{
		printf("Error opening output file\n");
		exit (EXIT_FAILURE);
	}

	/*
	 * perform calculation and print results
	 */

	uint32_t fuel = 0, mass = 0, TotalFuel = 0, i = 0;

	printf("Fuel Calculation Table\n"
			"*********************************************************\n"
			"ITEM\t\tMASS\t\tFUEL\t\tSUBTOTAL\n"
			"*********************************************************\n");

	fprintf(output_fp, "Fuel Calculation Table\n"
			"*********************************************************\n"
			"ITEM\t\tMASS\t\tFUEL\t\tSUBTOTAL\n"
			"*********************************************************\n");

	while (fscanf(input_fp, "%d", &mass) != EOF)
	{
		fuel = (mass / 3 ) - 2;
		TotalFuel += fuel;
		i += 1;
		printf("%d\t\t%d\t\t%d\t\t%d\n", i, mass, fuel, TotalFuel);
		fprintf(output_fp, "%d\t\t%d\t\t%d\t\t%d\n", i, mass, fuel, TotalFuel);
	}

	printf("\nTotal fuel is %d\n", TotalFuel);
	fprintf(output_fp, "\nTotal fuel is %d\n", TotalFuel);

	fclose(input_fp);  // close files
	fclose(output_fp);

	return EXIT_SUCCESS;
}
