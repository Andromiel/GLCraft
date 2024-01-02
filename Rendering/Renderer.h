#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Debug.h"
#include "Shader.h"
#include "Uniform.h"

#include <iostream>

class Renderer {
private:
    GLFWwindow* _window;
    GLuint _shaders;
    Uniform _uniform;

    std::vector<unsigned int> _vaos;
public:
	Renderer(int width, int height);
    Renderer(const Renderer&) = delete;
    Renderer operator=(const Renderer&) = delete;
	~Renderer();

	void SetShaders(std::string shaderspath);
    bool CloseWindow();
    GLFWwindow* GetWindow();
    void ClearWindow();
    void Draw(const std::vector<unsigned int>& indices);
    void LinkAndSetUniform(UNIFORM_TYPE type, std::string name, void* data);
    void ResetUniform(void* data);
    void SwapBuffers();
    void PollEvents();


};

Renderer::Renderer(int width, int height) {
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        std::cout << "GLFW error : GLFW din't initialize properly" << std::endl;

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        std::cout << "GLFW error : window/Opengl context didn't create correctly" << std::endl;
    }

    //glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, true);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error" << std::endl;
    }

    int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_ERROR, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    _window = window;
}

Renderer::~Renderer() {

}

void Renderer::SetShaders(std::string shaderspath) {
    std::vector shaders = ParseShaders(shaderspath);
    unsigned int shader = CreateShader(shaders[0], shaders[1]);
    glUseProgram(shader);
    _shaders = shader;
}

bool Renderer::CloseWindow() {
    return glfwWindowShouldClose(_window) || glfwGetKey(_window, GLFW_KEY_ESCAPE);
}

GLFWwindow* Renderer::GetWindow() {
    return _window;
}

void Renderer::ClearWindow() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2, 0.4, 0.6, 1.0);
}

void Renderer::Draw(const std::vector<unsigned int>& indices) {
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::LinkAndSetUniform(UNIFORM_TYPE type, std::string name, void* data) {
    _uniform.LinkUniform(name, _shaders);
    _uniform.SetUniform(type, data);
}

void Renderer::ResetUniform(void* data) {
    _uniform.SetUniform(_uniform.GetType(), data);
}

void Renderer::SwapBuffers() {
    glfwSwapBuffers(_window);
}

void Renderer::PollEvents() {
    glfwPollEvents();
}