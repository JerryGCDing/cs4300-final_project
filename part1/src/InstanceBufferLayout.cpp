#include "InstanceBufferLayout.h"

InstanceBufferObject::InstanceBufferObject() {
}

InstanceBufferObject::~InstanceBufferObject() {
	glDeleteBuffers(1, &m_instanceBuffer);
}

void InstanceBufferObject::Bind() {
	// Bind to Vertex Array Object
	glBindVertexArray(m_VAOId);
	// Bind to the mesh for instancing on
	glBindBuffer(GL_ARRAY_BUFFER, m_meshVertexVuffer);
	// Bind to the buffer of particle information
	glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);
}

void InstanceBufferObject::Unbind() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void InstanceBufferObject::MakePoint(glm::vec3 vert) {
	m_meshBuffer.push_back(vert.x);
	m_meshBuffer.push_back(vert.y);
	m_meshBuffer.push_back(vert.z);
}

void InstanceBufferObject::CreateInstanceBufferLayout() {
	// Buffer data structure
	// Pos - x, y, z, size
	// Color - r, g, b, a
	int m_stride = 8;

	// Float size consistency
	static_assert(sizeof(GLfloat) == sizeof(float),
		"GLFloat and gloat are not the same size on this architecture");

	// Vertex Array
	glGenVertexArrays(1, &m_VAOId);
	glBindVertexArray(m_VAOId);

	// Create VertexBufferLayout Object
	// Mesh for instancing
	glGenBuffers(1, &m_meshVertexVuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_meshVertexVuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_meshBuffer.size(), &m_meshBuffer[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glVertexAttribDivisor(0, 0);

	// Buffer for maximum number of particles
	glGenBuffers(1, &m_instanceBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * MaxParticles, NULL, GL_STREAM_DRAW);

	// Position pointer
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * m_stride, (void*)0);
	glVertexAttribDivisor(1, 1);
	// Color pointer - RGBA
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, sizeof(float) * m_stride, (void*)(sizeof(float) * 4));
	glVertexAttribDivisor(2, 1);
}

void InstanceBufferObject::Update(std::vector<float>& activePool) {
	// Glowy effect when particles are stacking
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	// Generate active particle pool
	m_particleCount = activePool.size();

	glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);
	// Buffer orphaning
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * MaxParticles, NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_particleCount * sizeof(float), &activePool[0]);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void InstanceBufferObject::Render() {
	// Bind everything
	Bind();
	// Instancing draw
	glDrawArraysInstanced(GL_POINTS, 0, 4, m_particleCount);
}
