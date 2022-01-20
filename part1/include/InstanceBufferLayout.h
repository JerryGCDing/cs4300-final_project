#ifndef INSTANCEBUFFERLAYOUT_H
#define INSTANCEBUFFERLAYOUT_H

#include "Particle.h"

class InstanceBufferObject
{
	// Store the mesh vertices of particles
	std::vector<GLfloat> m_meshBuffer;
	// Vertex Array Object
	GLuint m_VAOId;
	// Mesh vertices buffer
	GLuint m_meshVertexVuffer;
	// Particle instance buffer
	GLuint m_instanceBuffer;

	// Keep track of number of active particles
	int m_particleCount;
public:
	// Generate a new instance buffer
	InstanceBufferObject();
	// Destroy all buffer objects
	~InstanceBufferObject();
	// Bind the current buffer
	void Bind();
	// Unbind the buffer
	void Unbind();
	// Set the particle point for instancing
	void MakePoint(glm::vec3 vert1);
	// Create a new instance buffer object
	// Position - x, y, z
	// Color - r, g, b, a
	// Other Properties (TBD)
	void CreateInstanceBufferLayout();
	// Update the buffer
	void Update(std::vector<float>& activePool);
	// Render the buffer
	void Render();
};

#endif
