#version 330

out vec3 vert;
out vec3 vertNormal;

uniform mat4 worldMatrix;
uniform mat4 projMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;


in vec3 inputNormal;
in vec4 vertex1;



void main() {
    vert = vertex1.xyz;
    vertNormal = normalMatrix*inputNormal;
	vertNormal = inputNormal;	
    gl_Position = projMatrix * worldMatrix * mvMatrix * vertex1;
}