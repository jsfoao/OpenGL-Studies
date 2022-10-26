#version 330 core

in vec3 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
//    FragColor = texture(texture1, TexCoord) * vec4(1.0, 0.0, 0.0, 1.0);
//	  FragColor = texture(texture2, TexCoord);
} 