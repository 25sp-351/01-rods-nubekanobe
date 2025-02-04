#include <stdio.h> 
#include <stdlib.h>

#define LENGTH_INDEX 0
#define PRICE_INDEX 1
#define ARR_DIM1 30
#define ARR_DIM2 2

typedef struct {

    int cut_length; 
    int cut_price; 
    int cut_count;
    int total_value_of_cut; 

} Cut; 

typedef struct {

    int rod_length; 
    int number_of_options; 
    int remainder;  
    int maximum_value_of_cuts;  
    int* cut_counter; 
    Cut* cut; 

} Cut_list; 


/* Prototypes */ 

void input_lengths_and_prices(int lengths_and_prices[][ARR_DIM2], int* number_of_options);

Cut_list* generate_cut_list_struct(int lengths_and_prices[][ARR_DIM2], int number_of_options, int rod_length);

void solve_rods(Cut_list* optimal_cut_list, int remaining_length, int current_value_of_cuts);

void copy_best_cut_counts(Cut_list* optimal_cut_list);

void calculate_cut_values_and_remainder(Cut_list* opimal_cut_list);

void display_cut_list(Cut_list* optimal_cut_list);

void display_lengths_and_prices(int lengths_and_prices[][ARR_DIM2], int number_of_options); // FOR DEBUG


/***************************************************************************/
/* This program reads a data from a standard input stream and stores it in */
/* 2D array. The data contains various cut lengths and their respective    */
/* prices as a basis for solving the Rod Cutting Problem.                  */
/***************************************************************************/


int main(int argc, char *argv[]){

    if (argc != 2){

        printf("Failed to provide a valid rod length");
        return 1; 

    }

    int rod_length; 

    /* Check if the input is a valid integer */
    
    char check_for_char;

    if (sscanf_s(argv[1], "%d%c", &rod_length, &check_for_char) != 1 || rod_length <= 0){

        printf("Failed to provide a valid rod length");

        return 1; 

    }

    int lengths_and_prices[ARR_DIM1][ARR_DIM2] = {0};  
   
    int number_of_options = 0; 
    
    input_lengths_and_prices(lengths_and_prices, &number_of_options); 

    Cut_list* optimal_cut_list = generate_cut_list_struct(lengths_and_prices, number_of_options, rod_length);

    int current_value_of_cuts = 0; 

    int remaining_length = optimal_cut_list->rod_length; 
    
    solve_rods(optimal_cut_list, remaining_length, current_value_of_cuts);

    calculate_cut_values_and_remainder(optimal_cut_list); 

    display_cut_list(optimal_cut_list); 

    free(optimal_cut_list->cut);

    free(optimal_cut_list->cut_counter); 

    free(optimal_cut_list);

    return 0; 

}


/************* SOLVE_RODS ******************/
/* This function solves the rod cutting    */
/* problem using recursion.                */
/*                                         */                       
/*******************************************/

void solve_rods(Cut_list* optimal_cut_list, int remaining_length, int current_value_of_cuts){

    if(current_value_of_cuts > optimal_cut_list->maximum_value_of_cuts){

        optimal_cut_list->maximum_value_of_cuts = current_value_of_cuts; 

        copy_best_cut_counts(optimal_cut_list);

    }

    if (remaining_length <= 0){

        return; 

    }


    for (int current_cut = 0; current_cut < optimal_cut_list->number_of_options; current_cut++){

        if (optimal_cut_list->cut[current_cut].cut_length <= remaining_length){

            optimal_cut_list->cut_counter[current_cut]++; 

            /* These variables are intended to simplify the parameters being passed for readability */

            int remaining_length_after_this_cut = remaining_length - optimal_cut_list->cut[current_cut].cut_length;

            int value_of_cuts_after_this_cut = current_value_of_cuts + optimal_cut_list->cut[current_cut].cut_price;

            solve_rods(optimal_cut_list, remaining_length_after_this_cut, value_of_cuts_after_this_cut);      

            optimal_cut_list->cut_counter[current_cut]--; 
            
        }

    }

    return;  
 
}


/**********INPUT_LENGHTS_AND_PRICES*********/
/* This function reads the user input and  */
/* stores it in a 2D array                 */
/*                                         */
/* Output Parameters: number_of_options    */
/*******************************************/

void input_lengths_and_prices(int lengths_and_prices[][ARR_DIM2], int* number_of_options){

    char buffer[100]; 

    int length, price;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        
        if (sscanf_s(buffer, "%d, %d", &length, &price) == 2) {
            
            if (length > 0 && price > 0) {
                
                lengths_and_prices[*number_of_options][LENGTH_INDEX] = length;
                
                lengths_and_prices[*number_of_options][PRICE_INDEX] = price;
                
                (*number_of_options)++;
            } 
        }
    }

}


/**********DISPLAY_USER_INPUT **********/
/* This function displays information  */
/* entered by the user for DEBUG       */
/***************************************/

void display_lengths_and_prices(int lengths_and_prices[][ARR_DIM2], int number_of_options){


    printf("\nLengths and Prices Entered\n");
    printf("=========================\n\n");

    for (int current_cut = 0; current_cut < number_of_options; current_cut++){

       printf("Length: %d, Price: %d\n", lengths_and_prices[current_cut][LENGTH_INDEX], lengths_and_prices[current_cut][PRICE_INDEX]);
       
    }
}


/**********DISPLAY_CUT_LIST *****************/
/* This function displays the cutting list */
/* and the total value.                    */
/*******************************************/

void display_cut_list(Cut_list* optimal_cut_list){


    for (int current_cut = 0; current_cut < optimal_cut_list->number_of_options; current_cut++){

        if (optimal_cut_list->cut[current_cut].cut_count == 0){
            
            continue;

        }

        int cut_count = optimal_cut_list->cut[current_cut].cut_count; 

        int cut_length = optimal_cut_list->cut[current_cut].cut_length;

        int cut_total_value = optimal_cut_list->cut[current_cut].total_value_of_cut;

        printf("%d @ %d = %d\n", cut_count, cut_length, cut_total_value); 

    }

    printf("Remainder: %d\n", optimal_cut_list->remainder);

    printf("Value: %d", optimal_cut_list->maximum_value_of_cuts);

}


/**********COPY_BEST_CUT_COUNTS****************/
/* When a new maximum value is found, copies  */
/* the current cut counts used to find that   */
/* maximum value to the cut_count data field  */
/* of each cut                                */
/**********************************************/

void copy_best_cut_counts(Cut_list* optimal_cut_list){

    for (int current_cut = 0; current_cut < optimal_cut_list->number_of_options; current_cut++){

        optimal_cut_list->cut[current_cut].cut_count = optimal_cut_list->cut_counter[current_cut]; 

    }

}

/******CALCULATE_CUT_VALUES_AND_REMAINDER********/
/* When a final maximum value of cuts is found, */
/* calculates the total values of each cut and  */
/* the remainder of rod length                  */
/************************************************/


void calculate_cut_values_and_remainder(Cut_list* optimal_cut_list){

     optimal_cut_list->remainder = optimal_cut_list->rod_length;

    for (int current_cut = 0; current_cut < optimal_cut_list->number_of_options; current_cut++){

        /* The purpose of this pointer is to make the code more concise */

        Cut *current_p = &optimal_cut_list->cut[current_cut];

        current_p->total_value_of_cut = current_p->cut_price * current_p->cut_count;

        optimal_cut_list->remainder -= current_p->cut_length * current_p->cut_count; 

    }
    
}

/**********GENERATE_CUT_LIST_STRUCT*********/
/* This function generates the cut_list    */
/* struct and initializes its values       */
/*******************************************/

Cut_list* generate_cut_list_struct(int lengths_and_prices[][ARR_DIM2], int number_of_options, int rod_length){

    Cut_list* optimal_cut_list = (Cut_list*)malloc(sizeof(Cut_list));

    optimal_cut_list->rod_length = rod_length; 

    optimal_cut_list->remainder = rod_length; 

    optimal_cut_list->maximum_value_of_cuts = 0;

    optimal_cut_list->number_of_options = number_of_options;

    optimal_cut_list->cut = (Cut*)malloc(sizeof(Cut) * number_of_options);

    optimal_cut_list->cut_counter = (int*)malloc(sizeof(int) * number_of_options);

    for (int current_cut = 0; current_cut < number_of_options; current_cut++) {
    
        optimal_cut_list->cut_counter[current_cut] = 0;
    
    }



    for (int current_cut = 0; current_cut < number_of_options; current_cut++) {
    
        optimal_cut_list->cut[current_cut].cut_length = lengths_and_prices[current_cut][LENGTH_INDEX];
        
        optimal_cut_list->cut[current_cut].cut_price = lengths_and_prices[current_cut][PRICE_INDEX];
        
        optimal_cut_list->cut[current_cut].cut_count = 0;
        
        optimal_cut_list->cut[current_cut].total_value_of_cut = 0;

    }  

    return optimal_cut_list;

}

