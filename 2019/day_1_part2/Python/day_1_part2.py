# Name        : day_1_part2.py
# Author      : PS
# Date		  : 5.27.20
# Description : Day 1: The Tyranny of the Rocket Equation.
# 				Calculate the total fuel requirement to launch a rocket.
#				Fuel(x) = round( x / 3 ) - 2 , where x = module mass
# 				NOTE: part 2 accounts for the mass of fuel
# 				Answer = sum of Fuel(x) for all inputs

infile = open('module_mass.txt','r')
outfile = open('solution.txt','w')

header = ["Fuel Calculation Table\n",\
		  "*****************************************************\n",\
		  "ITEM\t\tMASS\t\tFUEL\t\tSUBTOTAL\n","*****************************************************\n"]
for x in header:
	print(x)
	outfile.write(x)

subtotal = 0
item = 1
mass = 0

for line in infile:
	mass = [int(line)]
	i = 0
	fuel = [(mass[0] // 3 ) - 2]
	
	while fuel[i] > 0:
		temp = [(fuel[i] // 3 ) - 2]
		if temp[0] > 0:
			fuel = fuel + temp
			i += 1
		else:
			break
			
	n = len(fuel)
	subtotal += sum(fuel)

	#output to file
	rowstring = [str(item), "\t\t\t", str(mass[0]), " \t\t", str(fuel[0]),\
		"\t\t", str(subtotal), "\n"]
	for x in rowstring:
		outfile.write(x)

	#output to screen
	print(item, "\t\t", mass[0], " \t", fuel[0], "\t\t", subtotal)
	item += 1
	
outfile.write("\nTotal Fuel is ")
outfile.write(str(subtotal))	
print("\nTotal Fuel is", subtotal)

close('module_mass.txt')
outfile.close()