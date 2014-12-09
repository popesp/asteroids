#ifndef	GAME
#define	GAME


#include	"render/window.h"
#include	"render/render.h"


#define	GAME_DEFAULT_WIDTH		600
#define	GAME_DEFAULT_HEIGHT		400
#define	GAME_DEFAULT_X			100
#define	GAME_DEFAULT_Y			100

#define	GAME_CLEARCOLOR			0.f, 0.1f, 0.1f

#define	GAME_TITLE				"Asteroids"

#define	GAME_KEY_ESC			27

#define	GAME_FLAG_INIT			0x00
#define	GAME_FLAG_TERMINATED	0x01


struct game
{
	struct window window;
	struct renderer renderer;
	
	unsigned char flags;
};


int game_startup(struct game* game);
void game_mainloop(struct game* game);
void game_shutdown(struct game* game);


#endif
