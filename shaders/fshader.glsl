#version 400
in vec2 tex_out;
in vec3 nm_out;
out vec4 frag_colour;
uniform sampler2D image;

void main() {
  vec3 light_dir = vec3(1.0, 1.0, 0.0);
  float light = max(0.5, dot(nm_out, light_dir));
	frag_colour = texture(image, tex_out) * light;
}
