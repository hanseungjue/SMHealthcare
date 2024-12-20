//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0;


/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    
    while (fscanf(file, "%49s %d", exercise_list[exercise_list_size].exercise_name, &exercise_list[exercise_list_size].calories_burned_per_minute) == 2) { 
	//get file data to diet_list using fscanf.
	//while loop condition: the information read by scanf is not equal to 2 = the end of file or reading fails
    	
        if (exercise_list_size >= MAX_EXERCISES){ //when get all data, close loop
        	break;
		}
		
		exercise_list_size++; //get information, make size getting bigger because of initializing size 0
    }

    fclose(file);
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    // ToCode: to provide the options for the exercises to be selected
    printf("The list of exercises: \n");


    // ToCode: to enter the exercise to be chosen with exit option
	for (i = 0; i < 6; i++) {
        printf("%d. %s (%d kcal burned per min.)\n", i + 1, exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute);
    }
    
	// ToCode: to enter the diet to be chosen with exit option
    printf("7. Exit\n");

    // ToCode: to enter the selected diet in the health data
    printf("Choose(1-7): ");
    scanf("%d", &choice);
 
    
    // To enter the duration of the exercise
    printf("Enter the duration of the exercise (in min.): ");
    scanf("%d", &duration);

    // ToCode: to enter the selected exercise and total calcories burned in the health data
    if (choice != 7) { 
	//Exit select -> while loop close, Go back to beginning
	
		// food_name: diet_list -> health data copy
		//Since arrays start at 0, choice - 1 becomes the array index
        strcpy(health_data->exercises[health_data->exercise_count].exercise_name, exercise_list[choice - 1].exercise_name);
        // calories_intake: diet_list -> health data copy
        //To use in the function within cal_healthdata.c, the calculated value with duration -> health_data
        health_data->exercises[health_data->exercise_count].calories_burned_per_minute = exercise_list[choice - 1].calories_burned_per_minute * duration;
			
        // diet_count count(health_data order)
        health_data->exercise_count++;
        // calculate and update total calories
        health_data->total_calories_burned += (exercise_list[choice - 1].calories_burned_per_minute * duration);
	}


}
