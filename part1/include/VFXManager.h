#ifndef VFXMANAGER_H
#define VFXMANAGER_H

#include "Particle.h"
#include "Shader.h"
#include "InstanceBufferLayout.h"
#include "Image.h"
#include "Transform.h"

#include <iostream>
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

class VFXManager {
	// Private constructor for singleton pattern
	VFXManager();
	// The particle pool
	std::vector<Particle> m_particlesContainer;
	// The index of next unused particle
	unsigned int m_nextParticle;
	// Control particle transform
	Transform m_transform;
	// Shader for the animation
	Shader m_shader;
	// Buffer for instancing
	InstanceBufferObject m_instanceBuffer;
	// Store projection model matrix
	glm::mat4 m_projectionMatrix;
	// Animation flag
	char m_flag;
	// Only used in sin curve simulation
	float m_shift;
public:
	// Singleton class
	static VFXManager& Instance();
	// Search for uninitialized particle (Used for continuous emitting)
	// unsigned int NextParticle();
	// Randomly generate a particle by flag
	Particle RandomGen();
	// Initialize particle properties in the pool
	void InitPool();
	// Update the particle pool properties by animation flag
	void UpdatePool();
	// Generate the buffer for rendering particles
	std::vector<float> GenParticleBuffer();
	// Bind everything we need
	void Bind();
	// Update the particale pool status
	void Update(unsigned int screenWidth, unsigned int screenHeight);
	// Render the particles
	void Render();
	// Set the VFX mode
	void SetMode(char flag);
	// Return the actual transform
	Transform& GetTransform();
};

#endif
