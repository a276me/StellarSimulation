

#include "raylib.h"
#include "physics.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800*3;
    const int screenHeight = 450*3;

    stellarEntities.push_back(stellarObject({0,0,0},{0,0,0},{0,0,0},BM*2,string("Star1"), 2));
    // stellarEntities.push_back(stellarObject({0,0,0},{-30,10,0},{0,0,0},BM*0.5,string("Star2"), 0.5));
    // stellarEntities.push_back(stellarObject({0,0,0},{40,10,-5},{0,0,0},BM,string("Star3"), 1));
    stellarEntities.push_back(stellarObject({0,5,0},{0,0,10},{0,0,0},BM*1,string("Planet"), 1));
    stellarEntities.push_back(stellarObject({0,7,0},{0,0,5},{0,0,0},BM*0.01,string("Planet2"), 0.1));
    // stellarEntities.push_back(stellarObject({0,0,0},{20,5,19},{0,0,0},99999999999,string("kenobi")));

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

    Vector3 position = { 0.0f, 0.0f, 0.0f };

    SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

    SetTargetFPS(120);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    // calculatePhysics();

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        cout<<"here";
        // Update
        //----------------------------------------------------------------------------------
        for(int i=0;i<16*time;i++)
            calculatePhysics();


        UpdateCamera(&camera);          // Update camera

        if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        //----------------------------------------------------------------------------------

        

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(camera);

                for(int i = 0; i<stellarEntities.size(); i++){
                    DrawSphere(stellarEntities[i].position, stellarEntities[i].radius, RAYWHITE);
                }

                // DrawSphere(position, 1, RAYWHITE);   

                DrawGrid(1000, 10.0f);

            EndMode3D();

            for(stellarObject i : stellarEntities){
                Vector2 cubeScreenPosition = GetWorldToScreen((Vector3){i.position.x, i.position.y + 2.5f, i.position.z}, camera);
                DrawText(i.name.c_str(), (int)cubeScreenPosition.x - MeasureText("Enemy: 100/100", 20)/2, (int)cubeScreenPosition.y, 20, RAYWHITE);
            }

            DrawRectangle( 10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 320, 133, BLUE);

            // DrawText("Free camera default controls:", 20, 20, 10, BLACK);
            // DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, RAYWHITE);
            // DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, RAYWHITE);
            // DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, RAYWHITE);
            // DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, RAYWHITE);
            // DrawText("- Z to zoom to (0, 0, 0)", 40, 120, 10, RAYWHITE);
            DrawFPS(10,10);

            DrawText(to_string(stellarEntities[0].position.x).c_str(), 20, 20, 10, RAYWHITE);
            DrawText(to_string(stellarEntities[0].position.y).c_str(), 20, 40, 10, RAYWHITE);
            DrawText(to_string(stellarEntities[0].position.z).c_str(), 20, 60, 10, RAYWHITE);

            DrawText(to_string(stellarEntities[1].position.x).c_str(), 20, 80, 10, RAYWHITE);
            DrawText(to_string(stellarEntities[1].position.y).c_str(), 20, 100, 10, RAYWHITE);
            DrawText(to_string(stellarEntities[1].position.z).c_str(), 20, 120, 10, RAYWHITE);

            DrawText(to_string(stellarEntities[0].acceleration.x).c_str(), 80, 20, 10, RAYWHITE);
            DrawText(to_string(stellarEntities[0].acceleration.y).c_str(), 80, 40, 10, RAYWHITE);
            DrawText(to_string(stellarEntities[0].acceleration.z).c_str(), 80, 60, 10, RAYWHITE);

            DrawText(to_string(ttt(stellarEntities[0],stellarEntities[1])).c_str(), 80, 80, 10, RAYWHITE);
            DrawText(to_string(ttt(stellarEntities[0],stellarEntities[1])).c_str(), 80, 100, 10, RAYWHITE);
            DrawText(to_string(stellarEntities[0].position.x).c_str(), 80, 120, 10, RAYWHITE);

            // DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, RAYWHITE);
            // DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, RAYWHITE);
            // DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, RAYWHITE);
            // DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, RAYWHITE);
            // DrawText("- Z to zoom to (0, 0, 0)", 40, 120, 10, RAYWHITE);
            

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}