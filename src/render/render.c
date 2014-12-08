#include	"render.h"

#include	<GL/glut.h>
#include	"../app.h"
#include	"../global.h"
#include	"shader.h"


#include	<stdio.h>


static int vertsize[4] = {
	RENDER_ATTRIBSIZE_POS + RENDER_ATTRIBSIZE_COL,							// points
	RENDER_ATTRIBSIZE_POS + RENDER_ATTRIBSIZE_COL,							// lines
	RENDER_ATTRIBSIZE_POS + RENDER_ATTRIBSIZE_COL,							// mesh
	RENDER_ATTRIBSIZE_POS + RENDER_ATTRIBSIZE_NOR + RENDER_ATTRIBSIZE_TEX};	// textured

static int shader[4];

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
		case RENDER_TYPE_POINTS:
		case RENDER_TYPE_LINES:
			attrib(RENDER_ATTRIB_POS, RENDER_ATTRIBSIZE_POS, vertsize[type], 0);
			attrib(RENDER_ATTRIB_COL, RENDER_ATTRIBSIZE_COL, vertsize[type], RENDER_ATTRIBSIZE_POS);
			break;
		
		case RENDER_TYPE_MESH:
			attrib(RENDER_ATTRIB_POS, RENDER_ATTRIBSIZE_POS, vertsize[type], 0);
			attrib(RENDER_ATTRIB_COL, RENDER_ATTRIBSIZE_COL, vertsize[type], RENDER_ATTRIBSIZE_POS);
			break;
		
		case RENDER_TYPE_TEXTURED:
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


int renderer_initshaders(struct renderer* r)
{
	int wirevert, wirefrag;
	int meshvert, meshfrag;
	
	// initialize shaders
	if (!(wirevert = shader_create(RENDER_SHADER_WIREVERT, SHADER_VERTEX)))
		return FAILURE;
	if (!(wirefrag = shader_create(RENDER_SHADER_WIREFRAG, SHADER_FRAGMENT)))
		return FAILURE;
	if (!(meshvert = shader_create(RENDER_SHADER_MESHVERT, SHADER_VERTEX)))
		return FAILURE;
	if (!(meshfrag = shader_create(RENDER_SHADER_MESHFRAG, SHADER_FRAGMENT)))
		return FAILURE;
	
	// link programs
	if (!(r->gl_wireid = shader_program(wirevert, wirefrag)))
		return FAILURE;
	if (!(r->gl_meshid = shader_program(meshvert, meshfrag)))
		return FAILURE;
	
	// bind attribute locations
	glBindAttribLocation(r->gl_wireid, RENDER_ATTRIB_POS, "vertpos");
	glBindAttribLocation(r->gl_wireid, RENDER_ATTRIB_COL, "vertcol");
	
	glBindAttribLocation(r->gl_meshid, RENDER_ATTRIB_POS, "vertpos");
	glBindAttribLocation(r->gl_meshid, RENDER_ATTRIB_NOR, "vertcol");
	
	// flag shaders for deletion
	shader_delete(wirevert);
	shader_delete(wirefrag);
	shader_delete(meshvert);
	shader_delete(meshfrag);
	
	// assign program ID's to render types
	shader[RENDER_TYPE_POINTS] = r->gl_wireid;
	shader[RENDER_TYPE_LINES] = r->gl_wireid;
	shader[RENDER_TYPE_MESH] = r->gl_meshid;
}
