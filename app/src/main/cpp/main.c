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
    //--------------------------------------------------------------------------------------

    Image image_witch = LoadImage("witch.png");
    Image image_king  = LoadImage("king.png");
    Texture2D texture_witch = LoadTextureFromImage(image_witch);
    Texture2D texture_king  = LoadTextureFromImage(image_king);
    UnloadImage(image_witch);
    UnloadImage(image_king);

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 20.0f, 20.0f, 20.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 8.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.6f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    Model house0 = LoadModel("house0.glb");
    Model house1 = LoadModel("house1.glb");
    Model house2 = LoadModel("house2.glb");
    Model house3 = LoadModel("house3.glb");
    Vector3 house0pos = { 0.0f, 0.0f, 0.0f };
    Vector3 house1pos = { 2.5f, 0.0f, 0.0f };
    Vector3 house2pos = { 0.0f, 0.0f, 2.5f };
    Vector3 house3pos = { 2.5f, 0.0f, 2.5f };

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(texture_witch, 100, 0, WHITE);
        DrawTexture(texture_king , 1100, 0, WHITE);

        BeginMode3D(camera);
        DrawModel(house0, house0pos, 1.0f, WHITE);
        DrawModel(house1, house1pos, 1.0f, WHITE);
        DrawModel(house2, house2pos, 1.0f, WHITE);
        DrawModel(house3, house3pos, 1.0f, WHITE);
        EndMode3D();

        DrawText("Congrats! You created your first window!", 350, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(house0);
    UnloadModel(house1);
    UnloadModel(house2);
    UnloadModel(house3);
    UnloadTexture(texture_witch);
    UnloadTexture(texture_king);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}