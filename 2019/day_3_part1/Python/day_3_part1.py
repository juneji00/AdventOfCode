# ============================================================================
# Name        : day_3_part1.py
# Author      : PS
# Date		  : 6.4.20
# Description : Day 3: Crossed Wires, part1
# Description : To fix the circuit, you need to find the intersection point
# 	 	 	   closest to the central port. Because the wires are on a grid,
# 	 	 	   use the Manhattan distance for this measurement. While the wires
# 	 	 	   do technically cross right at the central port where they both
# 	 	 	   start, this point does not count, nor does a wire count as
# 	 	 	   crossing with itself.
#
#			   For example, if the first wire's path is R8,U5,L5,D3, then starting
#			   from the central port (o), it goes right 8, up 5, left 5, and finally
#			   down 3.  Then, if the second wire's path is U7,R6,D4,L4, it goes up 7,
#			   right 6, down 4, and left 4. These wires cross at two locations
#			   (marked X), but the lower-left one is closer to the central port:
#			   its distance is 3 + 3 = 6.
#
#			   Here are a few more examples:
#		       R75,D30,R83,U83,L12,D49,R71,U7,L72
#			   U62,R66,U55,R34,D71,R55,D58,R83 = distance 159
#			   R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51
#			   U98,R91,D20,R16,D67,R40,U7,R15,U6,R7 = distance 135
#			   What is the Manhattan distance from the central port to the
#			   closest intersection?
# ============================================================================
#	Solution pseudocode
#	*  1. get array1 and array2 from input file
#	*  2. assign coordinates to each array vector
#	*  3. compare each set of coordinates between arrays  (use strstr()?)
#	*        if there's a match, store the coordinate
#	*  4. calculate distance from each matching coordinate
#	*  5. answer is shortest distance

import csv

outfile = open('readme.txt','w')

def header( var ):
	msg = ["\n*****************************************************",var,		
			"*****************************************************"]
	msg2 = ["\n\n*****************************************************\n",var,		
			"\n*****************************************************\n"]
	for x in msg:
		print(x)
	for x in msg2:
		outfile.write(x)
		
Day_Title = "Day 3: Crossed Wires, part 1"

print("\n" + Day_Title)
outfile.write( Day_Title )
header( "Wiring Solutions" )

#	*  1. get array1 and array2 from input file

readfile = open('test.txt', 'r') 
	

for line in readfile:
	wire1path = line
	wire2path = line

print(wire1path)
print(wire2path)
	



outfile.close()