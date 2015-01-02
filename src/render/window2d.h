#ifndef	WINDOW
#define	WINDOW


#include	"../math/mat4f.h"


#define	WINDOW_NEAR	-1.f
#define	WINDOW_FAR	1.f


struct GLFWwindow;


struct window
{
	struct GLFWwindow* w;
	
	int width, height;
	
	float projection[16];
};


/*	Resize a window
	param:	win		window object to resize (modified)
	param:	width	new width
	param:	height	new height
*/
static inline void window_resize(struct window* win, int width, int height)
{
	win->width = width;
	win->height = height;
	
	// update projection matrix
	mat4f_ortho(win->projection, 0, (float)win->width, (float)win->height, 0, WINDOW_NEAR, WINDOW_FAR);
}


/*	Initialize window with default settings
	param:	win		window object to initialize (modified)
	param:	width	window width
	param:	height	window height
*/
static inline void window_init(struct window* win, int width, int height)
{
	window_resize(win, width, height);
}


#endif
