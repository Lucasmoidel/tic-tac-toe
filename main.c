#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>



SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* grid_surface;
SDL_Surface* x_surface;
SDL_Surface* o_surface;
SDL_Texture* grid_texture;
SDL_Texture* x_texture;
SDL_Texture* o_texture;
SDL_Surface* x_wins_surface;
SDL_Surface* o_wins_surface;
SDL_Texture* x_wins_texture;
SDL_Texture* o_wins_texture;
SDL_Texture* tie_texture;
SDL_Surface* tie_surface;
int p;
int time_to_wait;
int game_running = false;
int last_frame_time = 0;
int move_speed = 5000;
int player;
int game_state[3][3] = {
    {0, 0, 0}, 
    {0, 0, 0}, 
    {0, 0, 0}
};
int winner;
#define Win_width 950
#define Win_height 950

#define FPS 15
#define frame_terget_time (100 / FPS)

int initialize_window();

void process_input();

void render();

void destroy_window();

struct x_struct {

    float x, y, width, height;
} x_struct;
struct o_struct {

    float x, y, width, height;
} o_struct;
void setup() {
    grid_surface = IMG_Load("grid.png");
    x_surface = IMG_Load("x.png");
    o_surface = IMG_Load("o.png");
    SDL_SetWindowIcon(window, grid_surface);
    grid_texture = SDL_CreateTextureFromSurface(renderer, grid_surface);
    x_texture = SDL_CreateTextureFromSurface(renderer, x_surface);
    o_texture = SDL_CreateTextureFromSurface(renderer, o_surface);

    x_wins_surface = IMG_Load("x_wins.png");
    o_wins_surface = IMG_Load("o_wins.png");

    x_wins_texture = SDL_CreateTextureFromSurface(renderer, x_wins_surface);
    o_wins_texture = SDL_CreateTextureFromSurface(renderer, o_wins_surface);

    tie_surface = IMG_Load("tie.png");
    tie_texture = SDL_CreateTextureFromSurface(renderer, tie_surface);

    x_struct.x = 0;
    x_struct.y = 0;
    x_struct.width = 300;
    x_struct.height = 300;
       
    o_struct.x = 690;
    o_struct.y = 600;
    o_struct.width = 300;
    o_struct.height = 300;
    
    player = 1;
    winner = 0;

}


int main (int argc, char **argv) {
    game_running = initialize_window();

    setup();

    while (game_running) {


        process_input();
        
        time_to_wait = frame_terget_time - (SDL_GetTicks() - last_frame_time);
        if (time_to_wait > 0 && time_to_wait <= frame_terget_time) {
            //printf("waiting...\n");
            SDL_Delay(time_to_wait);
            //printf("done!\n");
        }
        last_frame_time = SDL_GetTicks();




        //printf("{\n {%d, %d, %d},\n {%d, %d, %d}, \n {%d, %d, %d} \n}", game_state[0][0],game_state[0][1], game_state[0][2], game_state[1][0], game_state[1][1], game_state[1][2], game_state[2][0], game_state[2][1], game_state[2][2]);
        render();

    }

    
    SDL_Delay(5000);
    destroy_window();

    return 0;
}

void process_input() {

    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        game_running = false;
        break;
    
    case SDL_KEYDOWN:
        switch (event.key.keysym.scancode)
        {
            case SDL_SCANCODE_ESCAPE:
                game_running = false;
                printf("closed succesfuly\n");
                break;
            default:
                break;
        }
        break;

    default:
        break;

    }
    int x, y;
    if (SDL_MOUSEBUTTONDOWN == event.type) {
        SDL_GetMouseState( &x, &y);
        if (SDL_BUTTON_LEFT == event.button.button) {
            if ((x >= 0 && x <= 300) && (y >= 0 && y <= 300 )){
                if (game_state[0][0] == 0) {
                    game_state[0][0] = player;
                    if (player == 1) {player = 2;} else if (player == 2){ player = 1;}
                    
                } 
            }else if ((x >= 325 && x <= 625) && (y >= 0 && y <= 300 )){
                if (game_state[0][1] == 0) {
                    game_state[0][1] = player;
                    if (player == 1) {player = 2;} else if (player == 2){ player = 1;}
                } 
            }else if ((x >= 650 && x <= 950) && (y >= 0 && y <= 300 )){
                if (game_state[0][2] == 0) {
                    game_state[0][2] = player;
                    if (player == 1) {player = 2;} else if (player == 2){ player = 1;}
                } 
            } else if ((x >= 0 && x <= 300) && (y >= 325 && y <= 625)){
                if (game_state[1][0] == 0) {
                    game_state[1][0] = player;
                    if (player == 1) {player = 2;} else if (player == 2){ player = 1;}
                } 
            } else if ((x >= 325 && x <= 625) && (y >= 325 && y <= 625)){
                if (game_state[1][1] == 0) {
                    game_state[1][1] = player;
                    if (player == 1) {player = 2;} else if (player == 2){ player = 1;}
                } 
            } else if ((x >= 650 && x <= 950) && (y >= 325 && y <= 625)){
                if (game_state[1][2] == 0) {
                    game_state[1][2] = player;
                    if (player == 1) {player = 2;} else if (player == 2){ player = 1;}
                } 
            } else if ((x >= 0 && x <= 300) && (y >= 650 && y <= 950)){
                if (game_state[2][0] == 0) {
                    game_state[2][0] = player;
                    if (player == 1) {player = 2;} else if (player == 2){ player = 1;}
                } 
            } else if ((x >= 325 && x <= 625) && (y >= 650 && y <= 950)){
                if (game_state[2][1] == 0) {
                    game_state[2][1] = player;
                    if (player == 1) {player = 2;} else if (player == 2){ player = 1;}
                } 
            } else if ((x >= 650 && x <= 950) && (y >= 650 && y <= 950)){
                if (game_state[2][2] == 0) {
                    game_state[2][2] = player;
                    if (player == 1) {player = 2;} else if (player == 2){ player = 1;}
                } 
            }
        }
    }

}

void render() {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);


    //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect x_rect = {(int)x_struct.x, (int)x_struct.y, (int)x_struct.width, (int)x_struct.height};
    SDL_Rect o_rect = {(int)o_struct.x, (int)o_struct.y, (int)o_struct.width, (int)o_struct.height};
    


    SDL_RenderCopy(renderer, grid_texture, NULL, NULL);
    //SDL_RenderCopy(renderer, x_texture, NULL, &x_rect);



    int x, y;
    for (y = 0; y < 3; y++) {
        for (x = 0; x < 3; x++) {
            if (game_state[y][x] == 1) {
                x_struct.x = x * 325;
                x_struct.y = y * 325;
                SDL_Rect x_rect = {(int)x_struct.x, (int)x_struct.y, (int)x_struct.width, (int)x_struct.height};

                SDL_RenderCopy(renderer, x_texture, NULL, &x_rect);
            } else if (game_state[y][x] == 2) {
                o_struct.x = x * 325;
                o_struct.y = y * 325;
                SDL_Rect o_rect = {(int)o_struct.x, (int)o_struct.y, (int)o_struct.width, (int)o_struct.height};

                SDL_RenderCopy(renderer, o_texture, NULL, &o_rect);
            }
        }
    }

    for (p = 1; p < 3; p++) {
        if ((game_state[0][0] == p && game_state[1][1] == p && game_state[2][2] == p) || (game_state[0][2] == p && game_state[1][1] == p && game_state[2][0] == p) || (game_state[0][0] == p && game_state[0][1] == p && game_state[0][2] == p) || (game_state[1][0] == p && game_state[1][1] == p && game_state[1][2] == p) || (game_state[2][0] == p && game_state[2][1] == p && game_state[2][2] == p) || (game_state[0][0] == p && game_state[1][0] == p && game_state[2][0] == p) || (game_state[0][1] == p && game_state[1][1] == p && game_state[2][1] == p) || (game_state[0][2] == p && game_state[1][2] == p && game_state[2][2] == p)) {
            if (p == 1) {
                printf("x wins");
                SDL_RenderCopy(renderer, x_wins_texture, NULL, NULL);
                SDL_RenderPresent(renderer);
                game_running = false;
            }
            if (p == 2) {
                printf("o wins");
                SDL_RenderCopy(renderer, o_wins_texture, NULL, NULL);
                SDL_RenderPresent(renderer);
                game_running = false;
            }
        }  
    } 

    if ( (game_state[0][0] != 0) && (game_state[0][1] != 0) && (game_state[0][2] != 0) && (game_state[1][0] != 0) && (game_state[1][1] != 0) && (game_state[1][2] != 0) && (game_state[2][0] != 0) && (game_state[2][1] != 0) && (game_state[2][2] != 0)) {
        SDL_RenderCopy(renderer, tie_texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        game_running = false;
    }


    //SDL_RenderFillRect(renderer, &player_rect);

    SDL_RenderPresent(renderer);
}



void destroy_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int initialize_window(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("init sdl failed\n");
        return 0;
    }


    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Win_width, Win_height, 0);
    

    if (!window) {
        printf ("failed to create window\n");
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        printf ("failed to create renderer\n");
        return 0;
    }

    return 1;
}