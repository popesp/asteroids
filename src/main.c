#include	"game.h"


int main(int argc, char** argv)
{
	struct game game;
	
	game_startup(&game);
	game_mainloop(&game);
	game_shutdown(&game);
	
	return 0;
}
