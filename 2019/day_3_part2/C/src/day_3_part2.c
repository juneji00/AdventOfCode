/*
 ============================================================================
 Name        : day_3_part2.c
 Author      : PS
 Date        : 6-24-20

 What is the Manhattan distance from the central port to the
 closest intersection?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define     TEST       1

#ifdef      TEST
#define   IN_FILE     "test1.txt"
#else
#define     IN_FILE     "front_panel.txt"
#endif

#define     DEFAULT_SIZE        1500
#define     MIN(x,y)    (((x) < (y)) ? (x) : (y))
#define     MAX(x,y)    (((x) > (y)) ? (x) : (y))

struct Xarray{
    int Y[DEFAULT_SIZE];
    int Xmin[DEFAULT_SIZE];
    int Xmax[DEFAULT_SIZE];
    int Xarray_size;
};

struct Yarray{
    int X[DEFAULT_SIZE];
    int Ymin[DEFAULT_SIZE];
    int Ymax[DEFAULT_SIZE];
    int Yarray_size;
};

struct Point{
    int X[DEFAULT_SIZE];
    int Y[DEFAULT_SIZE];
    int pt_size;
};

struct Wire_s{
    char wire_path[DEFAULT_SIZE];
    struct Yarray Vert;
    struct Xarray Horiz;
    struct Point pts;
    int running_total;
    int single_move[DEFAULT_SIZE];
    int cross_length[DEFAULT_SIZE];
} red_wire, black_wire;

struct Crossing_s{
    int X[DEFAULT_SIZE];
    int Y[DEFAULT_SIZE];
    int Crossing_size;
};

void print_array(int *print_this){
    for(int loop = 0; loop < 10; loop++)
        printf("%4d ", print_this[loop]);
}


int find_crossing(struct Crossing_s *cross, struct Wire_s *wire1, struct Wire_s *wire2){
    int i = 0;
    int j = 0;
    int k = 0;
    int *A_init = &(wire2->Horiz.Y[j]);
    int *B_init = &(wire1->Vert.X[i]);
    int A_len = wire2->Horiz.Xarray_size;
    int B_len = wire1->Vert.Yarray_size;
    int cross_init = cross->Crossing_size;

    for (; (&(wire2->Horiz.Y[j]) - A_init) < A_len; j++, i = 0) {
        while ( &(wire1->Vert.X[i]) - B_init < B_len) {
            if ( (wire2->Horiz.Xmin[j] <= wire1->Vert.X[i]) && (wire1->Vert.X[i] <= wire2->Horiz.Xmax[j]) ) {
                if (( wire1->Vert.Ymin[i] <= wire2->Horiz.Y[j]) && (wire2->Horiz.Y[j] <= wire1->Vert.Ymax[i]) ) {
                    cross->X[k] = wire1->Vert.X[i];    // assign X value to crossing
                    cross->Y[k] = wire2->Horiz.Y[j];   // assign Y value to crossing
                    printf("Xcross: %d, Ycross: %d\n", cross->X[k], cross->Y[k] );
                    printf("\t\tWire1 Xpt: %d, Ypt: %d\n", wire1->pts.X[i-1], wire1->pts.Y[i-1] );
                    printf("\t\t\t\tWire2 Xpt: %d, Ypt: %d\n", wire2->pts.X[j-1], wire2->pts.Y[j-1] );
                    cross->Crossing_size++;
                    k++;
                }
            }
            i++;
        }
    }
    if (cross->Crossing_size == cross_init)     // did the value change? if not, return an error
        return -1;
    return 0;
}




int create_min_max_array(struct Wire_s *TestWire_ptr) {
    int x_old, x_new, y_old, y_new;
    int c;
    int i = 0;
    int j = 0;
    int k = 0;
    int num;
    char *pIn;

    pIn = TestWire_ptr->wire_path;
    x_new = 0;  // assign origin (0,0)
    y_new = 0;
    TestWire_ptr->Horiz.Xarray_size = 0;
    TestWire_ptr->Vert.Yarray_size = 0;
    TestWire_ptr->pts.pt_size = 0;

    // determine x_old, x_new, y_old, y_new
    while (*pIn != '\0') {
        if (isalpha(*pIn)) {
            c = *pIn++;
            num = strtol(pIn, &pIn, 10);
        }

        y_old = y_new;
        x_old = x_new;
        TestWire_ptr->single_move[k] = num;

        switch (c) {
            case 'U':
                y_new += num;
                break;
            case 'D':
                y_new -= num;
                break;
            case 'R':
                x_new += num;
                break;
            case 'L':
                x_new -= num;
                break;
            case '\n':
                return 0;
                break;
            default:
                printf("ERROR : unable to create x_new or y_new\n c = %i\n", c);
        };

        if (x_new - x_old == 0) {           // horizontal test
            TestWire_ptr->Vert.X[i] = x_old;
            TestWire_ptr->Vert.Ymin[i] = MIN(y_old, y_new);
            TestWire_ptr->Vert.Ymax[i] = MAX(y_old, y_new);
            TestWire_ptr->Vert.Yarray_size++;
            i++;
        }

        if (y_new - y_old == 0) {           // vertical test
            TestWire_ptr->Horiz.Y[j] = y_old;
            TestWire_ptr->Horiz.Xmin[j] = MIN(x_old, x_new);
            TestWire_ptr->Horiz.Xmax[j] = MAX(x_old, x_new);
            TestWire_ptr->Horiz.Xarray_size++;
            j++;
        }
        TestWire_ptr->pts.X[k] = x_new;
        TestWire_ptr->pts.Y[k++] = y_new;
        TestWire_ptr->pts.pt_size++;
        pIn += 1;
    }
    return 0;
}

void part1(FILE *filename) {

    fscanf(filename, "%s", red_wire.wire_path);
    fscanf(filename, "%s", black_wire.wire_path);

    create_min_max_array(&red_wire);
    create_min_max_array(&black_wire);

    struct Crossing_s crossing_array;
    for (int i = 0; i < 100; i++){
        crossing_array.X[i] = 0;
        crossing_array.Y[i] = 0;
    }
    crossing_array.Crossing_size = 0;

    find_crossing(&crossing_array, &red_wire, &black_wire);

    //  calculate distance from each matching coordinate
    int distance[100] = { 0 };
    int j = 0;
    for (int i = 0; i < DEFAULT_SIZE; i += 1)
        distance[j++] = abs(crossing_array.X[i]) + abs(crossing_array.Y[i]);

    //  answer is shortest distance
    int i = 0;
    int answer = distance[0];
    for (i = 1; i < 100; i++)
        if (distance[i] < answer && distance[i] != 0)
            answer = distance[i];

    printf("Part1: Shortest distance is %d\n", answer);

}

void part2(FILE *filename) {
    fscanf(filename, "%s", red_wire.wire_path);
    fscanf(filename, "%s", black_wire.wire_path);

    create_min_max_array(&red_wire);
    create_min_max_array(&black_wire);

    struct Crossing_s crossing_array;
    for (int i = 0; i < 100; i++){
        crossing_array.X[i] = 0;
        crossing_array.Y[i] = 0;
    }
    crossing_array.Crossing_size = 0;

    find_crossing(&crossing_array, &red_wire, &black_wire);

    printf("red_wire.pts.X: ");
    print_array(red_wire.pts.X);
    puts("\n");
    printf("red_wire.pts.Y: ");
    print_array(red_wire.pts.Y);
    puts("\n");

    printf("black_wire.pts.X: ");
    print_array(black_wire.pts.X);
    puts("\n");
    printf("black_wire.pts.Y: ");
    print_array(black_wire.pts.Y);
    puts("\n");
    int i = 1;
    int j = 0;
    for ( ; i < red_wire.pts.pt_size; i++, j = 0){
        for ( ; j < crossing_array.Crossing_size; j++){

            if (((red_wire.pts.X[i] - red_wire.pts.X[i-1]) == 0) && (crossing_array.X[j] == red_wire.pts.X[i]))
                if ((abs(red_wire.pts.Y[i-1]) < abs(crossing_array.Y[j])) && (abs(crossing_array.Y[j]) < abs(red_wire.pts.Y[i]))){
                    red_wire.running_total = red_wire.running_total + abs(crossing_array.Y[j] - red_wire.pts.Y[i]);
                    printf("partial_A");
                    red_wire.cross_length[j] = red_wire.running_total;

                }
            if (((red_wire.pts.Y[i] - red_wire.pts.Y[i-1]) == 0) && (crossing_array.Y[j] == red_wire.pts.Y[i]))
                if ((abs(red_wire.pts.X[i-1]) < abs(crossing_array.X[j])) && (abs(crossing_array.X[j]) < abs(red_wire.pts.X[i]))){
                    red_wire.running_total = red_wire.running_total + abs(crossing_array.X[j] - red_wire.pts.X[i]);
                    printf("partial_B");
                    red_wire.cross_length[j] = red_wire.running_total;
                }
            red_wire.running_total += red_wire.single_move[i];

            printf("\nred_wire.running_total: %d", red_wire.running_total);
        }
    }

    for ( i = 0, j = 0; i < black_wire.pts.pt_size; i++, j = 0){
            for ( ; j < crossing_array.Crossing_size; j++){

                if (((black_wire.pts.X[i] - black_wire.pts.X[i-1]) == 0) && (crossing_array.X[j] == black_wire.pts.X[i]))
                    if ((abs(black_wire.pts.Y[i-1]) < abs(crossing_array.Y[j])) && (abs(crossing_array.Y[j]) < abs(black_wire.pts.Y[i]))){
                        black_wire.running_total = black_wire.running_total + abs(crossing_array.Y[j] - black_wire.pts.Y[i]);
                        printf("partial_A");
                        black_wire.cross_length[j] = black_wire.running_total;

                    }
                if (((black_wire.pts.Y[i] - black_wire.pts.Y[i-1]) == 0) && (crossing_array.Y[j] == black_wire.pts.Y[i]))
                    if ((abs(black_wire.pts.X[i-1]) < abs(crossing_array.X[j])) && (abs(crossing_array.X[j]) < abs(black_wire.pts.X[i]))){
                        black_wire.running_total = black_wire.running_total + abs(crossing_array.X[j] - black_wire.pts.X[i]);
                        printf("partial_B");
                        black_wire.cross_length[j] = black_wire.running_total;
                    }
                black_wire.running_total += black_wire.single_move[i];

                printf("\nblack_wire.running_total: %d", black_wire.running_total);
            }
        }

    printf("\nred_wire.cross_length: ");
    print_array(red_wire.cross_length);
    puts("\n");

    printf("\nblack_wire.cross_length: ");
    print_array(black_wire.cross_length);
    puts("\n");
}

FILE * load_file(void){
    const char *path = IN_FILE;
    FILE *input;
    input = fopen(path, "r");

    if (!input) {
        fprintf(stderr, "ERROR: could not open %s\n", path);
        exit(EXIT_FAILURE);
    }
    return input;
}

int main(void) {
    FILE *input = load_file();
    part1(input);
    part2(input);
    fclose(input);

    return EXIT_SUCCESS;
}

