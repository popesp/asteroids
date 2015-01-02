#version	140


in		vec2		vertpos;
in		vec2		verttex;

out		vec2		pass_texcoords;

uniform mat4		transform;


void main()
{
	pass_texcoords = verttex;
	gl_Position = transform*vec4(vertpos, 0.f, 1.f);
}
