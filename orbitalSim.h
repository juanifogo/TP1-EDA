/**
 * @brief Orbital simulation
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

#ifndef ORBITALSIM_H
#define ORBITALSIM_H

#include "raylib.h"
#include "raymath.h"

/**
 * @brief Orbital body definition
 */
struct OrbitalBody
{
	const char* name; // Name
	double mass;		  // [kg]
	double radius;	  // [m]
	Color color;	  // Raylib color
	Vector3 position; // [m]
	Vector3 velocity; // [m/s]
	bool isMassive; // Whether the body is considered massive (for gravity calculations)
};

/**
 * @brief Orbital simulation definition
 */
struct OrbitalSim
{
	double time_step;
	double time;
	int num_bodies;
	OrbitalBody* orbital_arr;

};

OrbitalSim *constructOrbitalSim(float timeStep, int numAsteroids);
void destroyOrbitalSim(OrbitalSim *sim);

void updateOrbitalSim(OrbitalSim *sim);

#endif
