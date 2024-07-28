#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* grid_surface;
SDL_Surface* x_surface;
SDL_Surface* o_surface;
int game_running = false;
int last_frame_time = 0;
int move_speed = 5000;

int game_state[3][3] = {
    {1, 1, 2}, 
    {2, 1, 2}, 
    {0, 2, 0}
};

#define Win_width 950
#define Win_height 950

#define FPS 2
#define frame_terget_time (100 / FPS)

int initialize_window();

void process_input();

void update();

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

    x_struct.x = 0;
    x_struct.y = 0;
    x_struct.width = 300;
    x_struct.height = 300;
    

}


int main (int argc, char **argv) {
    game_running = initialize_window();

    setup();

    while (game_running) {


        process_input();
        update();
        
        int time_to_wait = frame_terget_time - (SDL_GetTicks() - last_frame_time);
        if (time_to_wait > 0 && time_to_wait <= frame_terget_time) {
            //printf("waiting...\n");
            SDL_Delay(time_to_wait);
            //printf("done!\n");
        }
        last_frame_time = SDL_GetTicks();
        render();

    }

    

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

}

void update() {
    
    //while (!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + frame_terget_time));
    
}

void render() {
    SDL_Texture* grid_texture = SDL_CreateTextureFromSurface(renderer, grid_surface);
    SDL_Texture* x_texture = SDL_CreateTextureFromSurface(renderer, x_surface);
    SDL_Texture* o_texture = SDL_CreateTextureFromSurface(renderer, o_surface);
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
            }
            if (game_state[y][x] == 2) {
                o_struct.x = x * 325;
                o_struct.y = y * 325;
                SDL_Rect o_rect = {(int)o_struct.x, (int)o_struct.y, (int)o_struct.width, (int)o_struct.height};

                SDL_RenderCopy(renderer, o_texture, NULL, &o_rect);
            }
        }
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