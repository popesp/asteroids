#include	"texture.h"

#include	<stdlib.h>
#include	"../lodepng/lodepng.h"


void texture_init(struct texturemanager* tm, int num_textures)
{
	tm->sheet.width = 0;
	tm->sheet.height = 0;
	tm->sheet.id_gl = 0;
	tm->sheet.bytes = NULL;
	
	tm->num_textures = num_textures;
	tm->textures = calloc(num_textures, sizeof(struct texture));
}

void texture_loadsheet(struct texturemanager* tm, char* filename)
{
	unsigned error;
	
	error = lodepng_decode32_file(&tm->sheet.bytes, &tm->sheet.width, &tm->sheet.height, filename);
	
	if (error)
		printf("Error loading %s: %s\n", filename, lodepng_error_text(error));
}
