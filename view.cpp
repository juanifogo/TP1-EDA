/**
 * @brief Implements an orbital simulation view
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 */

#include <time.h>
#include "raylib.h"
#include "raymath.h"
#include "view.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

/**
 * @brief Converts a timestamp (number of seconds since 1/1/2022)
 *        to an ISO date ("YYYY-MM-DD")
 *
 * @param timestamp the timestamp
 * @return The ISO date (a raylib string)
 */
const char *getISODate(float timestamp)
{
    // Timestamp epoch: 1/1/2022
    struct tm unichEpochTM = {0, 0, 0, 1, 0, 122};

    // Convert timestamp to UNIX timestamp (number of seconds since 1/1/1970)
    time_t unixEpoch = mktime(&unichEpochTM);
    time_t unixTimestamp = unixEpoch + (time_t)timestamp;

    // Returns ISO date
    struct tm *localTM = localtime(&unixTimestamp);
    return TextFormat("%04d-%02d-%02d",
                      1900 + localTM->tm_year, localTM->tm_mon + 1, localTM->tm_mday);
}

/**
 * @brief Constructs an orbital simulation view
 *
 * @param fps Frames per second for the view
 * @return The view
 */
View *constructView(int fps)
{
    View *view = new View();

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "EDA Orbital Simulation");
    SetTargetFPS(fps);
    DisableCursor();

    view->camera.position = {10.0f, 10.0f, 10.0f};
    view->camera.target = {0.0f, 0.0f, 0.0f};
    view->camera.up = {0.0f, 1.0f, 0.0f};
    view->camera.fovy = 45.0f;
    view->camera.projection = CAMERA_PERSPECTIVE;

    return view;
}

/**
 * @brief Destroys an orbital simulation view
 *
 * @param view The view
 */
void destroyView(View *view)
{
    CloseWindow();

    delete view;
}

/**
 * @brief Should the view still render?
 *
 * @return Should rendering continue?
 */
bool isViewRendering(View *view)
{
    return !WindowShouldClose();
}

/**
 * Renders an orbital simulation
 *
 * @param view The view
 * @param sim The orbital sim
 */
void renderView(View *view, OrbitalSim *sim)
{
    UpdateCamera(&view->camera, CAMERA_FREE);

    BeginDrawing();

    ClearBackground(BLACK);
    BeginMode3D(view->camera);

    // Fill in your 3D drawing code here:
    for(int i = 0; i < sim->num_bodies; i++) {
        OrbitalBody body = sim->orbital_arr[i];
        Vector3 scale_position = Vector3Scale(body.position, 1E-11F);
        DrawSphere(scale_position, logf(body.radius) * 0.01F, body.color); // Scale down radius for visibility
		DrawPoint3D(scale_position, body.color);
	}


    DrawGrid(10, 10.0f);
    EndMode3D();

    // Fill in your 2D drawing code here:
	DrawFPS(10, 10);
	DrawText(TextFormat("Date: %s",getISODate(sim->time)), 10, 30, 20, RAYWHITE);
	DrawText(TextFormat("Bodies: %d", sim->num_bodies), 10, 50, 20, RAYWHITE);
    DrawText(TextFormat("Venus pos: [%.2f, %.2f, %.2f]",
                       sim->orbital_arr[2].position.x ,
                       sim->orbital_arr[2].position.y ,
                       sim->orbital_arr[2].position.z ),
		10, 70, 20, RAYWHITE);

    EndDrawing();
}
