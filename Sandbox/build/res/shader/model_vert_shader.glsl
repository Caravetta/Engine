#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 colour;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;

uniform mat4 view_matrix;
uniform mat4 transformationMatrix;
uniform mat4 projection_matrix;

void main(void){
    vec4 worldPosition = transformationMatrix * vec4(position,1.0);
	gl_Position = projection_matrix * view_matrix *  worldPosition;

    surfaceNormal = (transformationMatrix * vec4(normal,0.0)).xyz;

    toLightVector = vec3(160, 150, 150) - worldPosition.xyz;
    
    toCameraVector = (inverse(view_matrix) * vec4(0.0,0.0,0.0,1.0)).xyz - worldPosition.xyz;
	vec3 a = vec3(0.098,0.486,0.0274);
	vec3 b = vec3(0.501,0.501,0.501);
	colour = b;
}
