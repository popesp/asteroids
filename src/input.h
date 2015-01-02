#ifndef	INPUT
#define	INPUT


struct input
{
	unsigned char w, a, s, d;
};


static void input_init(struct input* i)
{
	i->w = 0;
	i->a = 0;
	i->s = 0;
	i->d = 0;
}


#endif
