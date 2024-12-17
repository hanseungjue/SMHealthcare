//
//  cal_diets.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0;


/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

     // ToCode: to read a list of the diets from the given file
    while (fscanf(file, "%49s %d", diet_list[diet_list_size].food_name, &diet_list[diet_list_size].calories_intake) == 2) { 
	//get file data to diet_list using fscanf.
	//while loop condition: the information read by scanf is not equal to 2 = the end of file or reading fails
    	
        if (diet_list_size >= MAX_DIETS){ //when get all data, close loop
        	break;
		}
		
		diet_list_size++; //get information, make size getting bigger because of initializing size 0
    }
    fclose(file);
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice, i;
    
    // ToCode: to provide the options for the diets to be selected
    printf("The list of diets:\n");
    for (i = 0; i < 6; i++) {
        printf("%d. %s (%d kcal)\n", i + 1, diet_list[i].food_name, diet_list[i].calories_intake);
    }
    
	// ToCode: to enter the diet to be chosen with exit option
    printf("7. Exit\n");

    // ToCode: to enter the selected diet in the health data
    printf("Choose(1-7): ");
    scanf("%d", &choice);

    // ToCode: to enter the total calories intake in the health data
	while (choice != 7) { //Exit select -> while loop close, Go back to beginning
        if (choice < 1 || choice > 7) { //when select wrong number
            printf("ERROR! You select wrong number .\n");
            printf("Choose(1-7): ");
    		scanf("%d", &choice);
        } else {
            // one day three meal rules
            if (health_data->diet_count >= 3) {
                printf("You already eat three meals.\n");
                break;
            }

            // food_name: diet_list -> health data copy
            strcpy(health_data->diet[health_data->diet_count].food_name, diet_list[choice - 1].food_name);
            // calories_intake: diet_list -> health data copy
            health_data->diet[health_data->diet_count].calories_intake = diet_list[choice - 1].calories_intake;

            // diet_count count
            health_data->diet_count++;
            // calculate and update total calories
            health_data->total_calories_intake += diet_list[choice - 1].calories_intake;
    	}
	}

}

