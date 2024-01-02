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

#include "Rendering/Shader.h"
#include "Rendering/Renderer.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/Texture.h"





const int WIDTH = 700;
const int HEIGHT = 700;

int main(void)
{
    Renderer renderer(WIDTH, HEIGHT);
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    float tex_id = (256-8);
    std::vector<float> vertices = {
        0.0, 0.0, 0.0, tex_id,
        0.0, 1.0, 0.0, tex_id,
        1.0, 1.0, 0.0, tex_id,
        1.0, 0.0, 0.0, tex_id,

        0.0, 0.0, 1.0, tex_id,
        0.0, 1.0, 1.0, tex_id,
        1.0, 1.0, 1.0, tex_id,
        1.0, 0.0, 1.0, tex_id
    };

    float* newdatatest;
    
    VertexBuffer vbo(vertices.size(), vertices.data());
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(1);
    vbo.SetLayout(layout);
    //std::vector<float> newdata = { 0, 0, 45.0 };
    //glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*3*4, sizeof(float)*3, newdata.data());
    //newdatatest = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
    //std::cout << newdatatest[14] << std::endl;
    //newdatatest[14] = 12.0f;
    //glUnmapBuffer(GL_ARRAY_BUFFER);
    vbo.Bind();

    std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4};

    IndexBuffer ibo(indices.size(), indices.data());
    ibo.Bind();

    

    renderer.SetShaders("shaders.shader");

    Texture2DArray texture("C:/Visual Studio Projects/GL Craft Efrei/GL Craft/GameStructure/game_materials/atlas.png");
    glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, -1.0)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0, 1.0));
    

    Camera *camera = new Camera(WIDTH, HEIGHT);
    camera->moveAbsolute(vec3(0.0f, 0.0f, -1.0f));
    camera->setRotation(vec3(0.0f, 45.0f, 0.0f));

    glm::mat4 mvp = camera->getProjectionMatrix() * camera->getTransformationMatrix() * model;

    renderer.LinkAndSetUniform(UNIFORM_TYPE::MAT4, "matrix", &camera->getTransformationMatrix()[0][0]);

    glCheckError();

    double mouseX, mouseY;
    double orientationX = 0, orientationY = 0;

    /* Loop until the user closes the window */
    while (!renderer.CloseWindow())
    {
        float movingspeed = 0.001f;
        if (glfwGetKey(renderer.GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
            //center = center + glm::vec3(eye) * 0.001f;
            camera->moveLocal(vec3(0, 0, movingspeed));
        }
        if (glfwGetKey(renderer.GetWindow(), GLFW_KEY_S)) {
            //center = center + glm::vec3(eye) * -0.001f;
            camera->moveLocal(vec3(0, 0, -movingspeed));
        }
        if (glfwGetKey(renderer.GetWindow(), GLFW_KEY_A)) {
            //center = center + glm::vec3(-eye.z, eye.y, eye.x) * -0.001f;
            camera->moveLocal(vec3(-movingspeed, 0, 0));
        }
        if (glfwGetKey(renderer.GetWindow(), GLFW_KEY_D)) {
            //center = center + glm::vec3(eye.z, eye.y, -eye.x) * -0.001f;
            camera->moveLocal(vec3(movingspeed, 0, 0));
        }
        if (glfwGetKey(renderer.GetWindow(), GLFW_KEY_SPACE)) {
            //center = center + glm::vec3(0, 1, 0) * 0.001f;
            camera->moveLocal(vec3(0, movingspeed, 0));
        }
        if (glfwGetKey(renderer.GetWindow(), GLFW_KEY_LEFT_SHIFT)) {
            //center = center - glm::vec3(0, 1, 0) * 0.001f;
            camera->moveLocal(vec3(0, -movingspeed, 0));
        }
        glfwGetCursorPos(renderer.GetWindow(), &mouseX, &mouseY);
        orientationX += mouseX - WIDTH / 2.0f;
        orientationY += mouseY - HEIGHT / 2.0f;

        glfwSetCursorPos(renderer.GetWindow(), WIDTH/2.0f, HEIGHT/2.0f);

        float angularMovingSpeed = 1.0f;
        camera->setRotation(vec3(glm::radians((float)orientationY * angularMovingSpeed), glm::radians((float)orientationX * angularMovingSpeed), 0));
        mvp = camera->getProjectionMatrix() * camera->getTransformationMatrix() * model;
        renderer.ResetUniform(&mvp[0][0]);

        /* Render here */
        renderer.ClearWindow();
        //glClearColor(0.0, 1.0, 0.0, 1.0);

        renderer.Draw(indices);
        
        /* Swap front and back buffers */
        renderer.SwapBuffers();
        /* Poll for and process events */
        renderer.PollEvents();
    }

    glfwTerminate();
    return 0;
}