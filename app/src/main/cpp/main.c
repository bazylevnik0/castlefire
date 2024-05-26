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
#include "../raylib/raymath.h"
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
    Texture2D texture_back[2];
              texture_back[0]  = LoadTextureFromImage(LoadImage("back0.png"));
              texture_back[1]  = LoadTextureFromImage(LoadImage("back1.png"));

    Model house_model[5][5];
    Vector3 house_model_position[5][5];
    BoundingBox house_model_box[5][5];
    bool house_model_selected[5][5];

    for (int z = -2; z <= 2; z++) {
        for (int x =-2; x <= 2; x++) {
            int r = rand() % 4;
            if (r == 0) house_model[z+2][x+2] = LoadModel("house0.glb");
            if (r == 1) house_model[z+2][x+2] = LoadModel("house1.glb");
            if (r == 2) house_model[z+2][x+2] = LoadModel("house2.glb");
            if (r == 3) house_model[z+2][x+2] = LoadModel("house3.glb");
            house_model_position[z+2][x+2] = (Vector3){ x*2.5f, 2.0, z*2.5f };
            house_model_box[z+2][x+2] = GetMeshBoundingBox(house_model[z+2][x+2].meshes[0]);
            house_model_box[z+2][x+2].min = Vector3Add(house_model_box[z+2][x+2].min, (Vector3){ x*2.5f, 2.0, z*2.5f });
            house_model_box[z+2][x+2].max = Vector3Add(house_model_box[z+2][x+2].max, (Vector3){ x*2.5f, 2.0, z*2.5f });
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

    Ray ray = { 0 };        // Picking ray
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // Get ray and test against objects
            ray =  GetMouseRay(GetMousePosition(), camera);
            RayCollision boxHitInfo[5][5];
            for (int z = 0; z < 5; z++) {
                for (int x = 0; x < 5; x++) {
                    boxHitInfo[z][x] = GetRayCollisionBox(ray, house_model_box[z][x]);
                    if (boxHitInfo[z][x].hit) house_model_selected[z][x] = !house_model_selected[z][x];
                }
            }


        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        {
            for (int y = 0; y <= screen_height / 200; y++) {
                for (int x = 0; x <= screen_width / 200; x++) {
                    DrawTexture(texture_back[(x+y)%2] , x*200 , y*200 , WHITE);
                }
            }
        }

        DrawTexture(texture_witch, 0               , screen_height-720, WHITE);
        DrawTexture(texture_king , screen_width-500, screen_height-720, WHITE);

        BeginMode3D(camera);
             for (int z = 0; z < 5; z++) {
                for (int x = 0; x < 5; x++) {
                    DrawModel(house_model[z][x], house_model_position[z][x], 1.0f, WHITE);
                        if (house_model_selected[z][x]) {
                            DrawBoundingBox(house_model_box[z][x], BLACK);
                        } else {
                            DrawBoundingBox(house_model_box[z][x], WHITE);
                        }
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
     for (int z = 0; z < 5; z++) {
        for (int x = 0; x < 5; x++) {
            UnloadModel(house_model[z][x]);
        }
    }
    UnloadTexture(texture_witch);
    UnloadTexture(texture_king);
    UnloadTexture(texture_back[0]);
    UnloadTexture(texture_back[1]);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}