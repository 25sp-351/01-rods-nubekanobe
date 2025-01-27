#include <stdio.h> 
#include <stdlib.h>

#define LENGTH 0
#define PRICE 1
#define ARR_DIM1 30
#define ARR_DIM2 2


/* Prototypes */

int solveRods(int lengthsPrices[][ARR_DIM2], int remainingLength, int options, int currentPath[], int bestPath[]); 

void displayPrompt(int rodLength);

int readUserInput(int lengthsPrices[][ARR_DIM2]);

void displayUserInput(int lengthsPrices[][ARR_DIM2], int options);

void displayResults(int lengthsPrices[][ARR_DIM2], int options, int bestPath[], int maximumValue);


/***************************************************************************/
/* This program reads a data from a standard input stream and stores it in */
/* 2D array. The data contains various cut lengths and their respective    */
/* prices as a basis for solving the Rod Cutting Problem.                  */
/***************************************************************************/


int main(int argc, char *argv[]){

    /* converts the command line argument from char to int */
    /* and stores the value in supRodLength                */

    int rodLength = atoi(argv[1]);

    displayPrompt(rodLength); 


    /* 2D array to store the lengths and their respective prices */
    /* options will count the number of elements                 */

    int lengthsPrices[ARR_DIM1][ARR_DIM2] = {0};  
   
    int options = readUserInput(lengthsPrices); 

    /* Display the Lengths and Prices entered by the user */

    displayUserInput(lengthsPrices, options);

    /* Store the cut count. These are NOT working as intended */

    int currentPath[ARR_DIM1] = {0}; 
    int bestPath[ARR_DIM1] = {0};

    /* Solve Rod Cutting Problem */

    int maximumValue = solveRods(lengthsPrices, rodLength, options, currentPath, bestPath);

    displayResults(lengthsPrices, options, bestPath, maximumValue); 

    return 0; 

}


/************* SOLVE_RODS ******************/
/* This function solves the rod cutting    */
/* problem using recursion. Every possible */ 
/* combination of cuts is considered and   */
/* the maximum sum is returned             */
/*******************************************/

int solveRods(int lengthsPrices[][2], int remainingLength, int options, int currentPath[], int bestPath[]){

    /* Base case. There is no rod length left to cut */
    /* so the function returns 0                     */

    if (remainingLength <= 0){

        return 0; 

    }

    /* currentMaximum stores the largest sum within each call stack */
    /* and is updated with the maximum value found, then eventually */ 
    /* returned up to the previous call stack                       */

    int currentMaximum = 0; 

    for (int i = 0; i < options; i++){

        currentPath[i]++; 
        
        /* Length of the cut must be less than or equal to the remaining length */
        /* to be considered a valid cut, and will continue the recusive call   */

        if (lengthsPrices[i][LENGTH] <= remainingLength){

            
            int newMaximum = lengthsPrices[i][PRICE] + solveRods(lengthsPrices, 
                remainingLength - lengthsPrices[i][LENGTH], options, currentPath, bestPath); 
            
            
            if (newMaximum >= currentMaximum){

                currentMaximum = newMaximum;


                /* Copy contents of currentPath to bestPath */

                for (int j = 0; j < options; j++){

                    bestPath[j] = currentPath[j]; 

                }

            }

        }

        currentPath[i]--;

    }

    return currentMaximum; 
 
}

/**********DISPLAY_RESULTS *****************/
/* This function prompts the user to enter */
/* the different sized cuts and prices     */
/*******************************************/

void displayPrompt(int rodLength){

    printf("\nSupplied Rod Length: %d\n\n", rodLength); 

    /* Prompts the user to enter values in a specified format */

    printf("Enter Different Sized Cuts and Prices\n");
    printf("Format is 'LENGTH, PRICE'\n"); 
    printf("Enter 'CTRL + D' or A Single Integer Value to Stop\n");
    printf("=========================\n\n");

}

/**********READ_USER_INPUT *****************/
/* This function reads the user input and  */
/* stores it in a 2D array                 */
/*******************************************/

int readUserInput(int lengthsPrices[][ARR_DIM2]){

    int options = 0;

    while(scanf("%d, %d", &lengthsPrices[options][LENGTH], &lengthsPrices[options][PRICE]) == 2){

        options++; 

    }

    return options;

}


/**********DISPLAY_USER_INPUT **********/
/* This function displays information  */
/* entered by the user                 */
/***************************************/

void displayUserInput(int lengthsPrices[][ARR_DIM2], int options){


    printf("\nLengths and Prices Entered\n");
    printf("=========================\n\n");

    for (int i = 0; i < options; i++){

       printf("Length: %d, Price: %d\n", lengthsPrices[i][LENGTH], lengthsPrices[i][PRICE]);
       
    }
}


/**********DISPLAY_RESULTS *****************/
/* This function displays the cutting list */
/* and the total value.                    */
/*******************************************/

void displayResults(int lengthsPrices[][2], int options, int bestPath[], int maximumValue){

    /* Displays results */

    printf("\nCutting List:\n");
    printf("==================\n\n");

    for (int i = 0; i < options; i++){

        printf("%d @ %d = %d\n", bestPath[i], lengthsPrices[i][LENGTH], lengthsPrices[i][PRICE] * bestPath[i]); 

    }

    printf("\nValue: %d\n\n", maximumValue);

}


