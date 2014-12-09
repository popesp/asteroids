#version	140


in		vec3		pass_color;

out		vec3		frag_color;

uniform	vec3		ambient;
uniform	vec3		diffuse;
uniform	vec3		specular;
uniform	float		shininess;


void main()
{
	frag_color = pass_color;
}
