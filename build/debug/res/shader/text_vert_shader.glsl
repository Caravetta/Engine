#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2)in vec2 text_cord;

out vec3 colour;
out vec2 pass_text_cord;

uniform mat4 view_matrix;
uniform mat4 transformationMatrix;
uniform mat4 projection_matrix;
uniform mat4 ortho_matrix;
uniform vec2 pos;


void main(void){

     gl_Position = ortho_matrix * vec4(position.xy + pos, 0.0, 1.0);
	vec3 a = vec3(1,1,1);
	colour = a;
	pass_text_cord = text_cord;
}
