#include	"texture.h"

#include	<GL/glew.h>
#include	<GL/glfw3.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	"../lodepng/lodepng.h"


void texture_init(struct texturemanager* tm, int num_textures)
{
	tm->sheet.width = 0;
	tm->sheet.height = 0;
	tm->sheet.data = NULL;
	
	glActiveTexture(GL_TEXTURE0);
	
	glGenTextures(1, &tm->sheet.id_gl);
	glBindTexture(GL_TEXTURE_2D, tm->sheet.id_gl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	tm->num_textures = num_textures;
	tm->textures = calloc(num_textures, sizeof(struct texture));
}

void texture_destroy(struct texturemanager* tm)
{
	free(tm->sheet.data);
	free(tm->textures);
}


void texture_loadsheet(struct texturemanager* tm, char* filename)
{
	unsigned error;
	
	error = lodepng_decode32_file(&tm->sheet.data, &tm->sheet.width, &tm->sheet.height, filename);
	
	if (error)
		printf("Error loading %s: %s\n", filename, lodepng_error_text(error));
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tm->sheet.width, tm->sheet.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tm->sheet.data);
}
