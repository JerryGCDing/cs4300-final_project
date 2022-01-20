#include "Camera.h"
#include "glm/gtx/transform.hpp"

#include <iostream>

Camera::Camera() {
	// Place the camera certain distance away from the origin
	m_eyePosition = glm::vec3{ 0.0f, 11.0f, 11.0f };
	// Looking at the origin along z-axis
	m_viewDirection = glm::vec3{ 0.0f, -1.0f, -1.0f };
	// Up vector always along the positive y-direction
	m_upVector = glm::vec3{ 0.0f, 1.0f, 0.0f };

	std::cout << "Created a Camera!" << std::endl;
}

Camera& Camera::Instance() {
	static Camera* instance = new Camera();
	return *instance;
}

void Camera::Zoom(float speed, char flag) {
	if (flag == '+') {
		if (m_eyePosition.z > 0) {
			m_eyePosition += m_viewDirection;
		}
	}
	else {
		m_eyePosition -= m_viewDirection;
	}
}

glm::mat4 Camera::GetWorldToViewMatrix() const {
	return glm::lookAt(m_eyePosition,
		m_eyePosition + m_viewDirection,
		m_upVector);
}

float Camera::GetEyeXPostion() {
	return m_eyePosition.x;
}

float Camera::GetEyeYPostion() {
	return m_eyePosition.y;
}

float Camera::GetEyeZPostion() {
	return m_eyePosition.z;
}

float Camera::GetViewXDirection() {
	return m_viewDirection.x;
}

float Camera::GetViewYDirection() {
	return m_viewDirection.y;
}

float Camera::GetViewZDirection() {
	return m_viewDirection.z;
}

void Camera::SetCameraPosition(float x, float y, float z) {
	m_eyePosition.x = x;
	m_eyePosition.y = y;
	m_eyePosition.z = z;
}
