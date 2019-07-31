#include <termios.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


using namespace std;

const int GAME_FIELD_WIDTH = 24;
const int GAME_FIELD_HEIGHT = 24;
const int TETRIS_BLOCK_COUNT = 7;
const int TETRIS_BLOCK_BASE_SIZE = 4;

const char GAME_FIELD_BORDER = '#';
const char BLOCK_STYLE = '@';

enum TETRIS_BLOCK{I_BLOCK = 0, J_BLOCK, L_BLOCK, O_BLOCK, S_BLOCK, T_BLOCK, Z_BLOCK};
//enum INPUT_KEY{KEY_UP = 72, KEY_DOWN = 80, KEY_LEFT = 75, KEY_RIGHT = 77};


char getch(void){
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
 }

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

            srand(time(NULL));

            I_block = new tetris_block(I_BLOCK);
            J_block = new tetris_block(J_BLOCK);
            L_block = new tetris_block(L_BLOCK);
            O_block = new tetris_block(O_BLOCK);
            S_block = new tetris_block(S_BLOCK);
            T_block = new tetris_block(T_BLOCK);
            Z_block = new tetris_block(Z_BLOCK);

            CURRENT_block = I_block;
            gravity_stop_line = GAME_FIELD_HEIGHT - 1;
            falling_block_exists_on_game_field = false;
            block_pos_X = 1;
            block_pos_Y = 1;

            create_game_field(game_field);
            create_game_field(game_field_buffer);

            fill_game_field_with_border(game_field);
            fill_game_field_with_border(game_field_buffer);

            draw_game_field(game_field);
        }
        ~console_tetris(){
            free(I_block);
            free(J_block);
            free(L_block);
            free(O_block);
            free(S_block);
            free(T_block);
            free(Z_block);
            CURRENT_block = NULL;
        }
/////////////////////////////////////////////////////////
    public:

        void run_game(){
            while(true){
            clear_game_field();
            react_on_key_input(CURRENT_block);
            draw_game_field(game_field_buffer); 
            draw_game_field(game_field);
            printf("[X]: %d ", block_pos_X);
            printf("[Y]: %d\n", block_pos_Y);
            usleep(50 * 1000);
    }
        }

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

        void draw_game_field(char game_f[][GAME_FIELD_WIDTH]){
            for(int gf_height = 0; gf_height < GAME_FIELD_HEIGHT; gf_height++){
                for(int gf_width = 0; gf_width < GAME_FIELD_WIDTH; gf_width++)
                    printf("%c", game_f[gf_height][gf_width]);
                printf("\n");
            } 
        }
/////////////////////////////////////////////////////////
    protected:

        void react_on_key_input(tetris_block* requested_block){

            switch(getch()){
                case 'w':
                    fix_block_position__get_new_block(--block_pos_X, block_pos_Y, 0, 0, requested_block);
                break;

                case 'd':
                    fix_block_position__get_new_block(block_pos_X, ++block_pos_Y, 0, 0, requested_block);
                break;

                case 'a':
                    fix_block_position__get_new_block(block_pos_X, --block_pos_Y, 0, 0, requested_block);
                break;

                case 's':
                    fix_block_position__get_new_block(++block_pos_X, block_pos_Y, 0, 0, requested_block);
                break;
            }
        }

        void swicth_content_between_game_fields(char source_gf[][GAME_FIELD_WIDTH], char destination_gf[][GAME_FIELD_WIDTH]){
            for(int x = 1; x < GAME_FIELD_HEIGHT - 1; x++)
                for(int y = 1; y < GAME_FIELD_WIDTH - 1; y++)
                    destination_gf[x][y] = source_gf[x][y];
            draw_game_field(destination_gf);        
        }

        void clear_game_field(){
            for(int x = 1; x < GAME_FIELD_HEIGHT - 1; x++)
                for(int y = 1; y < GAME_FIELD_WIDTH - 1; y++){
                    if(game_field[x][y] == BLOCK_STYLE) 
                    game_field[x][y] = ' ';       
                }
        }

        void involve_gravity(){
                
        }

        void fix_block_position__get_new_block(int x_head, int y_head, int x_tail, int y_tail, tetris_block* requested_block){
            
            int block_tail = block_pos_X + requested_block->b_height;

            if(block_tail == GAME_FIELD_HEIGHT - 2){
                gravity_stop_line = block_pos_X;
                block_pos_X = 0;
                block_pos_Y = 0;
                CURRENT_block = get_random_block();

                swicth_content_between_game_fields(game_field, game_field_buffer);
                clear_game_field();
                swicth_content_between_game_fields(game_field_buffer, game_field);
                paste_block_on_game_field(block_pos_X, block_pos_Y, x_tail, y_tail, CURRENT_block);
            }else{
                swicth_content_between_game_fields(game_field_buffer, game_field);
                paste_block_on_game_field(x_head, y_head, x_tail, y_tail, CURRENT_block);        
            }
        }

        tetris_block* get_random_block(){
            int rand_block = rand() % TETRIS_BLOCK_COUNT;
            return parse_block_by_number(rand_block);
        }

        tetris_block* parse_block_by_number(int block_number){
            switch (block_number){
                case 0:
                    return I_block;
                break;
                    
                case 1:
                    return J_block;
                break;

                case 2:
                    return L_block;
                break;

                case 3:
                    return O_block;
                break;

                case 4:
                    return S_block;
                break;

                case 5:
                    return T_block;
                break;

                case 6:
                    return Z_block;
                break;
            }
        }

        void paste_block_on_game_field(int x_head, int y_head, int x_tail, int y_tail, tetris_block *requested_block){
            
            x_tail = x_head + 1 + requested_block->b_height;
            y_tail = y_head + 1 + requested_block->b_width;

            for(int paste_x = x_head + 1, t_block_index_x = 0; t_block_index_x < requested_block->b_height; paste_x++, t_block_index_x++)
                for(int paste_y = y_head + 1, t_block_index_y = 0; t_block_index_y < requested_block->b_width; paste_y++, t_block_index_y++){
                    if((x_tail < GAME_FIELD_HEIGHT) && (x_head + 1 > 0) && (y_tail < GAME_FIELD_WIDTH) && (y_head + 1 > 0))
                        game_field[paste_x][paste_y] = requested_block->t_block[t_block_index_x][t_block_index_y];                         
                    else 
                        printf("[!]OUT OF BORDER[!]");
                } 
        }

        bool fill_game_field_with_border(char game_f[][GAME_FIELD_WIDTH]){
            system("clear");

            for(int gf_height = 0; gf_height < GAME_FIELD_HEIGHT; gf_height++){
                for(int gf_width = 0; gf_width < GAME_FIELD_WIDTH; gf_width++){
                    if(gf_height == 0 || gf_height == GAME_FIELD_HEIGHT - 1 ||
                        (gf_width == 0 && (gf_height != 0 || gf_height != GAME_FIELD_HEIGHT - 1)) ||
                            (gf_width == GAME_FIELD_WIDTH - 1 && (gf_height != 0 || gf_height != GAME_FIELD_HEIGHT - 1)))
                        game_f[gf_height][gf_width] = GAME_FIELD_BORDER;
                }
            }
            return true;
        }

        void create_game_field(char game_f[][GAME_FIELD_WIDTH]){
            for(int gf_height = 0; gf_height < GAME_FIELD_HEIGHT; gf_height++)
                for(int gf_width = 0; gf_width < GAME_FIELD_WIDTH; gf_width++)
                    game_f[gf_height][gf_width] = ' '; 
        }

/////////////////////////////////////////////////////////
    public:
        char game_field[GAME_FIELD_HEIGHT][GAME_FIELD_WIDTH];
        char game_field_buffer[GAME_FIELD_HEIGHT][GAME_FIELD_WIDTH];
        bool falling_block_exists_on_game_field;
        int gravity_stop_line;
        int block_pos_X;
        int block_pos_Y;
        tetris_block* I_block;
        tetris_block* J_block;
        tetris_block* L_block;
        tetris_block* O_block;
        tetris_block* S_block;
        tetris_block* T_block;
        tetris_block* Z_block;
        tetris_block* CURRENT_block;

};

int main()
{
    console_tetris ct;

    ct.run_game();
   
    

    
    return 0;
}