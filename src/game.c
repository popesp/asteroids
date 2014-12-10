#include	"game.h"

#include	<GL/glew.h>
#include	<GL/glfw3.h>
#include	"render/render.h"
#include	"render/window.h"


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
	
	// process keyboard input
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
	// check for callback events
	glfwPollEvents();
	
	// update
	
	if (glfwWindowShouldClose(game->window.w))
		game->flags |= GAME_FLAG_TERMINATED;
}

static void render(struct game* game)
{
	float transform[16], worldmv[16], inverse[16];
	float eyepos[3];
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	// render objects
	
	glfwSwapBuffers(game->window.w);
}


int game_startup(struct game* game)
{
	// initialize GLFW
	if (glfwInit() != GL_TRUE)
		return 0;
	
	// initialize window object
	window_init(&game->window, GAME_DEFAULT_WIDTH, GAME_DEFAULT_HEIGHT);
	
	// ensure a compatible context
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	
	// create window handle
	if ((game->window.w = glfwCreateWindow(game->window.width, game->window.height, GAME_TITLE, NULL, NULL)) == NULL)
		return 0;
	
	// move to default screen position
	glfwSetWindowPos(game->window.w, GAME_DEFAULT_X, GAME_DEFAULT_Y);
	glfwShowWindow(game->window.w);
	
	// make window's opengl context current
	glfwMakeContextCurrent(game->window.w);
	
	// enable vsync
	glfwSwapInterval(1);
	
	// register game object as user pointer for callback functions
	glfwSetWindowUserPointer(game->window.w, (void*)game);
	
	// configure opengl
	glEnable(GL_DEPTH_TEST);
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
	
	// initialize the renderable objects
	
	// allocate buffers for the renderable objects
	
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
	glfwDestroyWindow(game->window.w);
	glfwTerminate();
}
