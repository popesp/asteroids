#ifndef	SHADER_H
#define	SHADER_H


#define	SHADER_VERTEX	0
#define	SHADER_FRAGMENT	1


int shader_create(char* filename, unsigned char type);
int shader_program(int vertex, int fragment);
int shader_link(int program);
void shader_delete(int id);


#endif
