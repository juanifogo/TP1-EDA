/**
 * @brief Implements an orbital simulation view
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 */

/**
 * @brief Implements an orbital simulation view
 * @author Rocco Diaz Parisi and Juan Ignacio Fogolin Lagares
 * Algoritmo y Estructuras de Datos - 25.03
 * TP1 - Warm Up
 * 
 */

#ifndef ORBITALSIMVIEW_H
#define ORBITALSIMVIEW_H

#include <raylib.h>

#include "OrbitalSim.h"

/**
 * The view data
 */
struct View
{
    Camera3D camera;
};

View *constructView(int fps);
void destroyView(View *view);

bool isViewRendering(View *view);
void renderView(View *view, OrbitalSim *sim);

#endif
