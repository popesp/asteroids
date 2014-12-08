#include	"shader.h"

#include	<GL/glut.h>
#include	<stdio.h>
#include	<stdlib.h>


int shader_create(char* filename, unsigned char type)
{
	char* text;
	char* info;
	FILE* file;
	int result;
	int len;
	int id;
	int i;
	
	if (type == SHADER_VERTEX)
		id = glCreateShader(GL_VERTEX_SHADER);
	else if (type == SHADER_FRAGMENT)
		id = glCreateShader(GL_FRAGMENT_SHADER);
	else
		return 0;
	
	file = fopen(filename, "rb");
	if (file == NULL)
	{
		printf("Error opening %s.\n", filename);
		return 0;
	}
	
	fseek(file, 0, SEEK_END);
	len = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	text = (char*)malloc(len+1);
	if (fread(text, 1, len, file) != len)
	{
		free(text);
		printf("Error reading from %s.\n", filename);
		return 0;
	}
	
	text[len] = '\0';
	
	glShaderSource(id, 1, &text, NULL);
	glCompileShader(id);
	free(text);
	
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &result);
		info = (char*)malloc(result);
		glGetShaderInfoLog(id, result, NULL, info);
		printf("%s failed to compile:\n%s\n", filename, info);
		free(info);
		return 0;
	}
	
	return id;
}

int shader_program(int vertex, int fragment)
{
	char* info;
	int result;
	int id;
	
	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);
	
	glGetProgramiv(id, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &result);
		info = (char*)malloc(result);
		glGetProgramInfoLog(id, result, NULL, info);
		printf("Failed to link shader program:\n%s\n", info);
		free(info);
		return 0;
	}
	
	return id;
}

void shader_delete(int id)
{
	glDeleteShader(id);
}
