#pragma once

#include "Image.h"
#include "SDL.h"
#include "SDL_image.h"

class Menu
{
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	Image* m_background;
	Image* m_playButton;
	Image* m_exitButton;

	int m_MouseX;
	int m_MouseY;

	bool m_isRunning;

	enum MenuState
	{
		StateMenu,
		StatePlay,
		StateExit
	};

	MenuState m_state;

public:
	Menu();
	~Menu();

	void Run();

};
