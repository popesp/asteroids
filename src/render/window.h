#ifndef	WINDOW
#define	WINDOW


#include	<math.h>
#include	"../math/mat4f.h"


#define	WINDOW_DEFAULT_VIEWANGLE	90.f
#define	WINDOW_DEFAULT_NEAR			0.01f
#define	WINDOW_DEFAULT_FAR			1000.f


struct window
{
	int glut_id;
	
	int width, height;
	
	float near, far;
	float ratio;
	
	float projection[16];
};


/*	Set the viewing angle for a window
	param:	win		window of which to change viewing angle (modified) (assumed near clipping distance is defined)
	param:	angle	angle in degrees
*/
static inline void window_viewangle(struct window* win, float angle)
{
	win->ratio = win->near * tanf(M_PI * angle / 360.f);
}

/*	Update the projection matrix for a window
	param:	win		window object to update (modified)
*/
static inline void window_updateprojection(struct window* win)
{
	float min;
	
	if (win->width < win->height)
	{
		min = (float)win->width/(float)win->height;
		mat4f_frustum(win->projection, -win->ratio*min, win->ratio*min, -win->ratio, win->ratio, win->near, win->far);
	} else
	{
		min = (float)win->height/(float)win->width;
		mat4f_frustum(win->projection, -win->ratio, win->ratio, -win->ratio*min, win->ratio*min, win->near, win->far);
	}
}

/*	Resize a window
	param:	win		window object to resize (modified)
	param:	width	new width
	param:	height	new height
*/
static inline void window_resize(struct window* win, int width, int height)
{
	win->width = width;
	win->height = height;
	
	window_updateprojection(win);
}


/*	Initialize window with default settings
	param:	win		window object to initialize (modified)
	param:	width	window width
	param:	height	window height
*/
static inline void window_init(struct window* win, int width, int height)
{
	win->near = WINDOW_DEFAULT_NEAR;
	win->far = WINDOW_DEFAULT_FAR;
	
	window_viewangle(win, WINDOW_DEFAULT_VIEWANGLE);
	
	window_resize(win, width, height);
}


#endif
