/********* main.c ********

	Student Name 	= Sabeen Rafiq
	Student Number	= 101258923
*/

/*
To run code in Terminal:
gcc -g main.c a1_functions.c -o A1
./A1
*/

// Include statements
#include <stdio.h>	//scanf, printf
#include <stdlib.h> //EXIT_SUCCESS

#include <string.h>	 //Strings (strcpy)
#include <stdbool.h> //Boolean (_Bool)

// Include header files
#include "a1_data_structures.h"
#include "a1_functions.h"

// Define hardcoded values
#define SIZE 6

int main()
{	
	
	// Initialize Variables
	unsigned short int milestone_choice, duration;
	float budget;
	_Bool menu_continue;
	char completion, continue_YN;

	float final_cost;

	// Welcome Statement
	printf("\n------------------------------------\n");
	printf("---Welcome to ABC Project Tracker---\n");
	printf("------------------------------------\n\n");
	printf("\n");

	// Enter Project's Budget & Duration
	printf("Enter total project's budget: ");
	budget = get_input_f();
	printf("Enter total project's duration in weeks: ");
	duration = get_input_usi();

	// Initialize array to store all milestone info
	milestone_t milestones[SIZE];

	// Update Info for Milestone 0 (Planned Details)
	milestones[0].cost = budget;
	milestones[0].time = duration;
	char milestone_name[] = "Planned Details";
	strcpy(milestones[0].name, milestone_name);

	// Calculate Number of Employees Needed
	number_of_employees(&milestones[0]);
	printf("The planned number of employees needed is: %d\n", milestones[0].num_employees);
	printf("\n------------------------------------\n\n");

	// Initialize all 5 Milestones
	milestones[1] = init_milestone("Technical Requirements", budget);
	milestones[2] = init_milestone("System Design", budget);
	milestones[3] = init_milestone("Software Development", budget);
	milestones[4] = init_milestone("Testing", budget);
	milestones[5] = init_milestone("Product release", budget);

	menu_continue = 1;

	// While loop to reloop the following code while menu_continue = 1
	while (menu_continue == 1)
	{
		// Print menu
		print_menu();

		// Get input from user for next milestone to update
		milestone_choice = get_input_usi();

		// While value is not between 0 and 5 print an error message
		while (milestone_choice < 0 || milestone_choice > 5)
		{
			printf("\n------------------------------------\n");
			printf("The value you entered is wrong\n");
			printf("Enter a value between 0 and 5: ");
			milestone_choice = get_input_usi();
		}

		// When user choice is 0:
		if (milestone_choice == 0)
		{
			printf("\n------------------------------------\n");
			printf("---------Project Performance---------\n");
			printf("------------------------------------\n\n");
			
			// Print stats
			print_stats(milestones[0]);

			// Check if all milestones are complete
			check_project_completion(milestones, 6);

			// If milestones are complete...
			if (milestones[0].completed == 1)
			{
				// Calculate final cost
				final_cost = finalcost_milestone(milestones);

				// Ouput final project performance
				final_project_performace(final_cost, budget);

				menu_continue = 0;
			}
			// If milestones are not complete...
			else
			{
				
				// Ask if the user wants to finish the other milestones
				printf("\nDo you want to finish the remaining milestones? (Y/N) ");
				scanf(" %c", &continue_YN);
				printf("\n");

				// If yes then reloop
				if (continue_YN == 'Y')
				{
					menu_continue = 1;
				}
				// If not then...
				else
				{
					// Calculate final cost
					final_cost = finalcost_milestone(milestones);

					// Ouput final project performance
					final_project_performace(final_cost, budget);
					
					menu_continue = 0;
				}
			}
		}

		// When user choice is between 1 to 5:
		else
		{
			// Print Stats
			print_stats(milestones[milestone_choice]);

			// Ask if milestone is complete
			completion = milestones[milestone_choice].completed;

			if (completion == 0)
			{
				// Ask user to update stats
				update_stats(milestones, milestone_choice);
				print_stats(milestones[milestone_choice]);
			}
			else
			{
				// Milestone cannot be updated
				printf("------------------------------------\n");
				printf("%s milestone is completed, \nit cannot be updated\n", milestones[milestone_choice].name);
				printf("------------------------------------\n\n");
			}

			// Print stats and reloop
			menu_continue = 1;
		}
	}
	return EXIT_SUCCESS;
}