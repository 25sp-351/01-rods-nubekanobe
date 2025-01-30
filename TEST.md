# These are tests cases for rods.c (Solves Rod Cutting Problem)

# Test Case 1: Program Accepts Intended Input 

### Description: 
A test to verify that the user can input a rod size and series of lengths and prices separated by a comma. 

### Input: 
- Rod Length: 10
- Cuts: 3,3 ; 10,1 ; 2,11 

### Expected Output: 
- Supplied Rod Length: 10 
- Length: 3, Price: 3
- Length: 10, Price: 1
- Length: 2, Price: 11

### Actual Output

Supplied Rod Length: 10

Enter Different Sized Cuts and Prices
Format is 'LENGTH, PRICE'
Enter 'CTRL + D' or A Single Integer Value to Stop
=========================

3,3
10,1
2,11
^D

Lengths and Prices Entered
=========================

Length: 3, Price: 3
Length: 10, Price: 1
Length: 2, Price: 11

Cutting List:
==================

0 @ 3 = 0
0 @ 10 = 0
1 @ 2 = 11

Value: 55


# Test Case 2: Program Outputs Correct Value 

### Description: 
A test to verify that the program calculates the correct maximum value solution to the rod cutting problem  

### Input: 
- Rod Length: 5
- Cuts: 1,2 ; 2,1 ; 3,3

### Expected Output:
- Value: 10

### Actual Output:
Value: 9



# Test Case 2.1: Program Outputs Correct Value 

### Description: 
An slightly modified test to verify that the program calculates the correct maximum value solution to the rod cutting problem  

### Input: 
- Rod Length: 5
- Cuts: 1,1 ; 2,3 ; 3,6

### Expected Output:
- Value: 9

### Actual Output:
Value: 9