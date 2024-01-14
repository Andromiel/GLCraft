#include "Uniform.h"
#include <iostream>

Uniform::Uniform() {

}

Uniform::Uniform(std::string name, unsigned int shader) : _name(name), _location(glGetUniformLocation(shader, name.c_str())) {

}

Uniform::~Uniform() {

}

void Uniform::LinkUniform(std::string name, UNIFORM_TYPE type, unsigned int shader) {
	_name = name;
	_location = glGetUniformLocation(shader, _name.c_str());
	_type = type;
}


void Uniform::SetUniform(void* data) {
	switch (_type) {
		case UNIFORM_TYPE::MAT4:
			glUniformMatrix4fv(_location, 1, GL_FALSE, (float*)data);
			break;
	}
}

UNIFORM_TYPE Uniform::GetType() {
	return _type;
}
