#shader vertex
#version 400 core
layout(location = 0) in vec3 aPos; // the position variable has attribute position 0

uniform mat4 matrix;

out vec4 vertexColor; // specify a color output to the fragment shader

void main()
{
    gl_Position = matrix * vec4(aPos, 1.0); // see how we directly give a vec2 to vec4's constructor
    vertexColor = gl_Position; // set the output variable to a dark-red color
}

#shader fragment
#version 400 core
out vec4 FragColor;

in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  

void main()
{
    FragColor = vertexColor;
}