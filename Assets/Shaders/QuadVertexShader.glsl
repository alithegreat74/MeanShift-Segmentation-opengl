#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTextureCoordinate;

out vec2 TexCoords;

void main()
{
	gl_Position = vec4(aPos,0.0,1.0);
	TexCoords = aTextureCoordinate;
}