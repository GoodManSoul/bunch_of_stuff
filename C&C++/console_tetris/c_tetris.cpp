#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

const int GAME_FIELD_WIDTH = 24;
const int GAME_FIELD_HEIGHT = 24;
const int TETRIS_BLOCK_BASE_SIZE = 4;

const char GAME_FIELD_BORDER = '#';
const char BLOCK_STYLE = '@';

enum TETRIS_BLOCK{I_BLOCK, J_BLOCK, L_BLOCK, O_BLOCK, S_BLOCK, T_BLOCK, Z_BLOCK};

class tetris_block{
    public: 
    tetris_block(TETRIS_BLOCK requested_block){
        
        //creation of each type of block
        switch(requested_block){
            case I_BLOCK:
                b_height = 4;
                b_width = 1;
                create_block_array();
                fill_array_with_void();
                t_block[0][0] = BLOCK_STYLE;
                t_block[1][0] = BLOCK_STYLE;
                t_block[2][0] = BLOCK_STYLE;
                t_block[3][0] = BLOCK_STYLE;
            break;

            case J_BLOCK:
                b_height = 3;
                b_width = 2;     
                create_block_array();
                fill_array_with_void();
                t_block[0][1] = BLOCK_STYLE;
                t_block[1][1] = BLOCK_STYLE;
                t_block[2][1] = BLOCK_STYLE;
                t_block[2][0] = BLOCK_STYLE;
            break;

            case L_BLOCK:
                b_height = 3;
                b_width = 2;     
                create_block_array();
                fill_array_with_void();
                t_block[0][0] = BLOCK_STYLE;
                t_block[1][0] = BLOCK_STYLE;
                t_block[2][0] = BLOCK_STYLE;
                t_block[2][1] = BLOCK_STYLE;
            break;

            case O_BLOCK:
                b_height = 2;
                b_width = 2;     
                create_block_array();
                fill_array_with_void();
                t_block[0][0] = BLOCK_STYLE;
                t_block[0][1] = BLOCK_STYLE;
                t_block[1][0] = BLOCK_STYLE;
                t_block[1][1] = BLOCK_STYLE;
            break;

            case S_BLOCK:
                b_height = 2;
                b_width = 3;     
                create_block_array();
                fill_array_with_void();
                t_block[1][0] = BLOCK_STYLE;
                t_block[1][1] = BLOCK_STYLE;
                t_block[0][1] = BLOCK_STYLE;
                t_block[0][2] = BLOCK_STYLE;
            break;

            case T_BLOCK:
                b_height = 2;
                b_width = 3;     
                create_block_array();
                fill_array_with_void();
                t_block[0][1] = BLOCK_STYLE;
                t_block[1][0] = BLOCK_STYLE;
                t_block[1][1] = BLOCK_STYLE;
                t_block[1][2] = BLOCK_STYLE;
            break;

            case Z_BLOCK:
                b_height = 2;
                b_width = 3;     
                create_block_array();
                fill_array_with_void();
                t_block[0][0] = BLOCK_STYLE;
                t_block[0][1] = BLOCK_STYLE;
                t_block[1][1] = BLOCK_STYLE;
                t_block[1][2] = BLOCK_STYLE;
            break;
            };
    }
    ~tetris_block(){
        free(t_block);
    }
/////////////////////////////////////////////////////////
    public:
        void draw_block(){
            for(int i = 0; i < b_height; i++){
                for(int j = 0; j < b_width; j++)
                    printf("%c", t_block[i][j]);
                printf("\n");
            } 
        }
/////////////////////////////////////////////////////////
    protected: 
        void fill_array_with_void(){
               for(int i = 0; i < b_height; i++)
                   for(int j = 0; j < b_width; j++)
                        t_block[i][j] = ' ';
        }
        
        void create_block_array(){
            t_block = new char*[b_height];
                for(int i = 0; i < b_height; i++)
                    t_block[i] = new char[b_width];
        }
/////////////////////////////////////////////////////////
    public:
        char** t_block;
        int b_height;
        int b_width;
};

class console_tetris{
    public:
        console_tetris(){
            create_game_field();
            fill_game_field_with_border();
        }
/////////////////////////////////////////////////////////
    public:
        bool draw_tetris_block(int x_head, int y_head, int x_tail, int y_tail, TETRIS_BLOCK requested_block){
            x_head = x_head + 1; // because of the game field border
            x_tail = x_tail + 1; // because of the game field border
            y_head = y_head + 1; // because of the game field border
            y_tail = y_tail + 1; // because of the game field border

            switch(requested_block){
                case I_BLOCK:
                    for(int draw_x = x_head; draw_x < GAME_FIELD_HEIGHT - 1; draw_x++){
                        for(int draw_y = y_head; draw_y < GAME_FIELD_WIDTH - 1; draw_y++){
                            
                        }
                    }
                break;

                case J_BLOCK:
                break;

                case L_BLOCK:
                break;

                case O_BLOCK:
                break;

                case S_BLOCK:
                break;

                case T_BLOCK:
                break;
                case Z_BLOCK:
                break;
            };
            return true;
        }

        void draw_game_field(){
            for(int gf_height = 0; gf_height < GAME_FIELD_HEIGHT; gf_height++){
                for(int gf_width = 0; gf_width < GAME_FIELD_WIDTH; gf_width++)
                    printf("%c", game_field[gf_height][gf_width]);
                printf("\n");
            } 
        }
/////////////////////////////////////////////////////////
    protected:
        bool fill_game_field_with_border(){
            system("clear");

            for(int gf_height = 0; gf_height < GAME_FIELD_HEIGHT; gf_height++){
                for(int gf_width = 0; gf_width < GAME_FIELD_WIDTH; gf_width++){
                    if(gf_height == 0 || gf_height == GAME_FIELD_HEIGHT - 1 ||
                        (gf_width == 0 && (gf_height != 0 || gf_height != GAME_FIELD_HEIGHT - 1)) ||
                            (gf_width == GAME_FIELD_WIDTH - 1 && (gf_height != 0 || gf_height != GAME_FIELD_HEIGHT - 1)))
                        game_field[gf_height][gf_width] = GAME_FIELD_BORDER;
                }
            }
            return true;
        }

        void create_game_field(){
            for(int gf_height = 0; gf_height < GAME_FIELD_HEIGHT; gf_height++)
                for(int gf_width = 0; gf_width < GAME_FIELD_WIDTH; gf_width++)
                    game_field[gf_height][gf_width] = ' '; 
        }

/////////////////////////////////////////////////////////
    public:
        char game_field[GAME_FIELD_HEIGHT][GAME_FIELD_WIDTH];

};

int main()
{
    console_tetris ct;

    ct.draw_game_field();

    tetris_block tb(J_BLOCK);

    tb.draw_block();
    

    
    return 0;
}