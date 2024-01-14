#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <unordered_map>

#include "../Debug.h"
#include "Shader.h"
#include "Uniform.h"

#include <iostream>

using namespace glm;

class Renderer {
private:
    GLFWwindow* _window;
    GLuint _shaders;
    std::unordered_map<std::string, Uniform*> _uniforms;

    std::vector<unsigned int> _vaos;
    mat4 _cameraMatrix;
public:
	Renderer(int width, int height);
    Renderer(const Renderer&) = delete;
    Renderer operator=(const Renderer&) = delete;
	~Renderer();

	void SetShaders(std::string shaderspath);
    bool CloseWindow();
    GLFWwindow* GetWindow();
    void ClearWindow();
    void UpdateCameraMatrix(mat4 matrix);
    mat4 GetCameraMatrix();
    void Draw(int indicesLenght);
    void LinkAndSetUniform(UNIFORM_TYPE type, std::string name, void* data);
    void ResetUniform(std::string name, void* data);
    void SwapBuffers();
    void PollEvents();


};