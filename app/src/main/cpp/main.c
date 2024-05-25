/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press Shift+F10 for Android Studio.
*
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2023 Ramon Santamaria (@raysan5) and reviewed by Victor Le Juez
*
********************************************************************************************/

#include <stdlib.h>
#include "raymob.h" // This header can replace 'raylib.h' and includes additional functions related to Android.

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(0, 0, "raylib [core] example - basic window");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Store screen sizes
    int screen_width  = GetScreenWidth();
    int screen_height = GetScreenHeight();
    int render_width  = GetRenderWidth();
    int render_height = GetRenderHeight();

    char str_screen_width[10];
    sprintf(str_screen_width, "%d", screen_width);
    char str_screen_height[10];
    sprintf(str_screen_height, "%d", screen_height);
    char str_render_width[10];
    sprintf(str_render_width, "%d", render_width);
    char str_render_height[10];
    sprintf(str_render_height, "%d", render_height);
    //--------------------------------------------------------------------------------------

    // Uploading sprites and models
    //--------------------------------------------------------------------------------------
    Texture2D texture_witch = LoadTextureFromImage(LoadImage("witch.png"));
    Texture2D texture_king  = LoadTextureFromImage(LoadImage("king.png"));
    Texture2D texture_back  = LoadTextureFromImage(LoadImage("back.png"));

    Model house_model[4];
    house_model[0] = LoadModel("house0.glb");
    house_model[1] = LoadModel("house1.glb");
    house_model[2] = LoadModel("house2.glb");
    house_model[3] = LoadModel("house3.glb");

    Vector3 house_position[5][5];
    for (int z = -2; z <= 2; z++) {
        for (int x =-2; x <= 2; x++) {
            house_position[z+2][x+2] = (Vector3){ x*2.5f, 2.5f, z*2.5f };
        }
    }
    int house_type[5][5];
    for (int z = 0; z < 5; z++) {
        for (int x = 0; x < 5; x++) {
            int r = rand() % 4;
            house_type[z][x] = r;
        }
    }
    //--------------------------------------------------------------------------------------


    // Define the camera
    //--------------------------------------------------------------------------------------
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target   = (Vector3){ 0.0f , 0.0f , 0.0f };  // Camera looking at point
    camera.up       = (Vector3){ 0.0f , 1.6f , 0.0f };  // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(texture_back , 0               , 0                , WHITE);
        DrawTexture(texture_witch, 0               , screen_height-720, WHITE);
        DrawTexture(texture_king , screen_width-500, screen_height-720, WHITE);

        BeginMode3D(camera);
        for (int z = 0; z < 5; z++) {
            for (int x = 0; x < 5; x++) {
                DrawModel(house_model[house_type[z][x]], house_position[z][x], 1.0f, WHITE);
            }
        }
        EndMode3D();

        DrawText(str_screen_width , 150, 0, 20, BLACK);
        DrawText(str_screen_height, 300, 0, 20, BLACK);
        DrawText(str_render_width , 450, 0, 20, BLACK);
        DrawText(str_render_height, 600, 0, 20, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel( house_model[0]);
    UnloadModel( house_model[0]);
    UnloadModel( house_model[0]);
    UnloadModel( house_model[0]);
    UnloadTexture(texture_witch);
    UnloadTexture(texture_king);
    UnloadTexture(texture_back);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}