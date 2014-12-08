#ifndef	RENDER
#define	RENDER


#define	RENDER_ATTRIB_POS		0
#define	RENDER_ATTRIB_COL		1
#define	RENDER_ATTRIB_NOR		2
#define	RENDER_ATTRIB_TEX		3

#define	RENDER_ATTRIBSIZE_POS	3
#define	RENDER_ATTRIBSIZE_COL	3
#define	RENDER_ATTRIBSIZE_NOR	3
#define	RENDER_ATTRIBSIZE_TEX	2

#define	RENDER_TYPE_POINTS		0
#define	RENDER_TYPE_LINES		1
#define	RENDER_TYPE_MESH		2
#define	RENDER_TYPE_TEXTURED	3

#define	RENDER_SHADER_WIREVERT	"shaders/wire.vert"
#define	RENDER_SHADER_WIREFRAG	"shaders/wire.frag"
#define	RENDER_SHADER_MESHVERT	"shaders/mesh.vert"
#define	RENDER_SHADER_MESHFRAG	"shaders/mesh.frag"

#define	RENDER_FLAGS_NONE		0x00
#define	RENDER_FLAGS_DYNAMIC	0x01


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
	int gl_wireid;
	int gl_meshid;
	int gl_textid;
};


void renderable_init(struct renderable* r, int gl_drawmode, unsigned char type, unsigned char flags);
void renderable_allocate(struct renderable* r, int num_verts);
void renderable_sendbuffer(struct renderable* r);
void renderable_render(struct renderable* r, float* transform);

int renderer_initshaders(struct renderer* r);


#endif
