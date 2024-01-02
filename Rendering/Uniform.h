#pragma once

#include <GL/glew.h>

#include <string>

#include <glm/mat4x4.hpp> // glm::mat4

enum class UNIFORM_TYPE { MAT4 = 0 };

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

	void LinkUniform(std::string name, unsigned int shader);
	void SetUniform(UNIFORM_TYPE type, void* data);
	UNIFORM_TYPE GetType();
};

Uniform::Uniform() {

}

Uniform::Uniform(std::string name, unsigned int shader) : _name(name), _location(glGetUniformLocation(shader, name.c_str())) {
	
}

Uniform::~Uniform() {

}

void Uniform::LinkUniform(std::string name, unsigned int shader) {
	_name = name;
	_location = glGetUniformLocation(shader, _name.c_str());
}


void Uniform::SetUniform(UNIFORM_TYPE type, void* data) {
	switch (type) {
	case UNIFORM_TYPE::MAT4 :
		glUniformMatrix4fv(_location, 1, GL_FALSE, (float*)data);
		_type = type;
	}
}

UNIFORM_TYPE Uniform::GetType() {
	return _type;
}
