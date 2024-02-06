#shader vertex
#version 400 core
layout(location = 0) in vec3 aPos; // the position variable has attribute position 0
//layout(location = 1) in float texture_id;

uniform mat4 matrix;

out vec4 vertexColor; // specify a color output to the fragment shader
out vec2 TexCoords;
flat out float tex_id;

void main()
{
    gl_Position = matrix * vec4(aPos, 1.0); // see how we directly give a vec2 to vec4's constructor
    vertexColor = vec4(0, 0, 0, 1); // set the output variable to a dark-red color
    TexCoords = aPos.xy;
    //tex_id = texture_id;
}

#shader fragment
#version 400 core
out vec4 FragColor;

in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)
in vec2 TexCoords;
//flat in float tex_id;

uniform sampler2DArray sampledTexture;
void main()
{
    FragColor = vertexColor;
    //FragColor = texture(sampledTexture, vec3(TexCoords, tex_id));

}