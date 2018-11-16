#version 400

in vec3 colour;
in vec2 pass_text_cord;

uniform sampler2D modelTexture;

out vec4 out_Color;

void main(void){
	
	out_Color = vec4(colour.xyz, texture(modelTexture, pass_text_cord).r);
}
