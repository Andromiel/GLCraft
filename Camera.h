#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>


using namespace glm;

class Camera
{
public:
	Camera(int camWidth, int camHeight);
	void setPosition(vec3 position);
	void moveAbsolute(vec3 position);
	void moveLocal(vec3 position);
	void setRotation(vec3 rotation);
	void rotate(vec3 rotation);
	void setScale(vec3 scale);
	void scale(vec3 scale);
	void setFieldOfView(float FOV);
	mat4 getTransformationMatrix();
	mat4 getProjectionMatrix();
	vec3 getPosition();
	quat getRotation();
	vec3 getScale();
private:
	vec3 _position;
	quat _rotation;
	vec3 _scale;
	float _aspect;
	float _near;
	float _far;
	float _fov;
};

