#include	"game.h"


int main(int argc, char** argv)
{
	struct game game;
	
	(void)argc;
	(void)argv;
	
	game_startup(&game);
	game_mainloop(&game);
	game_shutdown(&game);
	
	return 0;
}
