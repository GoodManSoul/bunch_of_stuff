#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <pthread.h>

using namespace std;

const int STACK_SIZE = 4;


struct stack_machine {

	stack_machine() {
		reg_A = 0;
		reg_B = 0;
		reg_C = 0;
		reg_D = 0;
		stack_pointer = -1;
		running_condition = false;
		word = "0000 0000 0000 0000"; //if opcode == 0000 -> the word can be skipped      
		for (int i = 0; i < STACK_SIZE; i++)
			stack[i] = word;
	}
	/////////////////////////////////////////////////////////////////////////////////////

	void run() {
		/* while(true){
			cout << "Running ..." << endl;
			Sleep(200);
		} */
	}

	void stop() {

	}

	bool push_on_top(string obtained_word) {
		if (stack_pointer == STACK_SIZE) {
			printf("\n\tThe stack is full\n");
			return false;
		}
		stack_pointer++;
		stack[stack_pointer] = obtained_word;
		return true;
	}

	void fetch_word() {

	}

	void print_stack() {
		if (stack_pointer < 0) {
			printf("\n\tThe stack is empty\n");
		}
		else {
			cout << '\n';
			for (int i = 0; i < STACK_SIZE; i++)
				cout << "[" << i << "] " << stack[i] << " [" << i << "]" << endl;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////
	bool running_condition;
	string word;
	string stack[STACK_SIZE];
	int stack_pointer;
	double reg_A, reg_B, reg_C, reg_D;
};

void* generate_stack_machine_word_set(void* arg) {
	/* FILE* word_set;
	word_set = fopen("word_set.sme", "w+");

	for (int i = 0; i < STACK_SIZE; i++)
		fprintf(word_set, words_array[i]);


	fclose(word_set);
	return true; */

	while (true) {
		cout << "Running ..." << endl;
		Sleep(200);
	}
}

int main() {

	system("cls");
	printf("\n\t[!]START[!]\n");



	// generate_stack_machine_word_set();

	stack_machine sm;

	sm.push_on_top("1111 1111 1111 1111");
	sm.push_on_top("1111 1111 1111 1111");
	sm.push_on_top("1111 1111 1111 1111");
	sm.print_stack();

	pthread_t thread_id;


	pthread_create(&thread_id, NULL, generate_stack_machine_word_set, NULL);
	pthread_join(thread_id, NULL);
	

	printf("\n\t[!]END[!]\n");
	return 0;
}
