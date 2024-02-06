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
#include "Rendering/VertexBuffers.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/Texture.h"
#include "Rendering/Mesh.h"

#include "GameStructure/BlockRegistry.h"
#include "GameStructure/WorldGenerator.h"
#include "GameStructure/Chunk.h"



const int WIDTH = 700;
const int HEIGHT = 700;

int main(void)
{
    Renderer* renderer = new Renderer(WIDTH, HEIGHT);
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    float tex_id = (256-8);
    std::vector<vec3> vertices = {
        vec3(0.0, 0.0, 0.0),
        vec3(0.0, 1.0, 0.0),
        vec3(1.0, 1.0, 0.0),
        vec3(1.0, 0.0, 0.0),

        vec3(0.0, 0.0, 1.0),
        vec3(0.0, 1.0, 1.0),
        vec3(1.0, 1.0, 1.0),
        vec3(1.0, 0.0, 1.0)
    };

    float* newdatatest;
    
    //VertexBuffer vbo(vertices.size(), vertices.data());
    //vbo.SetLayout(layout);
    //std::vector<float> newdata = { 0, 0, 45.0 };
    //glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*3*4, sizeof(float)*3, newdata.data());
    //newdatatest = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
    //std::cout << newdatatest[14] << std::endl;
    //newdatatest[14] = 12.0f;
    //glUnmapBuffer(GL_ARRAY_BUFFER);
    //vbo.Bind();

    std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4};

    //IndexBuffer ibo(indices.size(), indices.data());
    //ibo.Bind();


    Mesh* mesh = new Mesh();
    mesh->setVertices(&vertices);
    mesh->setIndices(&indices);


    std::vector<vec3> cubeVertices = {
        vec3(0.0, 0.0, 0.0),
        vec3(1.0, 0.0, 0.0),
        vec3(1.0, 0.0, 1.0),
        vec3(0.0, 0.0, 1.0),
        vec3(0.0, 1.0, 0.0),
        vec3(1.0, 1.0, 0.0),
        vec3(1.0, 1.0, 1.0),
        vec3(0.0, 1.0, 1.0)
    };

    std::vector<unsigned int> cubeIndices = {
        0, 1, 2,
        2, 3, 0,
        5, 1, 0,
        0, 4, 5,
        6, 2, 1,
        1, 5, 6,
        7, 3, 2,
        2, 6, 7,
        4, 0, 3,
        3, 7, 4,
        6, 5, 4,
        4, 7, 6
    };

    Mesh* mesh2 = new Mesh();
    mesh2->setVertices(&cubeVertices);
    mesh2->setIndices(&cubeIndices);

    SpaceIdentity* cubeTransformation = new SpaceIdentity();
    cubeTransformation->setPosition(vec3(0, 0, 0));
    cubeTransformation->setRotation(vec3(0, 0, 0));


    

    renderer->SetShaders("shaders.shader");

    Texture2DArray texture("C:/Visual Studio Projects/GL Craft Efrei/GL Craft/GameStructure/game_materials/atlas.png");
    

    Camera *camera = new Camera(WIDTH, HEIGHT);
    camera->setPosition(vec3(0.0f, 0.0f, 1.0f));
    camera->setRotation(vec3(0.0f, 0.0f, 0.0f));

    glm::mat4 vp = camera->getProjectionMatrix() * camera->getTransformationMatrix();

    renderer->LinkAndSetUniform(UNIFORM_TYPE::MAT4, "matrix", &vp);

    glCheckError();

    double mouseX, mouseY;
    double orientationX = 0, orientationY = 0;
    int y = 0;

    Chunk* chunk = new Chunk();
    chunk->FillChunk(WorldGenerator::Generate);
    chunk->GenerateMesh();

    SpaceIdentity* chunkPos = new SpaceIdentity();

    /* Loop until the user closes the window */
    while (!renderer->CloseWindow())
    {
        double deltaTime = renderer->GetFrameDeltaTime();

        y++;
        float movingspeed = -1.0f * deltaTime;
        if (glfwGetKey(renderer->GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
            //center = center + glm::vec3(eye) * 0.001f;
            camera->moveLocal(vec3(0, 0, movingspeed));
        }
        if (glfwGetKey(renderer->GetWindow(), GLFW_KEY_S)) {
            //center = center + glm::vec3(eye) * -0.001f;
            camera->moveLocal(vec3(0, 0, -movingspeed));
        }
        if (glfwGetKey(renderer->GetWindow(), GLFW_KEY_A)) {
            //center = center + glm::vec3(-eye.z, eye.y, eye.x) * -0.001f;
            camera->moveLocal(vec3(-movingspeed, 0, 0));
        }
        if (glfwGetKey(renderer->GetWindow(), GLFW_KEY_D)) {
            //center = center + glm::vec3(eye.z, eye.y, -eye.x) * -0.001f;
            camera->moveLocal(vec3(movingspeed, 0, 0));
        }
        if (glfwGetKey(renderer->GetWindow(), GLFW_KEY_SPACE)) {
            //center = center + glm::vec3(0, 1, 0) * 0.001f;
            camera->moveLocal(vec3(0, movingspeed, 0));
        }
        if (glfwGetKey(renderer->GetWindow(), GLFW_KEY_LEFT_SHIFT)) {
            //center = center - glm::vec3(0, 1, 0) * 0.001f;
            camera->moveLocal(vec3(0, -movingspeed, 0));
        }
        glfwGetCursorPos(renderer->GetWindow(), &mouseX, &mouseY);
        orientationX += mouseX - WIDTH / 2.0f;
        orientationY += mouseY - HEIGHT / 2.0f;

        glfwSetCursorPos(renderer->GetWindow(), WIDTH/2.0f, HEIGHT/2.0f);

        float angularMovingSpeed = 0.1f;
        camera->setRotation(vec3(glm::radians((float)orientationY * angularMovingSpeed), glm::radians((float)orientationX * angularMovingSpeed), 0));
        vp = camera->getProjectionMatrix() * camera->getTransformationMatrix();
        renderer->UpdateCameraMatrix(vp);

        /* Render here */
        renderer->ClearWindow();
        //glClearColor(0.0, 1.0, 0.0, 1.0);

        mat4 mvp;

        float cubeSpeed = 100;
        cubeTransformation->setScale(vec3(0.5, 0.5, 0.5));
        for (int i = 0; i < 10; i++) {
            cubeTransformation->setPosition(vec3(i-5, sin(radians((float) renderer->GetTime() * cubeSpeed + 10 * i)), 2.0));
            mvp = renderer->GetCameraMatrix() * cubeTransformation->getTransformationMatrix();
            mesh2->Draw(renderer, &mvp);
            
        }

        mvp = renderer->GetCameraMatrix() * chunkPos->getTransformationMatrix();
        chunk->GetMesh()->Draw(renderer, &mvp);

        std::cout << "FPS : " << (int ) (1 / deltaTime) << std::endl;
        
        /* Swap front and back buffers */
        renderer->SwapBuffers();
        /* Poll for and process events */
        renderer->PollEvents();
    }

    glfwTerminate();
    return 0;
}