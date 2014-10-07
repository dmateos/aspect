#version 400
in vec2 tex_out;
out vec4 frag_colour;
uniform sampler2D image;

void main() {
	frag_colour = texture(image, tex_out);
}
