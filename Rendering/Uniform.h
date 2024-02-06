#pragma once

#include <GL/glew.h>

#include <string>

#include <glm/mat4x4.hpp> // glm::mat4

enum class UNIFORM_TYPE { 
	MAT4,
	VEC3
};

class Uniform {
private:
	std::string _name;
	unsigned int _location;
	UNIFORM_TYPE _type;
public:
	Uniform();
	Uniform(std::string name, unsigned int shader);
	Uniform(const Uniform&) = delete;
	Uniform operator=(const Uniform&) = delete;
	~Uniform();

	void LinkUniform(std::string name, UNIFORM_TYPE type, unsigned int shader);
	void SetUniform(void* data);
	UNIFORM_TYPE GetType();
};