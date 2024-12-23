//
//  main.c
//  Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define EXERCISEFILEPATH "exercises.txt"
#define DIETFILEPATH "diets.txt"
#define HEALTHFILEPATH "health_data.txt"

static int choice;

int main() {
	// To initialize the health data object
    HealthData health_data = {0};
    
    // Tocode: to read the list of the exercises and diets
    loadDiets(DIETFILEPATH);
	loadExercises(EXERCISEFILEPATH);
	
	int remaining_calories; //Setting variables for ending conditions
	
    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    do {
    	
    	remaining_calories = health_data.total_calories_intake - (1300 + health_data.total_calories_burned); // 1300 = Basal Metabolic Rate
    	
	   	if (remaining_calories == 0){  // program ending condition 
            printf("You have consumed all your calories for today! \n");
			printf("System exiting...\n");           
			saveData(HEALTHFILEPATH, &health_data); // Function operates only during system end
            break;
		} 
		else{
			printf("\n=======================================================================\n");
        	printf("[Healthcare Management Systems] \n");
        	printf("1. Exercise \n");
        	printf("2. Diet \n");
        	printf("3. Show logged information \n");
        	printf("4. Exit \n");
        	printf("Select the desired number: ");
        	scanf("%d", &choice);
        	printf("=======================================================================\n");
        
        
			// ToCode: to run the sysmtem based on the user's choice
        	switch (choice) {
            	case 1:
            		inputExercise(&health_data); 
                	break;
                
            	case 2:
            		inputDiet(&health_data);
	                break;
	                
	            case 3:
	            	printHealthData(&health_data);
	                break;
	                
	            case 4:
					printf("There is no file for health data.\n");       //when choice is 4, saveData function is not working. 
	    			printf("Exit the system.\n");
	    			printf("=======================================================================\n");
	                break;
	                
	            default:
	                printf("[Error] Invalid option. \n");
	                printf("Please try again! \n");
	        }
    	}
    } while (choice != 4); 
	//Due to the condition related to remaining_calories in the if statement, the while loop condition is only determined by choice not being 4.
		
    return 0;
}

