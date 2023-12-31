/********* definitions.c ********

	Student Name 	= Sabeen Rafiq
	Student Number	= 101258923
*/

// Include statements
#include <stdio.h>	//scanf, printf
#include <stdlib.h> //EXIT_SUCCESS

#include <string.h>	 //Strings (strcpy)
#include <stdbool.h> //Boolean (_Bool)
#include <math.h>	 //round()

// Include header files
#include "a1_data_structures.h"
#include "a1_functions.h"

// Define hardcoded values
#define HOURS 40.0
#define SALARY 25.0

// Calculate number of employees needed for the project based on cost and time
void number_of_employees(milestone_t *project_details)
{
	// Initialize Variables
	int num_employees_i;
	float num_employees_f;
	float fulltime_salary;

	// Calculate full time salary
	fulltime_salary = (float)project_details->time * HOURS * SALARY;

	// Calculate number of employees in a float then round and store as an integer
	num_employees_f = project_details->cost / fulltime_salary;
	num_employees_f = round(num_employees_f);
	num_employees_i = (int)num_employees_f;

	// Store the number of employees back in project details
	project_details->num_employees = num_employees_i;
}

// Initialize milestones with names and planned budget
milestone_t init_milestone(char stage_name[], float assigned_budget)
{
	// Create milestones structure (will be stored as one element in an array milestones[] in main.c)
	milestone_t indiv_milestones;

	// Store the time, cost (1/5) of the budget, completion status and name in the milestone
	indiv_milestones.cost = ((float)(assigned_budget / 5));
	indiv_milestones.time = 0;
	indiv_milestones.num_employees = 0;
	indiv_milestones.completed = 0;
	strcpy(indiv_milestones.name, stage_name);

	// Return the milestone
	return indiv_milestones;
}

// Get unsigned short integer user input. The value must be positive.
// If negative value entered ask user to re-enter a positive value
unsigned short int get_input_usi(void)
{
	// Initialize Variables
	int user_input;

	// Get user input
	scanf("%d", &user_input);

	// Print an error message and take in input again if value is negative
	while (user_input < 0)
	{
		printf("\n------------------------------------\n");
		printf("The value you entered is wrong\n");
		printf("Enter a positive value: ");
		scanf("%d", &user_input);
	}

	// Return user input
	return user_input;
}

// Get float user input. The value must be positive.
// If negative value entered ask user to re-enter a positive value
float get_input_f(void)
{
	// Initialize Variables
	float user_input;

	// Get user input
	scanf("%f", &user_input);

	// Print an error message and take in input again if value is negative
	while (user_input < 0)
	{
		printf("\n------------------------------------\n");
		printf("The value you entered is wrong\n");
		printf("Enter a positive value: ");
		scanf("%f", &user_input);
	}

	// Return user input
	return user_input;
}

// Print menu with a list of milestones/options for the user to choose from
void print_menu(void)
{
	// Print out menu
	printf("Which milestone do you want to update? (0 to exit)\n");
	printf("1. Technical Requirements\n");
	printf("2. System Design\n");
	printf("3. Software Development\n");
	printf("4. Testing\n");
	printf("5. Product Release\n");
	printf("\nYour choice is: ");
}

// Print out current stats of each milestone/project
// (i.e, print all members of the milestone_t struct)
void print_stats(milestone_t details)
{
	// Header
	printf("\n--------- Milestone Stats ----------");
	printf("\nBelow is the \"%s\" current stats:", details.name);
	printf("\n------------------------------------\n");

	/// Print stats
	printf("\nActual time: %0.2f weeks", details.time);
	printf("\nActual number of employees: %d", details.num_employees);
	printf("\nActual cost: $%0.2f", details.cost);

	if (details.completed == 1)
		printf("\nCompleted: Yes\n\n");
	else
		printf("\nCompleted: No\n\n");
}

// Update the stats of the milestones (not the project).
// (i.e., Asks the user to update time, number of employees and completed.
// Cost is calculated based on the input data)
void update_stats(milestone_t milestone_array[], int milestone_num)
{
	// Initialize Variables
	char completion;

	// Header
	printf("-------------Update Stats-----------\n");

	// Ask for actual time and cost then take in input
	printf("\nEnter the milestone's actual time: ");
	scanf("%f", &milestone_array[milestone_num].time);
	printf("Enter the milestone's number of employees: ");
	scanf("%d", &milestone_array[milestone_num].num_employees);

	// Update milestone cost
	milestone_array[milestone_num].cost = (float)(milestone_array[milestone_num].num_employees) * (float)(milestone_array[milestone_num].time) * HOURS * SALARY;

	// Ask if milestone is complete and update completion accordingly
	printf("Is this milestone complete?: (Y/N) ");
	scanf(" %c", &completion);

	if (completion == 'Y')
	{
		milestone_array[milestone_num].completed = 1;
	}
	else
	{
		milestone_array[milestone_num].completed = 0;
	}

	printf("Status Updated!\n\n");
}

// Check if all milestones are completed or not. If completed, updated the project's details to completed.
void check_project_completion(milestone_t milestone_array[], int num_milestones)
{
	// For loop between 1 to the number of milestones
	for (int i = 1; i <= (num_milestones-1); i++)
	{
		// If milestones are complete update the element 0 if milestone array to 1 
		// else if any are not complete update it to 0
		if (milestone_array[i].completed == 1)
		{
			milestone_array[0].completed = 1;
		}
		else
		{
			milestone_array[0].completed = 0;
			break;
		}
	}
}

// Calculates final cost of all milestones
float finalcost_milestone(milestone_t milestone_array[])
{
	// Initialize Variables
	float sum;
	sum = 0.0;

	// For 1 to 5 add the cost values from each array to sum
	for (int i = 1; i <= 5; i++)
	{
		sum += (float) (milestone_array[i].cost);
	}
	// Return the sum (total cost) value
	return sum;
}

// Prints out final project performance
void final_project_performace(float final_cost, float budget)
{
	printf("\n------------------------------------\n");
	printf("-----Final Project Performance------\n");
	printf("------------------------------------\n\n");

	// If the cost is greater than the budget..
	if (final_cost > budget)
	{
		printf("The project's budget is above budget!\n");
	}
	// If the cost is less than the budget
	else
	{
		printf("The project's budget is below budget!\n");
	}

	// Print out planned and actual costs
	printf("Planned Budget: %.2f\n", budget);
	printf("Actual Cost: %.2f\n", final_cost);

	// Quit program
	printf("\n------------------------------------\n");
	printf("--The Program will quit now! Goodbye!--\n");
	printf("------------------------------------\n\n");
}
