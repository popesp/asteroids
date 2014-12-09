#version	140


in		vec3	pass_color;

out		vec3	frag_color;


void main()
{
	frag_color = pass_color;
}
