import math

subtotal = 0
item = 0

def round_down(n):
    return math.floor(n)

infile = open('module_mass.txt')


print("Fuel Calculation Table")
print("*********************************************************")
print("ITEM		MASS		FUEL		SUBTOTAL")
print("*********************************************************")

for line in infile:
	mass = int(line)
	fuel = round_down(mass / 3 ) - 2
	subtotal += fuel
	print(item,"\t\t%d" % mass,"\t\t%d" % fuel,"\t\t%d" % subtotal)
	item += 1
	
print("\nTotal Fuel is %d" % subtotal)

close('module_mass.txt')