#include	"game.h"

#include	<GL/glew.h>
#include	<GL/glfw3.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	"render/render.h"
#include	"render/sprite.h"
#include	"render/window2d.h"


static void resize(GLFWwindow* window, int width, int height);
static void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
static void cursor(GLFWwindow* window, double x, double y);
static void mouse(GLFWwindow* window, int button, int action, int mods);
static void scroll(GLFWwindow* window, double xoffset, double yoffset);
static void update(struct game* game);
static void render(struct game* game);


static void resize(GLFWwindow* window, int width, int height)
{
	struct game* game;
	
	game = (struct game*)glfwGetWindowUserPointer(window);
	
	window_resize(&game->window, width, height);
	glViewport(0, 0, width, height);
}

static void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	struct game* game;
	
	game = (struct game*)glfwGetWindowUserPointer(window);
	
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				game->flags |= GAME_FLAG_TERMINATED;
				break;
			
			case GLFW_KEY_W:
				game->input.w = 1;
				break;
			
			case GLFW_KEY_A:
				game->input.a = 1;
				break;
			
			case GLFW_KEY_S:
				game->input.s = 1;
				break;
			
			case GLFW_KEY_D:
				game->input.d = 1;
				break;
			
			default:
				break;
		}
	} else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
			case GLFW_KEY_W:
				game->input.w = 0;
				break;
			
			case GLFW_KEY_A:
				game->input.a = 0;
				break;
			
			case GLFW_KEY_S:
				game->input.s = 0;
				break;
			
			case GLFW_KEY_D:
				game->input.d = 0;
				break;
			
			default:
				break;
		}
	}
}

static void cursor(GLFWwindow* window, double x, double y)
{
	struct game* game;
	
	game = (struct game*)glfwGetWindowUserPointer(window);
	
	// process mouse movement
}

static void mouse(GLFWwindow* window, int button, int action, int mods)
{
	struct game* game;
	
	game = (struct game*)glfwGetWindowUserPointer(window);
	
	// process mouse buttons
}

static void scroll(GLFWwindow* window, double xoffset, double yoffset)
{
	struct game* game;
	
	game = (struct game*)glfwGetWindowUserPointer(window);
	
	// process mouse scroll
}

static void update(struct game* game)
{
	int i;
	
	// check for callback events
	glfwPollEvents();
	
	// handle input
	if (game->input.w)
		game->py -= 1.f;
	if (game->input.a)
		game->px -= 1.f;
	if (game->input.s)
		game->py += 1.f;
	if (game->input.d)
		game->px += 1.f;
	
	game->sprites[0].x = game->px;
	game->sprites[0].y = game->py;
	game->sprites[0].rotation += 0.1f;
	
	// update sprite buffer
	sprite_bufferdraw(game->sprites + 0, game->r_sprites.buffer);
	
	// send buffer to opengl
	renderable_sendbuffer(&game->r_sprites);
	
	if (glfwWindowShouldClose(game->window.w))
		game->flags |= GAME_FLAG_TERMINATED;
}

static void render(struct game* game)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	// render objects
	renderable_render(&game->r_sprites, game->window.projection, 6);
	
	glfwSwapBuffers(game->window.w);
}


int game_startup(struct game* game)
{
	int error;
	int i;
	
	// initialize GLFW
	if (glfwInit() != GL_TRUE)
		return 0;
	
	// initialize window object
	window_init(&game->window, GAME_DEFAULT_WIDTH, GAME_DEFAULT_HEIGHT);
	
	// ensure a compatible context
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	
	// create window handle
	if ((game->window.w = glfwCreateWindow(game->window.width, game->window.height, GAME_TITLE, NULL, NULL)) == NULL)
		return 0;
	
	// move to default screen position
	glfwSetWindowPos(game->window.w, GAME_DEFAULT_X, GAME_DEFAULT_Y);
	glfwShowWindow(game->window.w);
	
	// make window's opengl context current
	glfwMakeContextCurrent(game->window.w);
	
	// initialize GLEW
	glewExperimental = GL_TRUE;
	if ((error = glewInit()) != GLEW_OK)
		return 0;
	
	// enable vsync
	glfwSwapInterval(1);
	
	// register game object as user pointer for callback functions
	glfwSetWindowUserPointer(game->window.w, (void*)game);
	
	// configure opengl
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(GAME_CLEARCOLOR, 1.f);
	
	// initialize gl viewport
	glViewport(0, 0, game->window.width, game->window.height);
	
	// set callback functions for the window
	glfwSetWindowSizeCallback(game->window.w, &resize);
	glfwSetKeyCallback(game->window.w, &keyboard);
	glfwSetCursorPosCallback(game->window.w, &cursor);
	glfwSetMouseButtonCallback(game->window.w, &mouse);
	glfwSetScrollCallback(game->window.w, &scroll);
	
	// initialize renderer
	if (!renderer_init(&game->renderer))
		return 0;
	
	// initialize texture manager with 1 texture
	texture_init(&game->tm, 1);
	texture_loadsheet(&game->tm, GAME_FILE_SPRITESHEET);
	game->tm.textures[0].ul = game->tm.textures[0].vt = 0.f;
	game->tm.textures[0].ur = game->tm.textures[0].vb = 1.f;
	
	// initialize the renderable objects
	renderable_init(&game->r_sprites, GL_TRIANGLES, RENDER_TYPE_TXTRD, RENDER_FLAG_DYNAMIC);
	
	// allocate buffers for the renderable objects
	renderable_allocate(&game->r_sprites, GAME_MAX_SPRITES*6);
	
	game->input.w = 0;
	game->input.a = 0;
	game->input.s = 0;
	game->input.d = 0;
	
	game->num_sprites = 1;
	game->sprites = calloc(sizeof(struct sprite), game->num_sprites);
	
	// initialize player attributes
	game->pw = 32.f;
	game->ph = 32.f;
	game->px = (float)GAME_DEFAULT_WIDTH*0.5f;
	game->py = (float)GAME_DEFAULT_HEIGHT*0.5f;
	
	game->sprites[0].texture = game->tm.textures + 0;
	game->sprites[0].width = game->pw*2.f;
	game->sprites[0].height = game->ph*2.f;
	game->sprites[0].rotation = 0.f;
	
	return 1;
}

void game_mainloop(struct game* game)
{
	double time, timer, elapsed;
	unsigned fps, ups;
	
	time = 0.;
	fps = ups = 0u;
	
	// initialize timer
	glfwSetTime(0.);
	
	// loop until terminated
	while (!(game->flags&GAME_FLAG_TERMINATED))
	{
		// get elapsed time for current iteration
		elapsed = glfwGetTime();
		glfwSetTime(0.);
		
		time += elapsed;
		timer += elapsed;
		
		// update as much as necessary
		while (time >= GAME_SPU)
		{
			update(game);
			ups++;
			time -= GAME_SPU;
		}
		
		// every second, reset fps and ups counters
		while (timer >= 1.)
		{
			timer -= 1.;
			fps = ups = 0u;
		}
		
		// render as frequently as possible
		render(game);
		fps++;
	}
}

void game_shutdown(struct game* game)
{
	texture_destroy(&game->tm);
	renderable_deallocate(&game->r_sprites);
	free(game->sprites);
	
	glfwDestroyWindow(game->window.w);
	glfwTerminate();
}
