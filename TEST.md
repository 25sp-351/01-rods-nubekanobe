# Tests cases for rods.c (Solves Rod Cutting Problem)

# Test Case 1: Program Accepts Valid Rod Lengths Only

### Description: 
A test to verify that the user must provide a valid integer input greater than 0

### Input: 
./rods 0

./rods -1

./rods a

./rods 100a

./rods a100

### Expected Output: 
Indicates that a valid rod length was not provided and terminates the program. 

The program counts the 

### Actual Output
./rods 0
Failed to provide a valid rod length

./rods -1
Failed to provide a valid rod length

./rods a
Failed to provide a valid rod length

./rods 100a
Failed to provide a valid rod length

./rods a100
Failed to provide a valid rod length


# Test Case 2: Program Accepts Valid Piece Sizes and Prices

### Description: 
A test to verify that the user must input piece sizes and prices greater than 0, seperated by a comma

### Input: 
./rods 100
1, 2
3 4
5a, 6
a7, 8
9, 10a
-10, 11
10, -11

### Expected Output: 
Program ignores any input which does not follow the specified format

### Actual Output

Lengths and Prices Entered 
=========================

Length: 1, Price: 2
Length: 9, Price: 10

The program ignores any input that does not follow the specified format. 
If a valid input is followed by a character (9, 10a), then the values 
provided before the character will be treated as valid input and the 
character is ignored. 



# Test Case 3: Program Outputs the Correct Maximum Value, Cutting List, and Remainder

# 3.A 

### Description: 
A test to verify that the correct values are calculated and displayed

### Input: 
./rods 100
51, 97
50, 48
^Z

### Expected Output: 
1 cut of size 51, for a total value of 97, with a remainder of 49

### Actual Output: 
1 @ 51 = 97
Remainder: 49
Value: 97


# 3.B

### Description: 
A test to verify that the order of input does not affect the output and provide incorrect results

### Input: 
./rods 100
50, 48
51, 97
^Z

### Expected Output: 
1 cut of size 51, for a total value of 97, with a remainder of 49

### Actual Output 
1 @ 51 = 97
Remainder: 49
Value: 97


# 3.C

### Description: 
A test to verify that a greater maximum value can be found when provided with an additional option

### Input 
./rods 100
51, 97
23, 10
50, 48
^Z

### Expected Output: 
1 cut of size 51 and 2 cuts of size 23, for a total value of 117, with a remainder of 3

### Actual Output 
1 @ 51 = 97
2 @ 23 = 20
Remainder: 3
Value: 117