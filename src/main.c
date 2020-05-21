
#include <raylib.h>
#include <math.h>
#include <stdio.h>
#include "level.h"
#include "draw.h"
#include "state.h"

int main(int argc, char const *argv[]){

    // Initialization
    const int screen_width = 800;
    const int screen_height = 600;

    InitWindow(screen_width,screen_height,"Presente - the game");
    SetTargetFPS(60);

    // Initialize level and fill randomly
    level *lvl = level_new(50,40);
    level_fill_random(lvl,6);

    // Initialize state (and add enemies)
    state *sta = state_new();
    state_populate_random(lvl,sta,40);


    int buttonR = 1;
    int buttonT = 0;
    int buttonY = 0;

    

    // Main loop
    while(!WindowShouldClose()){


        
        // Update input depending if keys are pressed or not
        sta->button_state[0] = IsKeyDown(KEY_D);
        sta->button_state[1] = IsKeyDown(KEY_W);
        sta->button_state[2] = IsKeyDown(KEY_A);
        sta->button_state[3] = IsKeyDown(KEY_S);
        sta->button_state[4] = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
        sta->button_state[5] = IsKeyDown(KEY_R);
        sta->button_state[6] = IsKeyDown(KEY_T);
        sta->button_state[7] = IsKeyDown(KEY_Y);
        // Compute the angle the player is looking at from the mouse's position relative to the screen's center
        float mouse_y = GetMouseY()-GetScreenHeight()/2;
        float mouse_x = GetMouseX()-GetScreenWidth()/2;
        sta->aim_angle = atan2(-mouse_y,mouse_x);

        // Update the state
        state_update(lvl,sta,buttonR, buttonY, buttonT);

        if(sta->button_state[5] && buttonR==0){
            buttonR = 1;
            buttonT = 0;
            buttonY = 0;
        }
            
        else if(sta->button_state[6] && buttonT==0){
            buttonT = 1;
            buttonR = 0;
            buttonY = 0;
        }

        else if(sta->button_state[7] && buttonY==0){
            buttonT = 0;
            buttonR = 0;
            buttonY = 1;
        }

        // Drawing
        BeginDrawing();

            ClearBackground(RAYWHITE);
            draw_state(lvl, sta);

            DrawWeapons(buttonR, buttonY, buttonT);

            DrawText("Presente profe!",190,200,20,LIGHTGRAY);     
            DrawText("Armas:",0,0,20,LIGHTGRAY);
            DrawText("(R) Metralleta",5,20,15,LIGHTGRAY);
            DrawText("(T) Rifle Sniper",5,40,15,LIGHTGRAY);
            DrawText("(Y) Bazooka",5,60,15,LIGHTGRAY);

        EndDrawing();

    }

    // Closer window
    CloseWindow();

    // Free memory
    state_free(sta);
    level_free(lvl);

    return 0;
}
