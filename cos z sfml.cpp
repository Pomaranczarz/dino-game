#include <iostream>
#include "dino_game.h"

int main()
{
	dino_game gra;

	while (gra.is_good())
	{
		gra.update();
	}
}
