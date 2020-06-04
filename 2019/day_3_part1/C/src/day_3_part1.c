/*
 ============================================================================
 Name        : day_3_part1.c
 Author      : PS
 Version     :
 Copyright   : N/A
 Description : To fix the circuit, you need to find the intersection point
 	 	 	   closest to the central port. Because the wires are on a grid,
 	 	 	   use the Manhattan distance for this measurement. While the wires
 	 	 	   do technically cross right at the central port where they both
 	 	 	   start, this point does not count, nor does a wire count as
 	 	 	   crossing with itself.

			   For example, if the first wire's path is R8,U5,L5,D3, then starting
			   from the central port (o), it goes right 8, up 5, left 5, and finally
			   down 3.  Then, if the second wire's path is U7,R6,D4,L4, it goes up 7,
			   right 6, down 4, and left 4. These wires cross at two locations
			   (marked X), but the lower-left one is closer to the central port:
			   its distance is 3 + 3 = 6.

			   Here are a few more examples:
		       R75,D30,R83,U83,L12,D49,R71,U7,L72
			   U62,R66,U55,R34,D71,R55,D58,R83 = distance 159
			   R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51
			   U98,R91,D20,R16,D67,R40,U7,R15,U6,R7 = distance 135
			   What is the Manhattan distance from the central port to the
			   closest intersection?
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define 	IN_FILE		"front_panel.txt"
//#define 	IN_FILE		"test1.txt"
#define		OUT_FILE	"solution.txt"
#define 	SIZE		100

enum color{Red = 0x2B, Black = 0x23};
#define	CROSS		0x4E

enum direction{Up, Down, Left, Right};

const int ROWS = 10000;
const int COLS = 10000;
const int Xorigin = COLS/2;
const int Yorigin = ROWS/2;

#define MoveLeft(MAG,COLOR)		for (int i = 0; i < MAG; i++ ) grid[Y + 0][X-- - 1] += COLOR
#define MoveRight(MAG,COLOR)	for (int i = 0; i < MAG; i++ ) grid[Y + 0][X++ + 1] += COLOR
#define MoveUp(MAG,COLOR)		for (int i = 0; i < MAG; i++ ) grid[Y-- - 1][X + 0] += COLOR
#define MoveDown(MAG,COLOR)		for (int i = 0; i < MAG; i++ ) grid[Y++ + 1][X + 0] += COLOR

void printGrid(int array[ROWS][COLS]);
void WireRoute(char *str, int color, int grid[ROWS][COLS]);

struct Wires {
	char path[SIZE];
	int color;
};

int main(void) {

	/*
	 * open i/o files
	 */

	FILE *input_fp, *output_fp;
	input_fp = fopen(IN_FILE, "r");
	output_fp = fopen(OUT_FILE, "w");

	// error check
	if (input_fp == NULL || output_fp == NULL)	{
		perror("ERROR during I/O file access ");
		exit (EXIT_FAILURE);
	}

   /*  Potential paths to solution
	*  1. get array1 and array2 from input file
	*  2. assign coordinates to each array vector
	*  3. compare each set of coordinates between arrays  (use strstr()?)
	*        if there's a match, store the coordinate
	*  4. calculate distance from each matching coordinate
	*  5. answer is shortest distance
	*/

	// initialize grid
	const int glen = 10000;
	int grid[10000][10000] = {{0x2E}};
	grid[Yorigin][Xorigin] = 0x30;

	//printGrid(grid);

	printf("\n");


	// 1. get wire1 and wire2 path from input file


	struct Wires wire1;		// declare wire1 of type Wires
	struct Wires wire2;

	fscanf(input_fp, "%s\n%s", wire1.path, wire2.path);

	//  2. assign coordinates to each wire array vector

	wire1.color = Red;
	wire2.color = Black;

	WireRoute(wire1.path, wire1.color, grid);
	puts("\n");
	WireRoute(wire2.path, wire2.color, grid);
	puts("\n");
//	printGrid(grid);
	puts("\n");

	// 	3. compare each set of coordinates between arrays  (use strstr()?)
	//        if there's a match, store the coordinate

	int matches[100] = {0};
	int k = 0;
	matches[k++] = Xorigin;
	matches[k++] = Yorigin;

	for (int i = 0; i < glen; i++){
		for (int j = 0; j < glen; j++){
			if (grid[i][j] == CROSS){
				matches[k++] += i;
				matches[k++] += j;
			}
		}
	}

	//  4. calculate distance from each matching coordinate
	int distance[100] = {0};
	int j = 0;
	for (int i = 2; i < 100; i += 2){
		 distance[j++] = abs( matches[i] - Xorigin ) + abs( matches[i+1] - Yorigin);
	}

	//  5. answer is shortest distance
	int i = 0;
	int answer = distance[0];
    for (i = 1; i < 100; i++)
    {
        if (distance[i] < answer && distance[i] != 0)
        {
        	answer = distance[i];
        }
    }

	//int NumCross = 2;

	//printf("The wires cross at %d points\n", NumCross);
	printf("Shortest distance is %d", answer);

	fclose(input_fp);  // close files
	fclose(output_fp);

	return EXIT_SUCCESS;
}

void WireRoute(char *str, int color, int grid[ROWS][COLS]){
	//char c;
	char *pstr = str;
	int direction;
	long magnitude = 0;
	int X = Xorigin;
	int Y = Yorigin;

	for(int i = 0; *pstr != '\0'; i++ ){
		if(isalpha(*pstr)){		// found a letter
			switch (*pstr){
			case 'U':
				direction = Up;
				break;
			case 'D':
				direction = Down;
				break;
			case 'L':
				direction = Left;
				break;
			case 'R':
				direction = Right;
				break;
			default:
				printf("Error");
				break;
			}
		}
		if (isdigit(*pstr)){		// found a number
			magnitude = strtol(pstr, &pstr, 10);
			switch (direction){
			case Up:
				MoveUp(magnitude,color);
				break;
			case Down:
				MoveDown(magnitude,color);
				break;
			case Left:
				MoveLeft(magnitude,color);
				break;
			case Right:
				MoveRight(magnitude,color);
				break;

			}
			printf("move (%d) %ld times\n", direction, magnitude);
		}else{
			// move on to the next character if not a number
			pstr++;
		}
	}
}

void printGrid(int array[ROWS][COLS]){

	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++)
			printf("%c", (char)(array[i][j]));
		printf("\n");
	}

}
