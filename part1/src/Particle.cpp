#include "Particle.h"

void Particle::RenewWorld(Particle temp) {
	this->m_pos = temp.m_pos; this->m_direction = temp.m_direction;
	this->m_r = temp.m_r; this->m_g = temp.m_g; this->m_b = temp.m_b; this->m_a = temp.m_a;
	this->m_size = temp.m_size; this->m_weight = temp.m_weight;
	this->m_life = temp.m_life;
	this->m_active = true;
}
