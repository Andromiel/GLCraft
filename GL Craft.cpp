#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include "Camera.h"

#include "Context.h"
#include "Debug.h"


#include <iostream>

#include "Shader.h"


const int WIDTH = 700;
const int HEIGHT = 700;

int main(void)
{
    GLFWwindow* window = SeOpenGLContext(WIDTH, HEIGHT);
    if (window == nullptr) {
        std::cout << "An error has occurred while creating Opengl context" << std::endl;
    }

    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    std::vector<float> vertices = {
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 0.0, 0.0,

        0.0, 0.0, 1.0,
        0.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 0.0, 1.0
    };

    GLuint vertexBufferID;
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);


    std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4};
    GLuint indexBufferID;
    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_DYNAMIC_DRAW);

    std::vector shaders = ParseShaders("shaders.shader");
    unsigned int shader = CreateShader(shaders[0], shaders[1]);
    glUseProgram(shader);

    glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, -1.0)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0, 1.0));
    

    Camera *camera = new Camera(WIDTH, HEIGHT);
    camera->moveAbsolute(vec3(0.0f, 0.0f, -1.0f));
    camera->setRotation(vec3(0.0f, 45.0f, 0.0f));

    glm::mat4 mvp = camera->getProjectionMatrix() * camera->getTransformationMatrix() * model;
    int location = glGetUniformLocation(shader, "matrix");
    glUniformMatrix4fv(location, 1, GL_FALSE, &camera->getTransformationMatrix()[0][0]);

    glCheckError();

    double mouseX, mouseY;
    double orientationX = 0, orientationY = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            //center = center + glm::vec3(eye) * 0.001f;
            camera->moveLocal(vec3(0, 0, 0.01f));
        }
        if (glfwGetKey(window, GLFW_KEY_S)) {
            //center = center + glm::vec3(eye) * -0.001f;
            camera->moveLocal(vec3(0, 0, -0.01f));
        }
        if (glfwGetKey(window, GLFW_KEY_A)) {
            //center = center + glm::vec3(-eye.z, eye.y, eye.x) * -0.001f;
            camera->moveLocal(vec3(-0.01f, 0, 0));
        }
        if (glfwGetKey(window, GLFW_KEY_D)) {
            //center = center + glm::vec3(eye.z, eye.y, -eye.x) * -0.001f;
            camera->moveLocal(vec3(0.01f, 0, 0));
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE)) {
            //center = center + glm::vec3(0, 1, 0) * 0.001f;
            camera->moveLocal(vec3(0, 0.01f, 0));
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
            //center = center - glm::vec3(0, 1, 0) * 0.001f;
            camera->moveLocal(vec3(0, -0.01f, 0));
        }
        glfwGetCursorPos(window, &mouseX, &mouseY);
        orientationX += mouseX - WIDTH / 2.0f;
        orientationY += mouseY - HEIGHT / 2.0f;

        glfwSetCursorPos(window, WIDTH/2.0f, HEIGHT/2.0f);

        camera->setRotation(vec3(glm::radians((float)orientationY), glm::radians((float)orientationX), 0));
        mvp = camera->getProjectionMatrix() * camera->getTransformationMatrix() * model;
        glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        //glClearColor(0.0, 1.0, 0.0, 1.0);

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}