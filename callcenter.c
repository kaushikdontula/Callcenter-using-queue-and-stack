/*
 * This file is simulating a callcenter using the data structures that we created in the previous parts of the program
 *
 * Name: Kaushik Dontula
 * Email: Dontulak@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "stack.h"

struct call{
	int ID;
	int stack_size;
	int queue_size; 

	struct stack* stack;
	struct queue* queue;
};

struct data{
	int ID;
	char reason[100];
	char name[100];
};


/******************************************************************* 
** Function: display_data
** Description: This function displays the call data
** Parameters: struct data* data
** Pre-conditions: a call struct needs to be created
** Post-conditions: prints out the call data
*******************************************************************/
void display_data(struct data* data){
 
	if(data != NULL){
		printf(" \n ID: %d \n Name: %s\n Reason: %s \n \n", data->ID, data->name, data->reason);
	}
	
}


/******************************************************************* 
** Function: clear_memory
** Description: This function clears the memory of the callcenter
** Parameters: struct call* callcenter
** Pre-conditions: callcenter has to be created
** Post-conditions: no memory leaks
*******************************************************************/
void clear_memory(struct call* callcenter){

	//clears memory inside each queue variable using for loop
	for(int i=0; i<callcenter->queue_size; i++){
		struct data* temp = queue_dequeue(callcenter->queue);
		free(temp);
	}

	//clears memory inside each stack variable using for loop
	for(int i=0; i<callcenter->stack_size; i++){
		struct data* temp = stack_pop(callcenter->stack);
		free(temp);
	}

	//clearing the stack queue and callcenter themselves
	stack_free(callcenter->stack);
	queue_free(callcenter->queue);
	free(callcenter);

	return;
}


/******************************************************************* 
** Function: new_call
** Description: This function stores the infromation of a new call
** Parameters: struct call* callcenter
** Pre-conditions: the callcenter struct should be created
** Post-conditions: creates a new call data struct to be in the callcenter
*******************************************************************/
void new_call(struct call* callcenter){

	char temp[100];

	//adding one to the size of the queue
	callcenter->queue_size++;

	//creating a new call struct using dynamic memory
	struct data* new_call = malloc(sizeof(struct data));

	//getting user input for call information
	printf("Please enter the name of the caller : ");
	scanf("%c",&temp); // temp statement to clear buffer
	scanf("%[^\n]", new_call->name);
	//scanf("%s", new_call->name);

	printf("Please enter the reason for the call : ");
	scanf("%c",&temp); // temp statement to clear buffer
	scanf("%[^\n]", new_call->reason);
	//scanf("%s", new_call->reason);
	
	//setting the ID 
	callcenter->ID = callcenter->ID+1;
	new_call->ID = callcenter->ID;

	//adding the data to the queue of calls
	queue_enqueue(callcenter->queue,new_call);

}



/******************************************************************* 
** Function: answer_call
** Description: This function answers a call from the queue and adds it to the stack
** Parameters: struct call* callcenter 
** Pre-conditions: callcenter has to be created
** Post-conditions: adds the call data to the stack and removes it from the queue
*******************************************************************/
void answer_call(struct call* callcenter){

	//if there is no calls in the queue
	if(queue_isempty(callcenter->queue) == 1){
		printf("The queue is currently empty, no calls need to be answered \n");
	}

	//if the queue has calls
	else{
			//get the first call from the queue and store it in temp
			struct data* temp = queue_dequeue(callcenter->queue);
			callcenter->stack_size++;

			//add that call variable to the stack
			stack_push(callcenter->stack, temp);
			callcenter->queue_size--;
			

			printf("The following call has been added to the stack \n");
			display_data(temp);

	}
}


/******************************************************************* 
** Function: current_stack
** Description: This function gives information on the current stack
** Parameters: struct call* callcenter
** Pre-conditions: callcenter struct has to be created
** Post-conditions: displays data of stack
*******************************************************************/
void current_stack(struct call* callcenter){

	printf("Number of calls answered: %d \n", callcenter->stack_size);

	//if there are answered calls then output the data of th elast answered call
	if (callcenter->stack_size != 0){
		struct data* temp = stack_top(callcenter->stack);
		printf("\n The last call answered: \n");
		display_data(temp);
	}
	return;
}



/******************************************************************* 
** Function: current_queue
** Description: This function provides details of the current queue
** Parameters: struct call* callcenter
** Pre-conditions: the callcenter needs to be created
** Post-conditions: prints details of the current queue
*******************************************************************/
void current_queue(struct call* callcenter){

	printf("Number of calls need to be answered: %d \n", callcenter->queue_size);

	//if there are calls in the queue output the data of the next call in the queue
	if (callcenter->queue_size != 0){
		struct data* temp = queue_front(callcenter->queue);
		printf(" \n The next call in the queue is: \n ");
		display_data(temp);
	}
	return;
}




/******************************************************************* 
** Function: menu
** Description: This function gets the user input for menu
** Parameters: none 
** Pre-conditions: structs need to be created
** Post-conditions: creates the callcenter
*******************************************************************/
void menu(){

	//creating a call struct variable and initializing it
	struct call* callcenter = malloc(sizeof(struct call));
	callcenter->ID = 0;
	callcenter->queue_size = 0;
	callcenter->stack_size = 0;
	callcenter->stack = stack_create();
	callcenter->queue = queue_create();

	int option = 0;

	do{
		//get user input for option of call center
		printf(" \n 1. Recieve new call: \n 2. Answer a call \n 3. Current state of stack - answered calls \n 4. Current state of queue - calls to be answered\n 5. Quit \n");
		scanf("%d", &option);

		switch(option){
			case 1: 
				new_call(callcenter);
				break;

			case 2: 
				answer_call(callcenter);
				break;


			case 3: 
				current_stack(callcenter);
				break;

			case 4: 
				current_queue(callcenter);
				break;

			default:
				clear_memory(callcenter);
				printf("Thank you for running this callcenter, bye. \n");
				break;
		}
	}while(option != 5);
}




int main(int argc, char const *argv[]) {


	menu();

	return 0;
}
