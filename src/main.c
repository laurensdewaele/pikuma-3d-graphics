#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"

bool is_running = false;

const int N_POINTS = 9 * 9 * 9;
vec3_t cube_points[N_POINTS];
vec2_t cube_points_2D[N_POINTS];

// Why 128?
float fov_factor = 128;

vec2_t project(vec3_t point) {
    vec2_t point_2D = { fov_factor * point.x, fov_factor * point.y };
    return point_2D;
}

void setup(void) {
    // Create our cube
    // So we need 
    int point_count = 0;
    for (float x = -1; x <= 1; x += .25) {
        for (float y = -1; y <= 1; y += .25) {
            for (float z = -1; z <= 1; z += .25) {
                vec3_t new_point = { x , y , z };
                cube_points[point_count] = new_point;
                point_count += 1;
            }
        }
    } 


    // Allocate the required memory in bytes to hold the color buffer
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

    // Creating a SDL texture that is used to display the color buffer
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );
}

void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                is_running = false;
            break;
    }
}

void update(void) {
    // Project our 3D cube points to 2D ones
    for (int i = 0; i < N_POINTS; i++) {
        vec3_t point = cube_points[i];
        vec2_t point_2D = project(point);
        cube_points_2D[i] = point_2D;
    }
}

void render(void) {

    draw_grid();

    // Loop over 2D points and render them
    for (int i = 0; i < N_POINTS; i++) {
        vec2_t point = cube_points_2D[i];
        draw_rect(
            point.x + window_width / 2,
            point.y + window_height / 2, 
            4, 4, 0xFFFFFF00); 
    }

    render_color_buffer();
    clear_color_buffer(0xFF000000);

    SDL_RenderPresent(renderer);
}

int main(void) {
    is_running = initialize_window();

    setup();

    while (is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
