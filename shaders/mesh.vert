#version	140


in		vec3		vertpos;
in		vec3		vertcol;

out		vec3		pass_color;

uniform	vec3		lightpos;
uniform	vec3		eyepos;
uniform	mat4		transform;


void main()
{
	pass_color = vertcol;
	gl_Position = transform*vec4(vertpos, 1.f);
}
