#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

const int GAME_FIELD_WIDTH = 24;
const int GAME_FIELD_HEIGHT = 24;
const int TETRIS_BLOCK_COUNT = 7;
const int TETRIS_BLOCK_BASE_SIZE = 4;

const char GAME_FIELD_BORDER = '#';
const char BLOCK_STYLE = '@';

enum TETRIS_BLOCK{I_BLOCK, J_BLOCK, L_BLOCK, O_BLOCK, S_BLOCK, T_BLOCK, Z_BLOCK};

class tetris_block{
    public: 
    tetris_block(TETRIS_BLOCK requested_block){
        exist = false;
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
        bool exist;
};

class console_tetris{
    public:
        console_tetris(){
            I_block = new tetris_block(I_BLOCK);
            J_block = new tetris_block(J_BLOCK);
            L_block = new tetris_block(L_BLOCK);
            O_block = new tetris_block(O_BLOCK);
            S_block = new tetris_block(S_BLOCK);
            T_block = new tetris_block(T_BLOCK);
            Z_block = new tetris_block(Z_BLOCK);
            
            gravity_stop_line = 0;
            falling_block_exists_on_game_field = false;

            create_game_field();
            fill_game_field_with_border();
        }
        ~console_tetris(){
            free(I_block);
            free(J_block);
            free(L_block);
            free(O_block);
            free(S_block);
            free(T_block);
            free(Z_block);
        }
/////////////////////////////////////////////////////////
    public:
        bool draw_tetris_block(int x_head, int y_head, int x_tail, int y_tail, TETRIS_BLOCK requested_block){

            falling_block_exists_on_game_field = true;

            switch(requested_block){
                case I_BLOCK:
                    paste_block_on_game_field(x_head, y_head, x_tail, y_tail, I_block);
                break;

                case J_BLOCK:
                    paste_block_on_game_field(x_head, y_head, x_tail, y_tail, J_block);
                break;

                case L_BLOCK:
                    paste_block_on_game_field(x_head, y_head, x_tail, y_tail, L_block);
                break;

                case O_BLOCK:
                    paste_block_on_game_field(x_head, y_head, x_tail, y_tail, O_block);
                break;

                case S_BLOCK:
                    paste_block_on_game_field(x_head, y_head, x_tail, y_tail, S_block);
                break;

                case T_BLOCK:
                    paste_block_on_game_field(x_head, y_head, x_tail, y_tail, T_block);
                break;
                case Z_BLOCK:
                    paste_block_on_game_field(x_head, y_head, x_tail, y_tail, Z_block);
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
        void involve_gravity(){
            

        }

        void paste_block_on_game_field(int x_head, int y_head, int x_tail, int y_tail, tetris_block *requested_block){
            for(int paste_x = x_head + 1, t_block_index_x = 0; t_block_index_x < requested_block->b_height; paste_x++, t_block_index_x++)
                for(int paste_y = y_head + 1, t_block_index_y = 0; t_block_index_y < requested_block->b_width; paste_y++, t_block_index_y++)
                    game_field[paste_x][paste_y] = requested_block->t_block[t_block_index_x][t_block_index_y];                         
        }

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
        bool falling_block_exists_on_game_field;
        int gravity_stop_line;
        tetris_block* I_block;
        tetris_block* J_block;
        tetris_block* L_block;
        tetris_block* O_block;
        tetris_block* S_block;
        tetris_block* T_block;
        tetris_block* Z_block;

};

int main()
{
    console_tetris ct;

    ct.draw_tetris_block(1, 1, 0, 0, L_BLOCK);
    ct.draw_game_field();

    
    return 0;
}