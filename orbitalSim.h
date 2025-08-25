/**
 * @brief Orbital simulation
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 */

#ifndef ORBITALSIM_H
#define ORBITALSIM_H

/**
 * @brief Orbital body definition
 */
struct OrbitalBody
{
	const char* name; // Name
	float mass;		  // [kg]
	float radius;	  // [m]
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
	float time_step;
	float time;
	int num_bodies;
	OrbitalBody* orbital_arr;

};

OrbitalSim *constructOrbitalSim(float timeStep);
void destroyOrbitalSim(OrbitalSim *sim);

void updateOrbitalSim(OrbitalSim *sim);

#endif
