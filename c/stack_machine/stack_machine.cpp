#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <thread>

using namespace std;

const int STACK_SIZE = 4;


enum operation{ADD, SUB, MULT, DIV};

struct stack_machine{
	stack_machine(){
		reg_A = 0.0f;
		reg_B = 0.0f;
		reg_C = 0.0f;
		reg_D = 0.0f;
		stack_pointer = -1;
		performed_operation = "none";
		for(int i = 0; i < STACK_SIZE; i++)
			stack[i] = 0.0f;
	}
//////////////////////////////////////////////////////////////////////

	bool perform_operation(operation oper){
		if(stack_pointer < 0){
			printf("\nOpetarion can\'t be performed. The stack is empty!\n");
			return false;
		}

		switch(oper){
			case ADD:
				if(stack_pointer < 1){
					printf("\nOpetarion can\'t be performed. Not enough operands!\n");
					return false;
				}	
				push_on_top(remove_from_top() + remove_from_top());
			break;

			case SUB: 
				if(stack_pointer < 1){
						printf("\nOpetarion can\'t be performed. Not enough operands!\n");
						return false;
					}	
					push_on_top(remove_from_top() - remove_from_top());
			break;

			case MULT: 
				if(stack_pointer < 1){
						printf("\nOpetarion can\'t be performed. Not enough operands!\n");
						return false;
					}	
					push_on_top(remove_from_top() * remove_from_top());
			break;

			case DIV: 
				if(stack_pointer < 1){
						printf("\nOpetarion can\'t be performed. Not enough operands!\n");
						return false;
					}	
					push_on_top(remove_from_top() / remove_from_top());
			break;
		}
		return true;
	}

	bool push_on_top(double value){
		if(stack_pointer == STACK_SIZE - 1){
			printf("\n\tThe stack is full already\n");
			return false;
		}
		stack_pointer++;
		stack[stack_pointer] = value;
		return true;
	}

	double remove_from_top(){
		if(stack_pointer < 0){
			printf("\nCannot remove from the stack. The stack is empty!\n");
			return -100; //magic number
		}
		double temp_value = stack[stack_pointer];
		stack[stack_pointer] = 0.0f;
		stack_pointer--;
		return temp_value;
	}

	void print_stack() {
			if (stack_pointer < 0)
				printf("\n\tThe stack is empty\n");
			else 
				for (int i = STACK_SIZE - 1; i >= 0; i--)
					cout << "[" << i << "] " << stack[i] << " [" << i << "]" << endl;
	}

//////////////////////////////////////////////////////////////////////
	int stack_pointer;
	double stack[STACK_SIZE];
	double reg_A, reg_B, reg_C, reg_D;
	string performed_operation;
	//operation perf_oper;
};

int main() {

	system("clear");
	printf("\n\t[!]START[!]\n");

	stack_machine sm;

	sm.push_on_top(10.0);
	sm.push_on_top(5.0);
	sm.push_on_top(300.0);

	sm.perform_operation(DIV);
	//sm.perform_operation(ADD);

	sm.print_stack();
	

	printf("\n\t[!]END[!]\n");
	return 0;
}
