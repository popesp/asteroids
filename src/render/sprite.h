#ifndef	SPRITE
#define	SPRITE


#include	<math.h>
#include	"render.h"
#include	"texture.h"


struct texture;


struct sprite
{
	struct texture* texture;
	
	float x, y;
	float width, height;
	float rotation;
};


static inline void sprite_bufferdraw(struct sprite* sprite, float* ptr)
{
	float c, s, w, h;
	
	struct texture* t;
	
	t = sprite->texture;
	
	c = cosf(sprite->rotation);
	s = sinf(sprite->rotation);
	w = sprite->width/2.f;
	h = sprite->height/2.f;
	
	ptr[0] = sprite->x + (-w*c - -h*s);
	ptr[1] = sprite->y + (-w*s + -h*c);
	ptr[2] = t->ul;
	ptr[3] = t->vt;
	ptr += 4;
	
	ptr[0] = sprite->x + (-w*c - h*s);
	ptr[1] = sprite->y + (-w*s + h*c);
	ptr[2] = t->ul;
	ptr[3] = t->vb;
	ptr += 4;
	
	ptr[0] = sprite->x + (w*c - -h*s);
	ptr[1] = sprite->y + (w*s + -h*c);
	ptr[2] = t->ur;
	ptr[3] = t->vt;
	ptr += 4;
	
	ptr[0] = sprite->x + (w*c - -h*s);
	ptr[1] = sprite->y + (w*s + -h*c);
	ptr[2] = t->ur;
	ptr[3] = t->vt;
	ptr += 4;
	
	ptr[0] = sprite->x + (-w*c - h*s);
	ptr[1] = sprite->y + (-w*s + h*c);
	ptr[2] = t->ul;
	ptr[3] = t->vb;
	ptr += 4;
	
	ptr[0] = sprite->x + (w*c - h*s);
	ptr[1] = sprite->y + (w*s + h*c);
	ptr[2] = t->ur;
	ptr[3] = t->vb;
}


#endif
