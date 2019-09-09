#include "C:/Users/INV_LEGEND/Desktop/sdl_lib_source_code/include/SDL.h"
#include "C:/Users/INV_LEGEND/Desktop/sdl_lib_source_code/SDL_Image_lib/SDL_image.h"
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define internal static

//Screen dimension constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640
#define CELLS_COUNT 9
#define CELL_SIZE_PX 200
#define LINES_COUNT 4


struct Game_assets{
    SDL_Window* window;
    SDL_Surface* screen_surface;
    SDL_Surface* image;
};

internal void
Free_game_assets(Game_assets* game_assets){
    SDL_FreeSurface(game_assets->screen_surface);
    SDL_DestroyWindow(game_assets->window);
}


internal void 
Init_game_assets(Game_assets* game_assets){
    game_assets->window = SDL_CreateWindow("Image click", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                                   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    game_assets->screen_surface = SDL_GetWindowSurface(game_assets->window);
}

internal bool
Load_media_assets(Game_assets* game_assets){
    bool success = true;
    game_assets->image = SDL_LoadBMP("media_assets/hello_world.bmp");
    if(game_assets->image == NULL){
       printf("[!]Error cannot load media %s[!]\n", SDL_GetError());
        success = false;
    }
    return success;
}

int main( int argc, char* args[] )
{
    srand(time(NULL));
    Game_assets game_assets = { };

    Init_game_assets(&game_assets);
    Load_media_assets(&game_assets);


    SDL_Delay(3000);

    Free_game_assets(&game_assets);
    SDL_Quit();

    printf("END_OF_PROGRAM\n");

	return 0;
}