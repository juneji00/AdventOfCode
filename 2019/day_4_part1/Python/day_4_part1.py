# day_4_part1.py
# Advent of Code 2019 - Day 4 part 1
# Author: PS
# Date: 6.25.20

def repeating_digits(d):
    num = list(map(int,str(d)))
    for i in range(len(num)-1):
        if num[i] == num[i+1]:
            return True  
    return False

def increasing_digits(d):
    num = list(map(int,str(d)))
    for i in range(len(num)-1):
        if int(num[i]) <= int(num[i+1]):
            continue
        else:
            return False
    return True

def part1(raw_input):
    low = raw_input[:6]
    high = raw_input[-6:]

    possible_solution = []
    
    for x in range(int(low), int(high)+1, 1):
        if repeating_digits(x) and increasing_digits(x):
            possible_solution.append(x)

    print("Number of possible solutions: ", len(possible_solution))
        
def main():
    puzzle_input = "146810-612564"
    part1(puzzle_input)

if __name__ == "__main__":
    main()


