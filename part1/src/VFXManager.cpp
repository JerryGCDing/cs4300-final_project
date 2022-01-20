#include "VFXManager.h"
#include "Camera.h"

VFXManager::VFXManager() {
	// Set up instance buffer
	m_instanceBuffer.MakePoint(glm::vec3{ 0.0f, 0.0f, 0.0f });
	m_instanceBuffer.CreateInstanceBufferLayout();
	// Starting with the first particle in the pool
	m_nextParticle = 0;
	// Set up shader
	std::string vertexShader = m_shader.LoadShader("./shaders/vert.glsl");
	std::string fragmentShader = m_shader.LoadShader("./shaders/frag.glsl");

	m_shader.CreateShader(vertexShader, fragmentShader);
	// Initialize transform matrix
	m_transform.LoadIdentity();
	// Initial shift
	m_shift = 0.0f;
	// Default flag
	this->SetMode(PLAIN);
}
/*
unsigned int VFXManager::NextParticle() {
	// Search from last used particle, almost instant return
	for (int i = m_nextParticle; i < MaxParticles; i++) {
		if (m_particlesContainer[i].m_life <= 0.0f) {
			m_nextParticle = i;
			return i;
		}
	}
	// OR a linear search
	for (int i = 0; i < m_nextParticle; i++) {
		if (m_particlesContainer[i].m_life <= 0.0f) {
			m_nextParticle = i;
			return i;
		}
	}
	
	// Override from the beginning [WARNING]
	// Unreasonable particle spawning rate
	m_nextParticle = 0; 
	return 0;
}
*/
VFXManager& VFXManager::Instance() {
	static VFXManager* instance = new VFXManager();
	return *instance;
}

Particle VFXManager::RandomGen() {
	Particle temp;
	// Normal distribution randomness
	std::default_random_engine generator;
	std::normal_distribution<float> distribution(0.0f, 0.5f);
	std::normal_distribution<float> lifeDistribution(0.0, 1.0);

	switch (m_flag) {
		/*
	case FIRE:
		temp.m_pos = glm::vec3{ 10 * distribution(generator), distribution(generator),  10 * distribution(generator) };
		temp.m_direction = glm::normalize(glm::vec3{ 0.1 * distribution(generator), 3.0f + distribution(generator), 0.1 * distribution(generator) });
		temp.m_r = 1.0f; temp.m_g = 1.0f; temp.m_b = 0.0f; temp.m_a = 1.0f;
		temp.m_size = 1.5f; temp.m_weight = -1.0f;
		temp.m_life = lifeDistribution(generator) + 1;
		temp.m_active = true;
		break;
		*/
		/*
	case CLOUD:
		temp.m_pos = glm::vec3{ 0.7 * distribution(generator), 0.1 * distribution(generator), 0.7 * distribution(generator) };
		temp.m_r = 1.0f; temp.m_g = 1.0f; temp.m_b = 1.0f; temp.m_a = 0.8f;
		temp.m_size = 1.8f;
		temp.m_life = lifeDistribution(generator) + 2;
		temp.m_active = true;
		break;
		*/
	case GLOOM:
		temp.m_pos = glm::vec3{ distribution(generator), distribution(generator), distribution(generator) };
		temp.m_direction = glm::normalize(glm::vec3{ distribution(generator), distribution(generator), distribution(generator) });
		temp.m_r = 1.0f; temp.m_g = 1.0f; temp.m_b = 0.0f; temp.m_a = 0.9f;
		temp.m_size = 3.0f;
		temp.m_life = lifeDistribution(generator) + 1;
		temp.m_active = true;
		break;
	}

	return temp;
}

void VFXManager::InitPool() {
	m_particlesContainer.clear();
	m_transform.LoadIdentity();
	// Normal randomness
	std::default_random_engine generator;
	std::normal_distribution<float> distribution(0.0f, 0.5f);

	switch (m_flag) {
	case PLAIN:
		for (int i = 0; i < MaxParticles; i++) {
			int z = i / 100;
			int x = i - 100 * z;
			Particle temp;
			temp.m_pos = glm::vec3{ (x - 50) * 0.2, 3.0f, (z - 70) * 0.2 };
			temp.m_r = 1.0f; temp.m_g = 1.0f; temp.m_b = 1.0f; temp.m_a = 1.0f;
			temp.m_size = 1.0f;
			temp.m_active = true;

			m_particlesContainer.push_back(temp);
		}
		std::cout << "Plain effect initialization completed!\n";
		break;
	case GALATIC:
		for (int i = 0; i < MaxParticles * 0.8; i++) {
			Particle temp;
			temp.m_pos = glm::vec3{ 5 * distribution(generator), 5 * distribution(generator), 1.2 * distribution(generator) };
			temp.m_r = 1.0f; temp.m_g = 1.0f; temp.m_b = 0.67f; temp.m_a = 0.8f;
			temp.m_size = 1.0f;
			temp.m_active = true;

			m_particlesContainer.push_back(temp);
		}
		for (int i = 0; i < MaxParticles * 0.2; i++) {
			Particle temp;
			temp.m_pos = glm::vec3{ 15 * distribution(generator), 15 * distribution(generator), 15 * distribution(generator) };
			temp.m_r = 0.8f; temp.m_g = 0.8f; temp.m_b = 0.8f; temp.m_a = 1.0f;
			temp.m_size = 1.0f;
			temp.m_active = true;

			m_particlesContainer.push_back(temp);
		}
		break;
	case FIRE:
		for (int i = 0; i < MaxParticles; i++) {
			m_particlesContainer.push_back(RandomGen());
		}
		break;
	case CLOUD:
		for (int i = 0; i < MaxParticles; i++) {
			m_particlesContainer.push_back(RandomGen());
		}
		break;
	case GLOOM:
		for (int i = 0; i < MaxParticles; i++) {
			m_particlesContainer.push_back(RandomGen());
		}
		break;
	case FLUID:
		for (int i = 0; i < MaxParticles; i++) {
			int z = i / 100;
			int x = i - 100 * z;
			Particle temp;
			temp.m_pos = glm::vec3{ (x - 50) * 0.15, 0.0f, (z - 50) * 0.15 };
			temp.m_r = 1.0f; temp.m_g = 1.0f; temp.m_b = 1.0f; temp.m_a = 1.0f;
			temp.m_size = 1.0f;
			temp.m_active = true;

			m_particlesContainer.push_back(temp);
		}
		break;
	}
	
}

void VFXManager::UpdatePool() {
	// Normal distributed randomness
	std::default_random_engine generator;
	std::normal_distribution<float> distribution(0.0f, 0.5f);

	switch (m_flag) {
		// The default mode as a particle demo
	case PLAIN:
		// Nothing, keep steady
		break;
	case GALATIC:
		// Still nothing, what can I exepct for the fixed stars :)
		// A little rotation
		m_transform.Rotate(0.005, 0.0, 0.0, 1.0);
		break;
		/*
	case FIRE:
		// Fire: Inner flame -> Outter flame -> Smoke -> Dead
		for (int i = 0; i < MaxParticles; i++) {
			Particle* curr = &m_particlesContainer[i];
			if (curr->m_active) {
				curr->m_pos += curr->m_direction / 20.0f;
				curr->m_direction = glm::normalize(curr->m_direction + glm::vec3{ 0.1 * distribution(generator), 3.0f + distribution(generator), 0.1 * distribution(generator) });
				if (curr->m_life > 0.2) {
					curr->m_g = lerp(0.0f, 1.0f, curr->m_life);
				}
				else {
					curr->m_r = lerp(0.3f, 1.0f, curr->m_life * 5); curr->m_g = lerp(0.3f, 0.0f, curr->m_life * 5); curr->m_b = lerp(0.3f, 0.0f, curr->m_life * 5);
				}
				curr->m_a = lerp(0.0f, 1.0f, curr->m_life);

				// Life decay
				curr->m_life -= 0.01;

				if (curr->m_life < 0) {
					curr->m_active = false;
				}
			}
			else {
				curr->RenewWorld(RandomGen());
			}
		}

		break;
		*/
		/*
	case CLOUD:
		// Cloud particles are not moving but fading away and regenerate
		for (int i = 0; i < MaxParticles; i++) {
			Particle* curr = &m_particlesContainer[i];
			if (curr->m_active) {
				curr->m_a = lerp(0.0f, 0.6f, curr->m_life);

				curr->m_life -= 0.005;

				if (curr->m_life < 0) {
					curr->m_active = false;
				}
			}
			else {
				curr->RenewWorld(RandomGen());
			}
		}
		break;
		*/
	case GLOOM:
		// Rather chaotic - emit from the origin
		for (int i = 0; i < MaxParticles; i++) {
			Particle* curr = &m_particlesContainer[i];
			if (curr->m_active) {
				curr->m_pos += curr->m_direction / 20.0f;
				curr->m_direction = glm::normalize(curr->m_direction + glm::vec3{ 1.5 * distribution(generator), 1.5 * distribution(generator), 1.5 * distribution(generator) });
				curr->m_a = lerp(0.0f, 0.6f, curr->m_life);

				curr->m_life -= 0.005;
				if (curr->m_life < 0) {
					curr->m_active = false;
				}
			}
			else {
				curr->RenewWorld(RandomGen());
			}
		}
		break;
		// Developing Idea: Give water texture
		case FLUID:
			float pshift = 0.02;
			for (int z = 0; z < 100; z++) {
				float pdifference = (z % 6 + 1) * 0.5;
				for (int x = 0; x < 100; x++) {
					Particle* curr = &m_particlesContainer[z * 100 + x];
					curr->m_pos.y = sinCurve(x, pdifference, pshift * x + m_shift);
				}
			}
			m_shift += 0.01;
			break;
	}
}

std::vector<float> VFXManager::GenParticleBuffer() {
	std::vector<float> output;

	for (Particle p : m_particlesContainer) {
		if (p.m_active) {
			glm::vec3 pos = p.m_pos;
			output.push_back(pos.x); output.push_back(pos.y); output.push_back(pos.z);
			output.push_back(p.m_size);
			output.push_back(p.m_r); output.push_back(p.m_g); output.push_back(p.m_b); output.push_back(p.m_a);
		}
	}

	return output;
}

void VFXManager::Bind() {
	// Bind buffers
	m_instanceBuffer.Bind();
	// Bind shader
	m_shader.Bind();
}

void VFXManager::Update(unsigned int screenWidth, unsigned int screenHeight) {
	Bind();
	// Get screen projection matrix
	m_projectionMatrix = glm::perspective(45.0f, ((float)screenWidth) / ((float)screenHeight), 0.1f, 20.0f);
	// Pass MVP matrixs to the shader
	m_shader.SetUniformMatrix4fv("model", &m_transform.GetInternalMatrix()[0][0]);
	m_shader.SetUniformMatrix4fv("view", &Camera::Instance().GetWorldToViewMatrix()[0][0]);
	m_shader.SetUniformMatrix4fv("projection", &m_projectionMatrix[0][0]);

	// Update particle container
	UpdatePool();

	// Update buffer data
	std::vector<float> activePool = GenParticleBuffer();
	m_instanceBuffer.Update(activePool);
}

void VFXManager::Render() {
	Bind();
	m_instanceBuffer.Render();
}

void VFXManager::SetMode(char flag) {
	m_flag = flag;
	m_nextParticle = 0;
	InitPool();
}

Transform& VFXManager::GetTransform() {
	return m_transform;
}
