#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_timer.h"
#include "display.h"
#include "vector.h"

bool is_running = false;

const int N_POINTS = 9 * 9 * 9;
vec3_t cube_points[N_POINTS];
vec2_t cube_points_2D[N_POINTS];
vec3_t cube_rotation = { 0, 0, 0};
vec3_t camera_position = { 0, 0, -5 }; 

float fov_factor = 640;

int previous_elapsed_ms = 0;

vec2_t project(vec3_t point) {
    vec2_t point_2D = { 
        fov_factor * point.x / point.z,
        fov_factor * point.y / point.z 
    };
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
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_elapsed_ms);
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    previous_elapsed_ms = SDL_GetTicks();

    // Rotate the cube around all three axes
    cube_rotation.x += 0.001;
    cube_rotation.y += 0.001;
    cube_rotation.z += 0.001;

    // Project our 3D cube points to 2D ones
    for (int i = 0; i < N_POINTS; i++) {
        vec3_t point = cube_points[i];
        // Add the rotation to each point
        // And apply the rotation
        vec3_t transformed_point = vec3_rotate_x(point, cube_rotation.x); 
        transformed_point = vec3_rotate_y(transformed_point, cube_rotation.y); 
        transformed_point = vec3_rotate_z(transformed_point, cube_rotation.z); 
        transformed_point.z -= camera_position.z;
        vec2_t point_2D = project(transformed_point);

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
