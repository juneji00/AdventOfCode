# Name        : day_2_part1.py
# Author      : PS
# Date		  : 5.28.20
# Description : Day 2: 1202 Program Alarm
#			   Create a working Intcode program.  Once you have a working
# 	 	 	   computer, the first step is to restore the gravity assist
# 	 	 	   program (your puzzle input) to the "1202 program alarm" state
# 	 	 	   it had just before the last computer caught fire. To do this,
# 	 	 	   before running the program, replace position 1 with the value 12
# 	 	 	   and replace position 2 with the value 2.
#
# 	 	 	   What value is left at position 0 after the program halts?

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

print("\nDay 2: 1202 Program Alarm")
outfile.write("Day 2: 1202 Program Alarm")
header( "Original Program" )

with open('gravity_assist_program.csv', newline = '') as f:
	reader = csv.reader(f)
	for L in reader:
		print(L)
		
for element in L:
	outfile.write("%i " % int(element))
	
L = list(map(int, L))

header( "Program Pass 1" )
L[1] = 12
L[2] = 2

for element in L:
	outfile.write("%i " % int(element))

i = 0
ADD = 1
MUL = 2
HALT = 99
while i < len(L): 
	if L[i] == ADD:
		L[L[i+3]] = L[L[i+1]] + L[L[i+2]]
	elif L[i] == MUL:
		L[L[i+3]] = L[L[i+1]] * L[L[i+2]]
	elif L[i] == HALT:
		break
	else:
		print("ERROR")
	i += 4
	
print(i)
header( "Program Pass 2" )
print(L)	

for element in L:
	outfile.write("%i " % int(element))
	
outfile.write("\n\nValue at position 0 is ")
outfile.write(str(L[0]))	
print("\nValue at position 0 is", L[0])

outfile.close()