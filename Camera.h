#pragma once
#include <glm/mat4x4.hpp>
#include "SpaceIdentity.h"


using namespace glm;

class Camera : SpaceIdentity
{
public:
	Camera(int camWidth, int camHeight);
	void setFieldOfView(float FOV);
	mat4 getTransformationMatrix();
	mat4 getProjectionMatrix();
private:
	float _aspect;
	float _near;
	float _far;
	float _fov;
};

