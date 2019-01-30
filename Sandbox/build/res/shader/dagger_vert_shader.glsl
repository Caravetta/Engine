#version 400

layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;
layout(location = 5) in vec2 texture;

out vec2 text;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;

uniform mat4 view_matrix;
uniform mat4 transformationMatrix;
uniform mat4 projection_matrix;
uniform mat4 MVP;

void main(void){
    vec4 worldPosition = transformationMatrix * vec4(position,1.0);

	mat4 mvp = projection_matrix * view_matrix * transformationMatrix;

	gl_Position = mvp * vec4(position,1.0);

    surfaceNormal = (transformationMatrix * vec4(normal,0.0)).xyz;

    toLightVector = vec3(160, 150, 150) - worldPosition.xyz;
    
    toCameraVector = (inverse(view_matrix) * vec4(0.0,0.0,0.0,1.0)).xyz - worldPosition.xyz;
	text = texture;
}
