#version	140


in		vec3	vertpos;
in		vec3	vertcol;

out		vec3	pass_color;

uniform	mat4	transform;


void main()
{
	gl_Position = transform*vec4(vertpos, 1.f);
	pass_color = vertcol;
}
