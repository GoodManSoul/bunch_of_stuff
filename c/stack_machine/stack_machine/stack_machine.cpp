#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define _STACK_SIZE 5
#define _STACK_SUCCESS true
#define _STACK_FAILURE false
#define _CLEAR_STACK 0

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
	bool rm_from_stack(int_fast8_t& dest_reg) {
		if (!stack_pointer == 0) {
			//printf("\n\t IN_REMOVE_STACK_PTR: %d \n", stack_pointer);
			stack_pointer--;
			dest_reg = stack[stack_pointer];
			stack[stack_pointer] = _CLEAR_STACK;
			return _STACK_SUCCESS;
		}		
		return _STACK_FAILURE;
	}

	bool add_to_stack(int_fast8_t& source_reg) {
		//printf("\tSTACK_POINTER: %d\n", stack_pointer);
		if (stack_pointer < _STACK_SIZE) {
			stack[stack_pointer] = source_reg;
			stack_pointer++;
			return _STACK_SUCCESS;
		}else {
			printf("\t[!]_stack_overflow_[!]\n");
			return _STACK_FAILURE;
		}
	}

	bool exec(op_code operand){
		switch (operand){
		case ADD:
			rm_from_stack(A_reg);
			rm_from_stack(B_reg);

			add_to_stack(R_reg = A_reg + B_reg);
			break;
		case SUB:
			rm_from_stack(A_reg);
			rm_from_stack(B_reg);

			add_to_stack(R_reg = A_reg - B_reg);
			break;
		case MULT:
			rm_from_stack(A_reg);
			rm_from_stack(B_reg);

			add_to_stack(R_reg = A_reg * B_reg); // type overflow !!!
			break;
		case DIV:
			/*rm_from_stack(A_reg);
			rm_from_stack(B_reg);

			add_to_stack(R_reg = A_reg + B_reg);*/ // distinct type?
			break;
		default:
			break;
		}

		
		return true;
	}

	void print_stack() {
		for (int i = _STACK_SIZE - 1; i >= 0; i--)
			printf("\tStack[%d]: %d\n",i ,stack[i]);
	}

	int_fast8_t stack[_STACK_SIZE] = { 0 };
	uint_fast8_t stack_pointer; //to control stack fulfilment

	int_fast8_t A_reg, B_reg, R_reg;
};

int main(int argc, char* argv[])
{	
	printf("\n\t\tSTART OF APPLICATION\n");
	c_stack demo;
	demo.A_reg = 26;
	demo.B_reg = 10;
	demo.add_to_stack(demo.A_reg);
	demo.add_to_stack(demo.B_reg);

	printf("\tREG R: %d\n", demo.exec(MULT));
	
	demo.print_stack();
	

	printf("\n\t\tEND OF APPLICATION\n");

	return EXIT_SUCCESS;
}
