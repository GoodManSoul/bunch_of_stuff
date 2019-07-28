#include <bits/stdc++.h> 
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <thread>

using namespace std;

const int STACK_SIZE = 4;
const int PERFORMED_OPERATION_STACK = 4;

enum control_mode{MANUAL, STACK};
enum operation{ADD, SUB, MULT, DIV};

struct stack_machine{
	stack_machine(){
		reg_A = 0.0f;
		reg_B = 0.0f;
		reg_C = 0.0f;
		reg_D = 0.0f;
		run_flag = false;
		stack_pointer = -1;
		control_stack_pointer = -1;
		performed_operation_buffer = "none";

		for(int i = 0; i < STACK_SIZE; i++)
			stack[i] = 0.0f;
		for(int i = 0; i < PERFORMED_OPERATION_STACK; i++)
			operation_stack[i] = "none";
	}
//////////////////////////////////////////////////////////////////////

	void run(){

	}

	void stop(){
		run_flag = false;
		printf("[!]The machine had been stoped[!]\n");
	}

	void run_by_stack(){
		run_flag = true;
		while(run_flag){
			printf("machine is running...\n");
			run_flag = perform_operation();
			sleep(2);
		}
		printf("machine has stop running!\n");
	}

	bool perform_operation(operation oper){
		if(stack_pointer < 0){
			printf("\nOpetarion can\'t be performed. The stack is empty!\n");
			return false;
		}else if(stack_pointer < 1){
					printf("\nOpetarion can\'t be performed. Not enough operands!\n");
					return false;
				}	
		switch(oper){
			case ADD:
				push_on_top(remove_from_top(MANUAL) + remove_from_top(MANUAL));
			break;

			case SUB: 
				push_on_top(remove_from_top(MANUAL) - remove_from_top(MANUAL));
			break;

			case MULT: 
				push_on_top(remove_from_top(MANUAL) * remove_from_top(MANUAL));
			break;

			case DIV:	
				push_on_top(remove_from_top(MANUAL) / remove_from_top(MANUAL));
			break;
		}
	return true;
}

	bool perform_operation(){
		if(control_stack_pointer < 0){
			printf("\nOpetarion can\'t be performed. The stack is empty!\n");
			return false;
		}else
			remove_from_top(STACK); //performed_operation_buffer will be update
		

		if(performed_operation_buffer == "ADD"){
				if(stack_pointer < 1){
					printf("\nOpetarion can\'t be performed. Not enough operands!\n");
					return false;
				}	
			push_on_top(remove_from_top(MANUAL) + remove_from_top(MANUAL));
			return true;
		}
		if(performed_operation_buffer == "SUB"){
				if(stack_pointer < 1){
					printf("\nOpetarion can\'t be performed. Not enough operands!\n");
					return false;
				}	
			push_on_top(remove_from_top(MANUAL) - remove_from_top(MANUAL));
			return true;
		}
		if(performed_operation_buffer == "MULT"){
				if(stack_pointer < 1){
					printf("\nOpetarion can\'t be performed. Not enough operands!\n");
					return false;
				}	
			push_on_top(remove_from_top(MANUAL) * remove_from_top(MANUAL));
			return true;
		}
		if(performed_operation_buffer == "DIV"){
				if(stack_pointer < 1){
					printf("\nOpetarion can\'t be performed. Not enough operands!\n");
					return false;
				}	
			push_on_top(remove_from_top(MANUAL) / remove_from_top(MANUAL));
			return true;
		}		
		return true;
	}

/* 	bool run_by_file(){
		FILE* read_file;
		read_file = fopen("oper.txt", "r");
		if(read_file == NULL){
			printf("\nFile cannot be found\n");
			return false;
		}


		FILE * fp;
		char * line = NULL;
		size_t len = 0;
		ssize_t read;

		fp = fopen("oper.txt", "r");
		if (fp == NULL)
			exit(EXIT_FAILURE);



		while ((read = getline(&line, &len, fp)) != -1) {
			operation_stack[0] = line;
			cout << operation_stack[0] << endl;
		}
		cout << operation_stack[0] << endl;

		fclose(fp);
		if (line)
			free(line);
	return true;
} */

	bool push_on_top(double value){
		if(stack_pointer == STACK_SIZE - 1){
			printf("\n\tThe stack is full already\n");
			return false;
		}
		stack_pointer++;
		stack[stack_pointer] = value;
		return true;
	}

	bool push_on_top(string perform_operation){
		if(control_stack_pointer == PERFORMED_OPERATION_STACK - 1){
				printf("\n\tThe control stack is full already\n");
				return false;
			}
		control_stack_pointer++;
		operation_stack[control_stack_pointer] = perform_operation;	
		return true;
	}

	double remove_from_top(control_mode mode){
		if(mode == MANUAL){
			if(stack_pointer < 0){
				printf("\nCannot remove from the stack. The stack is empty!\n");
				return -100; //magic number
			}
			double temp_value = stack[stack_pointer];
			stack[stack_pointer] = 0.0f;
			stack_pointer--;
			return temp_value;
		}else{
			if(control_stack_pointer < 0){
				printf("\nCannot remove from the control stack. The stack is empty!\n");
				return -100; //magic number
			}
			performed_operation_buffer = operation_stack[control_stack_pointer];
			operation_stack[control_stack_pointer] = "none";
			control_stack_pointer--;
			return 0;
		}
	}

	void print_stack() {
			if (stack_pointer < 0)
				printf("\n\tThe stack is empty\n");
			else 
				for (int i = STACK_SIZE - 1; i >= 0; i--)
					cout << "[" << i << "] " << stack[i] << " [" << i << "]" << endl;
	}

	void print_control_stack(){
		if (control_stack_pointer < 0)
				printf("\n\tThe control stack is empty\n");
			else 
				for (int i = PERFORMED_OPERATION_STACK - 1; i >= 0; i--)
					cout << "[" << i << "] " << operation_stack[i] << " [" << i << "]" << endl;
	}

//////////////////////////////////////////////////////////////////////
	int stack_pointer;
	int control_stack_pointer;
	double stack[STACK_SIZE];
	double reg_A, reg_B, reg_C, reg_D;
	string operation_stack[PERFORMED_OPERATION_STACK];
	string performed_operation_buffer;
	bool run_flag;
};

int main() {

	system("clear");
	printf("\n\t[!]START[!]\n");

	stack_machine* sm = new stack_machine();

	
	
	

	sm->push_on_top(100.0f);
	sm->push_on_top(400.0f);
	sm->push_on_top(1000.0f);
	sm->push_on_top(500.0f);
	
	sm->push_on_top("ADD");
	sm->push_on_top("ADD");
	sm->push_on_top("ADD");
	sm->push_on_top("ADD");

	sm->print_stack();
	printf("\n");
	sm->print_control_stack();

	thread th(&stack_machine::run_by_stack, sm);
	
	th.join();


	

	free(sm);
	printf("\n\t[!]END[!]\n");
	return 0;
}
