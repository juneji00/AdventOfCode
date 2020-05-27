# Name        : day_2_part2.py
# Author      : PS
# Date		  : 5.28.20
# Description : Day 2: 1202 Program Alarm, part2
#
#			 To complete the gravity assist, you need to determine what
#			 pair of inputs produces the output 19690720.
#
#			 The inputs should still be provided to the program by replacing
#			 the values at addresses 1 and 2, just like before. In this
#			 program, the value placed in address 1 is called the noun,
#			 and the value placed in address 2 is called the verb. Each
#			 of the two input values will be between 0 and 99, inclusive.
#
#			 Once the program has halted, its output is available at
#			 address 0, also just like before. Each time you try a pair of
#			 inputs, make sure you first reset the computer's memory to the
#			 values in the program (your puzzle input) - in other words,
#			 don't reuse memory from a previous attempt.
#
#			 Find the input noun and verb that cause the program to produce
#			 the output 19690720. What is 100 * noun + verb? (For example, if
#			 noun=12 and verb=2, the answer would be 1202.)

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
		
def Intcode( TestNoun, TestVerb, array):
	array[1] = TestNoun
	array[2] = TestVerb
	
	i = 0
	ADD = 1
	MUL = 2
	HALT = 99
	INPUT1 = 1
	INPUT2 = 2
	OUTPUT = 3

	while i < len(array):
		if array[i] == ADD:
			addr1 = array[i + INPUT1]
			addr2 = array[i + INPUT2]
			addr3 = array[i + OUTPUT]
			array[addr3] = array[addr1] + array[addr2]

		elif array[i] == MUL:
			addr1 = array[i + INPUT1]
			addr2 = array[i + INPUT2]
			addr3 = array[i + OUTPUT]
			array[addr3] = array[addr1] * array[addr2]

		elif array[i] == HALT:
			return array[0]
			break

		i += 4
	return array[0]

print("\nDay 2: 1202 Program Alarm, part 2")
outfile.write("Day 2: 1202 Program Alarm, part 2")
header( "INTCODE Solutions" )
print("Item\t\tNoun\t\tVerb\t\tOutput\n")
outfile.write("Item\t\tNoun\t\tVerb\t\tOutput\n")

with open('gravity_assist_program.csv', newline = '') as f:
	reader = csv.reader(f)
	for L in reader:
		Lprime = L

L = list(map(int, L))
Lprime = list(map(int, Lprime))

item = 1
TARGET = 19690720

for noun in range(0, 100):
	for verb in range(0, 100):		
		# reset memory to initial values
		L = Lprime[:]
		value = Intcode( noun, verb, L)
		if value == TARGET:
			Tnoun = noun
			Tverb = verb
		print(item,"\t\t", noun, "\t\t", verb, "\t\t", value);
		msg = [item,"\t\t\t", noun, "\t\t\t", verb, "\t\t\t", value, '\n'];
		for x in msg:
			outfile.write(str(x))
		item += 1
	
print("\nOutput Target", TARGET, "is generated by using",\
			" noun = ", Tnoun, "and ", Tverb)
print("\nPUZZLE ANSWER: 100 * noun + verb = ", 100 * Tnoun + Tverb, '\n')

msg1 = ["\nOutput Target ", TARGET, " is generated by using",\
			" noun = ", Tnoun, " and ", Tverb]
msg2 = ["\n\nPUZZLE ANSWER: 100 * noun + verb = ", 100 * Tnoun + Tverb, '\n']

for x in msg1:
	outfile.write(str(x))
for x in msg2:
	outfile.write(str(x))

outfile.close()