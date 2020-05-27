/*
 ============================================================================
 Name        : day_2_part1.c
 Author      : PS
 Version     :
 Copyright   : N/A
 Description : Day 2: 1202 Program Alarm

 	 	 	   Create a working Intcode program.  Once you have a working
 	 	 	   computer, the first step is to restore the gravity assist
 	 	 	   program (your puzzle input) to the "1202 program alarm" state
 	 	 	   it had just before the last computer caught fire. To do this,
 	 	 	   before running the program, replace position 1 with the value 12
 	 	 	   and replace position 2 with the value 2.

 	 	 	   What value is left at position 0 after the program halts?

 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define 	IN_FILENAME		"gravity_assist_program.txt"
//#define 	IN_FILENAME		"test.txt"
#define		OUT_FILENAME	"solution.txt"
#define		UNKNOWN_SIZE	1000
#define		STEP			4		// step 4 positions after OPCODE
#define		INPUT1			1		// input1 value position
#define		INPUT2			2		// input2 value position
#define		OUTPUT			3		// output value position
#define		ADD				1		// opcode 1
#define		MUL				2		// opcode 2
#define		HALT			99		// opcode 99

void header(char *c);

int main(void) {

	/*
	 * open i/o files
	 */

	FILE *input_fp, *output_fp;
	input_fp = fopen(IN_FILENAME, "r");
	output_fp = fopen(OUT_FILENAME, "w");

	// error check
	if (input_fp == NULL || output_fp == NULL) {
		printf("Error opening i/o files\n");
		exit(EXIT_FAILURE);
	}

	/*
	 * initialize program array and opcodes
	 */

	volatile uint32_t program[UNKNOWN_SIZE];
	volatile uint32_t opcode = 0;

	/*
	 * load opcodes into program array
	 */

	volatile uint16_t i;
	for (i = 0; (fscanf(input_fp, "%d,", &opcode) != EOF); i++) {
		program[i] = opcode;
	}
	int len = i;

	puts("Original Program\n");
	fprintf(output_fp, "Original Program\n");

	for (volatile uint16_t  i = 0; i < len; i++) {
		printf("%d ", program[i]);
		fprintf(output_fp, "%d ", program[i]);
	}

	header("PASS1");

	program[1] = 12;
	program[2] = 2;

	for (volatile uint16_t i = 0; i < len; i++) {
		printf("%d ", program[i]);
		fprintf(fopen(OUT_FILENAME, "a"), "%d ", program[i]);
	}

	header("PASS2");

	volatile uint32_t addr1;
	volatile uint32_t addr2;
	volatile uint32_t addr3;

	for (volatile uint16_t i = 0; i < len; i += STEP)	{
		switch (program[i]) {
		case ADD:
			addr1 = program[i + INPUT1];
			addr2 = program[i + INPUT2];
			addr3 = program[i + OUTPUT];
			program[addr3] = program[addr1] + program[addr2];
			break;

		case MUL:
			addr1 = program[i + INPUT1];
			addr2 = program[i + INPUT2];
			addr3 = program[i + OUTPUT];
			program[addr3] = program[addr1] * program[addr2];
			break;

		case HALT:
			for (volatile uint16_t i = 0; i < len; i++) {
				printf("%d ", program[i]);
				fprintf(fopen(OUT_FILENAME, "a"), "%d ", program[i]);
			}

			printf("\n\nValue at position 0 is %d", program[0]);
			fprintf(fopen(OUT_FILENAME, "a"), "\n\nValue at position 0 is %d", program[0]);


			fclose(input_fp);  // close files
			fclose(output_fp);
			exit(EXIT_SUCCESS);
			break;

		default:
			printf("%d", program[i]);
			fprintf(fopen(OUT_FILENAME, "a"), "%d ", program[i]);
		}
	}

	return EXIT_SUCCESS;
}

void header(char *c)
{
	puts("\n\n*********************************************\n");
	fprintf(fopen(OUT_FILENAME, "a"), "\n\n*********************************************\n");
	printf("Program %s\n", c);
	fprintf(fopen(OUT_FILENAME, "a"), "Program %s\n", c);
}



