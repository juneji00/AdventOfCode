### ============================================================================
### Name        : day_3_part2.py
### Author      : PS
### Date        : 6.12.20
### Description : Day 3: Crossed Wires, part1
### Description : To fix the circuit, you need to find the intersection point
###              closest to the central port. Because the wires are on a grid,
###              use the Manhattan distance for this measurement. While the wires
###              do technically cross right at the central port where they both
###              start, this point does not count, nor does a wire count as
###              crossing with itself.
###
###              For example, if the first wire's path is R8,U5,L5,D3, then starting
###              from the central port (o), it goes right 8, up 5, left 5, and finally
###              down 3.  Then, if the second wire's path is U7,R6,D4,L4, it goes up 7,
###              right 6, down 4, and left 4. These wires cross at two locations
###              (marked X), but the lower-left one is closer to the central port:
###              its distance is 3 + 3 = 6.
###
###              Here are a few more examples:
###              R75,D30,R83,U83,L12,D49,R71,U7,L72
###              U62,R66,U55,R34,D71,R55,D58,R83 = distance 159
###              R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51
###              U98,R91,D20,R16,D67,R40,U7,R15,U6,R7 = distance 135
###              What is the Manhattan distance from the central port to the
###              closest intersection?
### ============================================================================
###   Solution pseudocode
###   *  1. get array1 and array2 from input file
###   *  2. assign coordinates to each array vector
###   *  3. compare each set of coordinates between arrays
###   *        if there's a match, store the coordinate
###   *  4. calculate distance from each matching coordinate
###   *  5. answer is shortest distance

import csv

def get_coordinate( wireVector, x_old, y_old ):
    'figure out new x,y coordinates from old x,y plus vector'
    direction = wireVector[:1]
    num = int(wireVector[1:])

    y_new = y_old
    x_new = x_old

    if direction == 'U':
        y_new += num
#        print("move" + direction, num)
    elif direction == 'D':
        y_new -= num
#        print("move" + direction, num)
    elif direction == 'R':
        x_new += num
#        print("move" + direction, num)
    elif direction == 'L':
        x_new -= num
#        print("move" + direction, num)
    else:
        print("ERROR: unable to create x_new or y_new. c = ", c)
    return x_new, y_new

def min_max_assignment( a, b ):
    'return min and max of the given inputs'
    c = min(a, b)
    d = max(a, b)
    return c, d
    

def min_max_array( Input ):
    'return two horizontal and vertical lists formatted with min/max values'
    x_new = 0
    y_new = 0
    Vert = []
    Horiz = []
 
    for i in range(len(Input)):
        vector = Input[i]
        y_old = y_new
        x_old = x_new
        x_new, y_new = get_coordinate( vector, x_old, y_old )
        
        if x_new - x_old == 0:  ## vertical test
            Xval = x_old
            Ymin, Ymax = min_max_assignment(y_old, y_new)
            Vgroup = [Xval, Ymin, Ymax]
            Vert.append(Vgroup)
            
        if y_new - y_old == 0:  ## horizontal test
            Yval = y_old
            Xmin, Xmax = min_max_assignment(x_old, x_new)
            Hgroup = [Yval, Xmin, Xmax]
            Horiz.append(Hgroup)
    return Horiz, Vert

def find_intersection( array1, array2 ):
    'return a list of intersections from two input lists'
    intersection = []

    for i in range(0,len(array1)):
        for j in range(0,len(array2)):
            if array2[j][1] <= array1[i][0] <= array2[j][2]:
                if array1[i][1] <= array2[j][0] <= array1[i][2]:
                    Xval = array2[j][0]
                    Yval = array1[i][0]
                    coordinate = [Xval, Yval]
                    if coordinate != [0, 0]:  ## ignore origin
                        intersection.append(coordinate) 
    if not intersection:
        print('Error: no crossing detected')
    return intersection

def cross_test( Xcross, Ycross, Xstart, Ystart, Xend, Yend):
    'determines if a crossing has occurred from a pair of x,y coordinates'
    Xflag = False
    Yflag = False
    Cross_Occurrence = False
    Xmin, Xmax = min_max_assignment(Xstart, Xend)
    Ymin, Ymax = min_max_assignment(Ystart, Yend)
    
    if Xend - Xstart == 0 and Xcross == Xstart and Ymin < Ycross < Ymax:
        Xflag = True
        Cross_Occurrence = True

    if Yend - Ystart == 0 and Ycross == Ystart and Xmin < Xcross < Xmax:
        Yflag = True
        Cross_Occurrence = True
       
    return Xflag, Yflag, Cross_Occurrence 

def measure_wire( array ):
    'return the length of the wire'
    x_old = 0
    y_old = 0
    wirerun = 0
    wiretable = [] 
    is_looping = True

    for i in range(len(array)):
        element = array[i]
        x_new, y_new = get_coordinate( element, x_old, y_old )
        
        for j in range(len(crossing)):
            Xcross = crossing[j][0]
            Ycross = crossing[j][1]
            Xflag, Yflag, Cross_flag  = cross_test( Xcross, Ycross,
                                                    x_old, y_old, x_new, y_new)

            if Cross_flag == True and Xflag == True:
                partial_wirerun = wirerun + abs( abs(Ycross) - abs(y_old) )
                wiretable.append([Xcross,Ycross,partial_wirerun])
                Cross_flag = False
                Xflag = False
                
            elif Cross_flag == True and Yflag == True:
                partial_wirerun = wirerun + abs( abs(Xcross) - abs(x_old) )
                wiretable.append([Xcross,Ycross,partial_wirerun])
                Cross_flag = False
                Yflag = False

        y_old = y_new
        x_old = x_new
        if Cross_flag == False:
            wirerun += int(element[1:])
    return wiretable

def TotalIntersectionLengths(list1, list2):
    'create list with format: [Xcross, Ycross, TotalLength]'
    list3 = []
    
    for i in range(len(list1)):
        for j in range(len(list2)):
            if list1[i][0] == list2[j][0] and list1[i][1] == list2[j][1]:
                list3.append([list1[i][0],list1[i][1],list1[i][2] + list2[j][2]])

    return list3

## program start
Day_Title = "Day 3: Crossed Wires, part 2"

## get lists from input file
f = open('front_panel.txt', 'r') 
#f = open('example2.txt', 'r') 

wire1String = f.readline()
wire2String = f.readline()

wire1 = wire1String.split(",")
wire2 = wire2String.split(",")

## remove new line
wrongFormat = wire1.pop()
rightFormat = wrongFormat[:-1]
wire1.append(rightFormat)

## for each input list, create separate nested vertical and horizontal lists
## in the following format:
## 	vert_array = [X value, Ymin, Ymax]
##   	horiz_array = [Y value, Xmin, Xmax]

wire1_horiz , wire1_vert = min_max_array(wire1)
wire2_horiz , wire2_vert = min_max_array(wire2)

## test for intersection against only horizontal to vertical members
## enter crossing coordinates into crossing list
crossing = []
crossPairA = find_intersection( wire1_horiz, wire2_vert )
crossPairB = find_intersection( wire2_horiz, wire1_vert )

crossPairA.extend(crossPairB)
crossing = crossPairA.copy()

distance = []
for i in range(len(crossing)):
    value = abs(crossing[i][0]) + abs(crossing[i][1])
    distance.append(value)

print("Part 1 Answer: Shortest distance is", min(distance))

## begin part 2 analysis
red_wire = measure_wire(wire1)
blue_wire = measure_wire(wire2)

total_length_table = TotalIntersectionLengths(red_wire, blue_wire)

answer = total_length_table[0][2] #load first value for minimum check
for i in range(len(total_length_table)):
    if total_length_table[i][2] < answer:
        answer = total_length_table[i][2]

print("Part 2 Answer: Shortest wire length is", answer)

f.close() 
