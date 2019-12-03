//#define MVS_BUILD

#ifndef MVS_BUILD
#include "C:/Users/INV_LEGEND/Desktop/bunch_of_stuff/sdl_lib_source_code/include/SDL.h"
#include "C:\SDL\SDL2\include\SDL_image.h"
#endif


#ifdef MVS_BUILD
#include <SDL.h>
#include <SDL_image.h>
#endif

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define internal static

//Screen dimension constants
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define CELLS_COUNT 9
#define CELL_SIZE_PX 200
#define LINES_COUNT 4

#define GAME_ASSET_X_O_SIZE_PX 200

enum X_O_sign{NONE, X, O};

struct pixel {
	uint8_t r, g, b;
	SDL_Rect pixel;
};

struct Cell{
    SDL_Texture* image;
    X_O_sign current_sign;
    uint8_t cell_number;
    // int32_t x, y;
    // int32_t w, h;
    SDL_Rect image_collision_rect;
};
struct Game_assets{
    SDL_Window* window;
    SDL_Renderer* render;
    SDL_Texture* screen_surface;
    SDL_Texture* X_image;
    SDL_Texture* O_image;
    Cell cells_array[CELLS_COUNT];
};

struct Color_palete{
    uint8_t r, g, b;
};

internal void
Free_game_assets(Game_assets* game_assets){

	//TODO : Free cells texture image.
    SDL_DestroyTexture(game_assets->X_image);
    SDL_DestroyTexture(game_assets->O_image);
    SDL_DestroyTexture(game_assets->screen_surface);
    SDL_DestroyWindow(game_assets->window);
}

/* internal SDL_Texture*
Load_texture(SDL_Renderer* render, char* path){
    return SDL_CreateTextureFromSurface(render, IMG_Load(path));
} */

internal void 
Init_game_assets(Game_assets* game_assets){
    game_assets->window = SDL_CreateWindow("Image click", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                                   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //game_assets->screen_surface = SDL_GetWindowSurface(game_assets->window);
    game_assets->render = SDL_CreateRenderer(game_assets->window, -1, SDL_RENDERER_SOFTWARE);
}

internal void
Init_cells(Game_assets* game_assets){
    for(int index = 0; index < CELLS_COUNT; index++){
		game_assets->cells_array[index].image_collision_rect.w = GAME_ASSET_X_O_SIZE_PX;
		game_assets->cells_array[index].image_collision_rect.h = GAME_ASSET_X_O_SIZE_PX;
        game_assets->cells_array[index].current_sign = NONE;
    }

    uint8_t cell_index = 0;
    for (int y = 0; y < SCREEN_HEIGHT; y += GAME_ASSET_X_O_SIZE_PX){
        for (int x = 0; x < SCREEN_WIDTH; x += GAME_ASSET_X_O_SIZE_PX){
            game_assets->cells_array[cell_index].image_collision_rect.x = x;
            game_assets->cells_array[cell_index].image_collision_rect.y = y;
            cell_index++;
        }
    }
    
}

internal void
Debug_check_cells(Game_assets* game_assets){
    SDL_Rect rect;
    rect.w = 10;
    rect.h = 10;
	rect.x = 100;
	rect.y = 100;

	//SDL_RenderClear(game_assets->render);
    SDL_RenderDrawRect(game_assets->render, &rect);
    SDL_SetRenderDrawColor(game_assets->render, 0xff, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(game_assets->render, &rect);
    SDL_RenderPresent(game_assets->render);
}

internal bool
Load_media_assets(Game_assets* game_assets){
    bool success = true;
    game_assets->X_image = SDL_CreateTextureFromSurface(game_assets->render, IMG_Load("media_assets/X.png"));
    game_assets->O_image = SDL_CreateTextureFromSurface(game_assets->render, IMG_Load("media_assets/O.png"));
    if (game_assets->X_image == NULL || game_assets->O_image == NULL)
    {
        OutputDebugStringA("[!]Error cannot load media %s[!]\n");
        success = false;
    }
    return success;
}

internal void
Draw_game_field(Game_assets* game_assets, Color_palete* color){
    SDL_SetRenderDrawColor(game_assets->render, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(game_assets->render);

    SDL_SetRenderDrawColor(game_assets->render, color->r, color->g, color->b, SDL_ALPHA_OPAQUE);
    //drawing horizontal lines
    //SDL_RenderSetScale(game_assets->render, 3.0f, 3.0f);
    for(int h = GAME_ASSET_X_O_SIZE_PX; h < SCREEN_HEIGHT; h += GAME_ASSET_X_O_SIZE_PX){
        SDL_RenderDrawLine(game_assets->render, 0, h, SCREEN_WIDTH, h);
        SDL_RenderDrawLine(game_assets->render, 0, h + 1, SCREEN_WIDTH + 1, h + 1);
    }
    //drawing vertical lines
    for (int v = GAME_ASSET_X_O_SIZE_PX; v < SCREEN_WIDTH; v += GAME_ASSET_X_O_SIZE_PX){
        SDL_RenderDrawLine(game_assets->render, v, 0, v, SCREEN_WIDTH);
        SDL_RenderDrawLine(game_assets->render, v + 1, 0, v + 1, SCREEN_WIDTH + 1);
    }

    //DEBUG field
    
    SDL_RenderCopy(game_assets->render, game_assets->X_image, NULL, &(game_assets->cells_array[1].image_collision_rect));
    SDL_RenderCopy(game_assets->render, game_assets->O_image, NULL, &(game_assets->cells_array[0].image_collision_rect));

    //SDL_SetRenderDrawColor(game_assets->render, 255, 0, 0, SDL_ALPHA_OPAQUE);
    //SDL_RenderFillRect(game_assets->render, &(game_assets->cells_array[4].image_collision_rect));

    SDL_RenderPresent(game_assets->render);
}

int main( int argc, char* args[] )
{
    srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
    Game_assets game_assets = { };
    Color_palete color ={0, 0, 0};

    Init_game_assets(&game_assets);
	Init_cells(&game_assets);
	Load_media_assets(&game_assets);
    Draw_game_field(&game_assets, &color);
    //Debug_check_cells(&game_assets);
    //SDL_RenderCopy(game_assets.render, game_assets.X_image, NULL, NULL);
    //SDL_RenderPresent(game_assets.render);

    //SDL_BlitSurface(game_assets.image, NULL, game_assets.screen_surface, NULL);
    //SDL_UpdateWindowSurface(game_assets.window);

    //TODO: Handle mouse input
    int x, y;
    

    while(1){
		SDL_GetMouseState(&x, &y);
        if(x > 30)
            OutputDebugStringA("Mouse on area!\n");
        else
            OutputDebugStringA("Miss\n");    
        Sleep(200);
    }

    SDL_Delay(3000);

    Free_game_assets(&game_assets);
    SDL_Quit();

    printf("END_OF_PROGRAM\n");

	return 0;
}
