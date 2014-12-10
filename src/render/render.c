#include	"render.h"

#include	<stdlib.h>
#include	<GL/glew.h>
#include	<GL/glfw3.h>
#include	"shader.h"


static int vertsize[2] = {
	RENDER_ATTRIBSIZE_POS + RENDER_ATTRIBSIZE_COL,							// solid
	RENDER_ATTRIBSIZE_POS + RENDER_ATTRIBSIZE_NOR + RENDER_ATTRIBSIZE_TEX};	// textured

static int shader[2];

static inline void attrib(int index, int size, int vsize, int offs)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, sizeof(float)*vsize, (void*)(sizeof(float)*offs));
}


void renderable_init(struct renderable* r, int gl_drawmode, unsigned char type, unsigned char flags)
{
	r->gl_drawmode = gl_drawmode;
	
	glGenVertexArrays(1, &r->gl_vao);
	glGenBuffers(1, &r->gl_buf);
	
	glBindVertexArray(r->gl_vao);
	glBindBuffer(GL_ARRAY_BUFFER, r->gl_buf);
	
	switch (type)
	{
		case RENDER_TYPE_SOLID:
			attrib(RENDER_ATTRIB_POS, RENDER_ATTRIBSIZE_POS, vertsize[type], 0);
			attrib(RENDER_ATTRIB_COL, RENDER_ATTRIBSIZE_COL, vertsize[type], RENDER_ATTRIBSIZE_POS);
			break;
		
		case RENDER_TYPE_TXTRD:
			attrib(RENDER_ATTRIB_POS, RENDER_ATTRIBSIZE_POS, vertsize[type], 0);
			attrib(RENDER_ATTRIB_NOR, RENDER_ATTRIBSIZE_NOR, vertsize[type], RENDER_ATTRIBSIZE_POS);
			attrib(RENDER_ATTRIB_TEX, RENDER_ATTRIBSIZE_TEX, vertsize[type], RENDER_ATTRIBSIZE_POS + RENDER_ATTRIBSIZE_NOR);
			break;
		
		default:
			break;
	}
	
	r->buffer = NULL;
	
	r->uniforms = NULL;
	
	r->type = type;
	r->flags = flags;
}

void renderable_allocate(struct renderable* r, int num_verts)
{
	glBindBuffer(GL_ARRAY_BUFFER, r->gl_buf);
	
	r->buffer = calloc(vertsize[r->type] * num_verts, sizeof(float));
	
	if (r->flags & RENDER_FLAGS_DYNAMIC)
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertsize[r->type] * num_verts, NULL, GL_DYNAMIC_DRAW);
	else
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertsize[r->type] * num_verts, NULL, GL_STATIC_DRAW);
	
	r->num_verts = num_verts;
}

void renderable_sendbuffer(struct renderable* r)
{
	glBindBuffer(GL_ARRAY_BUFFER, r->gl_buf);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * vertsize[r->type] * r->num_verts, r->buffer);
}

void renderable_render(struct renderable* r, float* transform)
{
	glUseProgram(shader[r->type]);
	glBindVertexArray(r->gl_vao);
	
	glUniformMatrix4fv(glGetUniformLocation(shader[r->type], "transform"), 1, GL_FALSE, transform);
	if (r->uniforms != NULL)
		r->uniforms();
	
	glDrawArrays(r->gl_drawmode, 0, r->num_verts);
}


int renderer_init(struct renderer* r)
{
	int solidvert, solidfrag;
	int txtrdvert, txtrdfrag;
	
	// initialize shaders
	if (!(solidvert = shader_create(RENDER_SHADER_SOLIDVERT, SHADER_VERTEX)))
		return 0;
	if (!(solidfrag = shader_create(RENDER_SHADER_SOLIDFRAG, SHADER_FRAGMENT)))
		return 0;
	if (!(txtrdvert = shader_create(RENDER_SHADER_TXTRDVERT, SHADER_VERTEX)))
		return 0;
	if (!(txtrdfrag = shader_create(RENDER_SHADER_TXTRDFRAG, SHADER_FRAGMENT)))
		return 0;
	
	// link programs
	if (!(r->gl_solidid = shader_program(solidvert, solidfrag)))
		return 0;
	if (!(r->gl_txtrdid = shader_program(txtrdvert, txtrdfrag)))
		return 0;
	
	// bind attribute locations
	glBindAttribLocation(r->gl_solidid, RENDER_ATTRIB_POS, "vertpos");
	glBindAttribLocation(r->gl_solidid, RENDER_ATTRIB_COL, "vertcol");
	
	glBindAttribLocation(r->gl_txtrdid, RENDER_ATTRIB_POS, "vertpos");
	glBindAttribLocation(r->gl_txtrdid, RENDER_ATTRIB_NOR, "vertcol");
	glBindAttribLocation(r->gl_txtrdid, RENDER_ATTRIB_TEX, "verttex");
	
	// flag shaders for deletion
	shader_delete(solidvert);
	shader_delete(solidfrag);
	shader_delete(txtrdvert);
	shader_delete(txtrdfrag);
	
	// assign program ID's to render types
	shader[RENDER_TYPE_SOLID] = r->gl_solidid;
	shader[RENDER_TYPE_TXTRD] = r->gl_txtrdid;
}
