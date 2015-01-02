#ifndef	RENDER
#define	RENDER


#define	RENDER_ATTRIB_POS		0
#define	RENDER_ATTRIB_COL		1
#define	RENDER_ATTRIB_TEX		2

#define	RENDER_ATTRIBSIZE_POS	2
#define	RENDER_ATTRIBSIZE_COL	3
#define	RENDER_ATTRIBSIZE_TEX	2

#define	RENDER_TYPE_SOLID		0
#define	RENDER_TYPE_TXTRD		1

#define	RENDER_SHADER_SOLIDVERT	"shaders/solid.vert"
#define	RENDER_SHADER_SOLIDFRAG	"shaders/solid.frag"
#define	RENDER_SHADER_TXTRDVERT	"shaders/textured2d.vert"
#define	RENDER_SHADER_TXTRDFRAG	"shaders/textured.frag"

#define	RENDER_FLAG_NONE		0x00
#define	RENDER_FLAG_DYNAMIC	0x01

int shader[2];
struct renderable
{
	int gl_drawmode;
	int gl_vao;
	int gl_buf;
	
	int num_verts;
	float* buffer;
	
	void (* uniforms)();
	
	unsigned char type;
	unsigned char flags;
};


struct renderer
{
	int id_glsolid;
	int id_gltxtrd;
};


void renderable_init(struct renderable* r, int gl_drawmode, unsigned char type, unsigned char flags);
void renderable_allocate(struct renderable* r, int num_verts);
void renderable_deallocate(struct renderable* r);
void renderable_sendbuffer(struct renderable* r);
void renderable_render(struct renderable* r, float* transform, int num_verts);

int renderer_init(struct renderer* r);


#endif
