#pragma once

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

static std::vector<std::string> Split(std::string str, bool keep = false, char del = '\n') {
	std::vector<std::string> strings = {};

	std::string temp = "";
	
	for (char chr : str.substr(0, str.size()-1)) {
		if (chr == del) {
			if (keep) temp += chr;
			strings.push_back(temp);
			temp.clear();
		}
		else {
			temp += chr;
		}
	}

	if (str.back() == del) {
		strings.push_back(temp);
		temp.clear();
	}
	else {
		temp += str.back();
		strings.push_back(temp);
	}

	return strings;
}


enum SHADER {NONE=-1, VERTEX=0, FRAGMENT=1 };

static std::vector<std::string> ParseShaders(std::string filepath) {
	std::ifstream stream(filepath);

	std::string line;

	std::vector<std::string> shaders = { "", "" };

	unsigned int shader = SHADER::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				shader = SHADER::VERTEX;
			}
			if (line.find("fragment") != std::string::npos) {
				shader = SHADER::FRAGMENT;
			}
		}
		else {
			shaders[shader] += line + '\n';
		}
	}

	return shaders;
}

static unsigned int CompileShader(unsigned int type, const std::string sourcecode) {
	const char* src = sourcecode.c_str();
	unsigned int id = glCreateShader(type);
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" << std::endl;
		std::cout << message << std::endl;
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string vshader, const std::string fshader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vshader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fshader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

