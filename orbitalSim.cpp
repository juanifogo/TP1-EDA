/**
 * @brief Orbital simulation
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 */

// Enables M_PI #define in Windows
#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <math.h>

#include "orbitalSim.h"
#include "ephemerides.h"

#define GRAVITATIONAL_CONSTANT 6.6743E-11F
#define ASTEROIDS_MEAN_RADIUS 4E11F

/**
 * @brief Gets a uniform random value in a range
 *
 * @param min Minimum value
 * @param max Maximum value
 * @return The random value
 */
float getRandomFloat(float min, float max)
{
    return min + (max - min) * rand() / (float)RAND_MAX;
}

/**
 * @brief Configures an asteroid
 *
 * @param body An orbital body
 * @param centerMass The mass of the most massive object in the star system
 */
void configureAsteroid(OrbitalBody *body, float centerMass)
{
    // Logit distribution
    float x = getRandomFloat(0, 1);
    float l = logf(x) - logf(1 - x) + 1;

    // https://mathworld.wolfram.com/DiskPointPicking.html
    float r = ASTEROIDS_MEAN_RADIUS * sqrtf(fabsf(l));
    float phi = getRandomFloat(0, 2.0F * (float)M_PI);

    // Surprise!
    // phi = 0;

    // https://en.wikipedia.org/wiki/Circular_orbit#Velocity
    float v = sqrtf(GRAVITATIONAL_CONSTANT * centerMass / r) * getRandomFloat(0.6F, 1.2F);
    float vy = getRandomFloat(-1E2F, 1E2F);

    // Fill in with your own fields:
    body->mass = 1E12F;  // Typical asteroid weight: 1 billion tons
    body->radius = 2E3F; // Typical asteroid radius: 2km
    body->color = GRAY;
    body->position = {r * cosf(phi), 0, r * sinf(phi)};
    body->velocity = {-v * sinf(phi), vy, v * cosf(phi)};
	body->isMassive = false;
}

/**
 * @brief Constructs an orbital simulation
 *
 * @param float The time step
 * @return The orbital simulation
 */
OrbitalSim* constructOrbitalSim(float timeStep, int numAsteroids)
{
	const int bodies = SOLARSYSTEM_BODYNUM + numAsteroids;
    OrbitalSim* sim = new OrbitalSim;
    sim->num_bodies = bodies;

    sim->orbital_arr = new OrbitalBody[bodies];
	sim->time_step = timeStep;
	sim->time = 0.0F;

    for(int i = 0; i < SOLARSYSTEM_BODYNUM; i++) {
        sim->orbital_arr[i].name = solarSystem[i].name;
        sim->orbital_arr[i].mass = solarSystem[i].mass; //1000000000000000000000000.0  10000000000000000000000000000000.0;
        sim->orbital_arr[i].radius = solarSystem[i].radius;
        sim->orbital_arr[i].color = solarSystem[i].color;
        sim->orbital_arr[i].position = solarSystem[i].position;
        sim->orbital_arr[i].velocity = solarSystem[i].velocity;
		sim->orbital_arr[i].isMassive = true;
	}

    for (int i = SOLARSYSTEM_BODYNUM; i < bodies; i++) {
        configureAsteroid(&sim->orbital_arr[i], solarSystem[0].mass);
    }
    
    return sim; // This should return your orbital sim
}

/**
 * @brief Destroys an orbital simulation
 */
void destroyOrbitalSim(OrbitalSim *sim)
{
    delete[] sim->orbital_arr;
    delete sim;
}

/**
 * @brief Simulates a timestep
 *
 * @param sim The orbital simulation
 */
void updateOrbitalSim(OrbitalSim *sim)
{
    for (int i = 0; i < sim->num_bodies; i++){
		Vector3 aceleracion_total = { 0,0,0 };
        for (int j = 0; j < sim->num_bodies; j++){
            if (sim->orbital_arr[j].isMassive){

                if (i != j){
					Vector3 diff = Vector3Subtract(sim->orbital_arr[i].position, sim->orbital_arr[j].position);
					double distancia = Vector3Length(diff); // calcula la distancia entre los dos cuerpos antes de normalizar
					double fuerza_magnitud = ( - 1 * GRAVITATIONAL_CONSTANT * sim->orbital_arr[j].mass ) / (distancia * distancia * distancia);
					aceleracion_total = Vector3Add(aceleracion_total, Vector3Scale(diff, fuerza_magnitud));
                }   
            }

        }
		sim->orbital_arr[i].velocity = Vector3Add(sim->orbital_arr[i].velocity, Vector3Scale(aceleracion_total, sim->time_step));

    }

    for (int i = 0; i < sim->num_bodies; i++){
		sim->orbital_arr[i].position = Vector3Add(sim->orbital_arr[i].position, Vector3Scale(sim->orbital_arr[i].velocity, sim->time_step));
    }
	sim->time += sim->time_step;
}
