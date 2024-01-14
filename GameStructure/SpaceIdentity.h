#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>

#include "../Rendering/Renderer.h"

using namespace glm;

class SpaceIdentity
{
public:
	SpaceIdentity();
	void setPosition(vec3 position);
	void moveAbsolute(vec3 position);
	void moveLocal(vec3 position);
	void setRotation(vec3 rotation);
	void rotate(vec3 rotation);
	void setScale(vec3 scale);
	void scale(vec3 scale);
	vec3 getPosition();
	quat getRotation();
	vec3 getScale();
	mat4 getTransformationMatrix();
protected:
	vec3 _position;
	quat _rotation;
	vec3 _scale;
};

