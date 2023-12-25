#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Context.h"
#include "Debug.h"


#include <iostream>

#include "Shader.h"
int main(void)
{
    GLFWwindow* window = SeOpenGLContext();
    if (window == nullptr) {
        std::cout << "An error has occurred while creating Opengl context" << std::endl;
    }

    float vertices[8] = {
        0.0, 0.0, 
        0.0, 1.0,
        1.0, 1.0, 
        1.0, 0.0,
    };

    GLuint vertex;
    glGenBuffers(1, &vertex);
    glBindBuffer(GL_ARRAY_BUFFER, vertex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    unsigned int indices[6] = {0, 1, 2, 2, 3, 0};
    GLuint index;
    glGenBuffers(1, &index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_DYNAMIC_DRAW);

    std::vector shaders = ParseShaders("shaders.shader");
    unsigned int shader = CreateShader(shaders[0], shaders[1]);
    glUseProgram(shader);

    glCheckError();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}