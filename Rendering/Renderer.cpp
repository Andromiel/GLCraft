#include "Renderer.h"
#include <glm/gtc/quaternion.hpp>

using namespace glm;

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

    _cameraMatrix = mat4();
    previousTime = glfwGetTime();
    deltaTime = 0;
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

void Renderer::UpdateCameraMatrix(mat4 matrix)
{
    _cameraMatrix = matrix;
}

mat4 Renderer::GetCameraMatrix()
{
    return _cameraMatrix;
}

void Renderer::Draw(int indicesLenght) {
    glDrawElements(GL_TRIANGLES, indicesLenght, GL_UNSIGNED_INT, nullptr);
}

void Renderer::LinkAndSetUniform(UNIFORM_TYPE type, std::string name, void* data) {
    Uniform* uniform = _uniforms[name];
    if (uniform != nullptr)
        delete uniform;
    _uniforms[name] = new Uniform();
    _uniforms[name]->LinkUniform(name, type, _shaders);
    _uniforms[name]->SetUniform(data);
    std::cout << "setted" << std::endl;
}

void Renderer::ResetUniform(std::string name, void* data)
{
    Uniform* uniform = _uniforms[name];
    if (uniform != nullptr) {
        uniform->SetUniform(data);
    }
    else {
        std::cout << "oups" << std::endl;
    }
}

void Renderer::SwapBuffers() {
    glfwSwapBuffers(_window);
    double currentTime = glfwGetTime();
    deltaTime = currentTime - previousTime;
    previousTime = currentTime;
}

void Renderer::PollEvents() {
    glfwPollEvents();
}

double Renderer::GetFrameDeltaTime() {
    return deltaTime;
}

double Renderer::GetTime() {
    return previousTime;
}