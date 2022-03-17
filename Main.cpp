#include "Main.h"

DirectXComponent* dxc;
Game* game;


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
	dxc = new DirectXComponent;
	game = new Game;
	if (game != nullptr)
	{
		if (SUCCEEDED(dxc->Initialize(hInstance)) && SUCCEEDED(game->Initialize(dxc)))
		{
			game->Loop(dxc);
		}
		game->Shutdown();
		SAFE_DELETE(game);
		SAFE_DELETE(dxc);
	}
	return 0;
}


Main::Main()
{
}

Main::~Main()
{
}
