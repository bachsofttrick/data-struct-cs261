#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "stack.h"

#define STR_LENGTH 100

// Globally define call ID
int callID = 1;

/*
 * Define your call struct here.
 */
struct call {
	int id;
	char name[STR_LENGTH];
	char reason[STR_LENGTH];
};

/* Display options and get option from user input */
int display_options() {
	char* displayText = "1. Receive a new call\r\n"
						"2. Answer a call\r\n"
						"3. Current state of the stack – answered calls\r\n"
						"4. Current state of the queue – calls to be answered\r\n"
						"5. Quit\r\n"
						"Choose an option: ";
	printf("%s", displayText);
	int option;
	scanf("%d", &option);
	return option;
}

/* Take user inputs of caller’s name and call reason to
 * create a call object, and add it to the queue.
 * Params:
 *   callQueue - the call queue to add new call
 */
void receive_new_call(struct queue* callQueue) {
	struct call* newCall = malloc(sizeof(struct call));
	newCall->id = callID++;
	printf("%s", "\r\nEnter caller’s name: ");
	scanf("%s", newCall->name);
	printf("%s", "Enter call reason: ");
	scanf("%s", newCall->reason);
	queue_enqueue(callQueue, newCall);
	printf("%s", "\r\nThe call has been successfully added to the queue!\r\n\r\n");
}

/* Remove the first call from the queue and add it to the
 * stack of answered calls. 
 * Display an error message if the queue is empty.
 * Params:
 *   callQueue - the call queue to remove a call
 *   callStack - the call stack to add that call
 */
void answer_call(struct queue* callQueue, struct stack* callStack) {
	if (queue_isempty(callQueue)) {
		printf("%s", "\r\nQueue is empty. Wait for a call.\r\n\r\n");
		return;
	}
	struct call* pulledCall = queue_dequeue(callQueue);
	stack_push(callStack, pulledCall);
	pulledCall = stack_pop(callStack);
	printf("%s", "\r\nThe following call has been answered and added to the stack!\r\n");
	printf("%s %d %s", "Call ID: ", pulledCall->id,"\r\n");
	printf("%s %s %s", "Caller's name: ", pulledCall->name,"\r\n");
	printf("%s %s %s", "Call reason: ", pulledCall->reason,"\r\n\r\n");
}

int main(int argc, char const *argv[]) {
	int option = 0;
	struct stack* callStack = stack_create();
	struct queue* callQueue = queue_create();
	while (1) {
		option = display_options();
		switch (option)
		{
		case 1:
			receive_new_call(callQueue);
			break;
		case 2:
			answer_call(callQueue, callStack);
			break;
		case 3:
			printf("%s", "\r\nNot implemented yet.\r\n\r\n");
			// display_stack_current_state(callStack);
			break;
		case 4:
			printf("%s", "\r\nNot implemented yet.\r\n\r\n");
			// display_queue_current_state(callQueue);
			break;
		case 5:
			printf("%s", "\r\nHave a nice day.\r\n\r\n");
			return 0;
		}
	}
}
