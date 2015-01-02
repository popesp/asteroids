#ifndef	GAME
#define	GAME


#include	"render/window2d.h"
#include	"render/render.h"
#include	"render/texture.h"


#define	GAME_DEFAULT_WIDTH		600
#define	GAME_DEFAULT_HEIGHT		400
#define	GAME_DEFAULT_X			100
#define	GAME_DEFAULT_Y			100

#define	GAME_TITLE				"Asteroids"

#define	GAME_UPS				60.f
#define	GAME_SPU				1.f/GAME_UPS

#define	GAME_CLEARCOLOR			0.f, 0.1f, 0.1f

#define	GAME_FILE_SPRITESHEET	"res/sprites.png"

#define	GAME_MAX_SPRITES		128

#define	GAME_FLAG_INIT			0x00
#define	GAME_FLAG_TERMINATED	0x01


struct sprite;


struct game
{
	struct window window;
	struct renderer renderer;
	struct texturemanager tm;
	
	struct renderable r_sprites;
	
	struct
	{
		unsigned char w, a, s, d;
	} input;
	
	int num_sprites;
	struct sprite* sprites;
	
	float px, py;
	float pw, ph;
	
	unsigned char flags;
};


int game_startup(struct game* game);
void game_mainloop(struct game* game);
void game_shutdown(struct game* game);


#endif
