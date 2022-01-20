#ifndef PARTICLE_H
#define PARTICLE_H

#include <glad/glad.h>
#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
#include "Utils.h"

#include <string>
#include <vector>
#include <random>
#include <iostream>

// Particle generation mode handler
const char PLAIN = 'p';
const char GALATIC = 'g';
const char FIRE = 'f';
const char CLOUD = 'c';
const char GLOOM = 'o';
const char FLUID = 'w';

// Maximum number of particles to track of
const int MaxParticles = 10000;
// Number of particles spawned each frame
const int SpawnRate = 200;

// Structure of a single particle
struct Particle {
	glm::vec3 m_pos, m_direction;
	// Normalized color data
	float m_r, m_g, m_b, m_a;
	float m_size, m_weight;
	// Time length of existence
	float m_life;
	// To render the particle
	bool m_active = false;

	// Recycle dead particles
	void RenewWorld(Particle temp);
};

#endif
