#include "include/Game.h"


int main(int argc, char **argv){
	
	Game game = Game();
	
	game.setup();
	game.start();
	game.clean();
	
}

