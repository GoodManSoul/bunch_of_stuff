#include <termios.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "get_c.h"

using namespace std;

const int GAME_FIELD_WIDTH = 24;
const int GAME_FIELD_HEIGHT = 24;
const int TETRIS_BLOCK_COUNT = 7;

const char GAME_FIELD_BORDER = '#';

enum TETRIS_BLOCK{I_BLOCK = 0, J_BLOCK, L_BLOCK, O_BLOCK, S_BLOCK, T_BLOCK, Z_BLOCK};

class console_tetris_game{
    public:
        console_tetris_game(){ 
            allocate_array(game_field);
            allocate_array(game_field_buffer);
           /*  if(!allocate_array(game_field) && !allocate_array(game_field_buffer))
                printf("Allocation error!\n");
            else
                printf("Allocation success!\n"); */
              

        }

        ~console_tetris_game(){
           
            // for(int i = 0; i < GAME_FIELD_HEIGHT; i++){
            //     free(game_field[i]);
            //    // free(game_field_buffer[i]);
            // }
            // for(int i = 0; i < GAME_FIELD_HEIGHT; i++){
            //     //free(game_field[i]);
            //     free(game_field_buffer[i]);
            // }
            // free(game_field);
            // free(game_field_buffer);
        }
    protected:
        bool allocate_array(char** requested_array){
            requested_array = (char**)malloc(sizeof(char*) * GAME_FIELD_HEIGHT);
            for (int i = 0; i < GAME_FIELD_HEIGHT; i++)
                requested_array[i] = (char*)malloc(sizeof(char) * GAME_FIELD_WIDTH);
            
            if(requested_array == NULL)
                return false;            
            return true;        
        }

    public:
        char** game_field;
        char** game_field_buffer;
};


int main(){

    printf("START\n");

    console_tetris_game ct;

    printf("END\n");

    return 0;
}