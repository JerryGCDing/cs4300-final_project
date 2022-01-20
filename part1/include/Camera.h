#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

class Camera {
	// Private constructor
	Camera();
	// Camera position
	glm::vec3 m_eyePosition;
	// Direction camera is looking at
	glm::vec3 m_viewDirection;
	// Up direction in the world
	glm::vec3 m_upVector;

public:
	// Get the camera instance
	static Camera& Instance();
	// Zoom camera in/out
	void Zoom(float speed, char flag);
	// Return the modelled view matrix
	glm::mat4 GetWorldToViewMatrix() const;
	// Set position of the camera
	void SetCameraPosition(float x, float y, float z);
	// Return camera X position
	float GetEyeXPostion();
	// Return camera Y position
	float GetEyeYPostion();
	// Return camera Z position
	float GetEyeZPostion();
	// Return view X direction
	float GetViewXDirection();
	// Return view X direction
	float GetViewYDirection();
	// Return view X direction
	float GetViewZDirection();
};

#endif
