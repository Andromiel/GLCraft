#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

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
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    GLuint vertex;
    glGenBuffers(1, &vertex);
    glBindBuffer(GL_ARRAY_BUFFER, vertex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);


    std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4};
    GLuint index;
    glGenBuffers(1, &index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_DYNAMIC_DRAW);

    std::vector shaders = ParseShaders("shaders.shader");
    unsigned int shader = CreateShader(shaders[0], shaders[1]);
    glUseProgram(shader);

    glm::mat4 perspective = glm::perspective(glm::radians(90.0f), float(WIDTH/HEIGHT), 0.01f, 1000.0f);
    glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, -1.0)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0, 1.0));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, -2.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));

    glm::mat4 mvp = perspective * model * view;
    int location = glGetUniformLocation(shader, "matrix");
    glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

    glCheckError();

    double posx, posy;
    glfwGetCursorPos(window, &posx, &posy);
    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
    glm::vec4 eye = glm::vec4(0.0, 0.0, 1.0, 0.0);
    glm::vec3 center = glm::vec3(0.0, 0.0, 0.0);
    view = glm::lookAt(glm::vec3(rotate*eye)+center, center, glm::vec3(0.0, 1.0, 0.0));

    mvp = perspective * model * view;
    glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

    glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            center = center + glm::vec3(eye) * 0.001f;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            center = center + glm::vec3(eye) * -0.001f;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            center = center + glm::vec3(-eye.z, eye.y, eye.x) * -0.001f;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            center = center + glm::vec3(eye.z, eye.y, -eye.x) * -0.001f;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            center = center + glm::vec3(0, 1, 0) * 0.001f;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            center = center - glm::vec3(0, 1, 0) * 0.001f;
        }
        glfwGetCursorPos(window, &posx, &posy);
        posx = posx - WIDTH / 2.0f;
        posy = posy - HEIGHT / 2.0f;

        glfwSetCursorPos(window, WIDTH/2.0f, HEIGHT/2.0f);
        rotate = rotate * glm::rotate(glm::mat4(1.0f), glm::radians((float)(-posx)), glm::vec3(0.0, 1.0, 0.0));
        eye = rotate * glm::vec4(0.0, 0.0, 1.0, 0.0);
        view = glm::lookAt(center, glm::vec3(eye) + center, glm::vec3(0.0, 1.0, 0.0));

        mvp = perspective * view * model;
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