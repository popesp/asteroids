#ifndef	TEXTURE
#define	TEXTURE


struct texturesheet
{
	int width, height;
	
	int id_gl;
	
	unsigned char* data;
};

struct texture
{
	float ul, ur;
	float vt, vb;
};

struct texturemanager
{
	struct texturesheet sheet;
	
	int num_textures;
	struct texture* textures;
};


void texture_init(struct texturemanager* tm, int num_textures);
void texture_destroy(struct texturemanager* tm);

void texture_loadsheet(struct texturemanager* tm, char* filename);


#endif
