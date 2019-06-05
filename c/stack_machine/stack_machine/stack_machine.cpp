#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define _STACK_SIZE 5

enum op_code{ADD = 0, SUB, MULT, DIV};

struct c_stack {
///////////////////////////////////////////////////
	c_stack() {
		stack_pointer	= 0;
		A_reg			= 0;
		B_reg			= 0;
		R_reg			= 0;
	}
///////////////////////////////////////////////////
	int_fast8_t rm_from_stack() {
		if (!stack_pointer == 0) 
			return stack[stack_pointer--];
		else
			return -127; //magic number 
	}

	int_fast8_t add_to_stack(int_fast8_t source_reg) {
		if (stack_pointer < _STACK_SIZE) {
			stack[stack_pointer++] = source_reg;
		}
		return -127; //magic number 
	}

	bool exec(op_code operand){
		
		return true;
	}

	int_fast8_t stack[_STACK_SIZE] = { 0 };
	uint_fast8_t stack_pointer; //to control stack fulfilment

	int_fast8_t A_reg, B_reg, R_reg;
};

int main(int argc, char* argv[])
{	
	printf("\n\t\tSTART OF APPLICATION\n");
	c_stack demo;
	
	printf("Stack init: %d", demo.stack[0]);
	

	printf("\n\t\tEND OF APPLICATION\n");

	return EXIT_SUCCESS;
}
