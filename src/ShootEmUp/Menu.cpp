#include "Menu.h"
#include "GameManager.h"
#include <iostream>

Menu::Menu()
{
	m_window = nullptr;
	m_renderer = nullptr;
	m_background = nullptr;
	m_playButton = nullptr;
	m_exitButton = nullptr;
	m_MouseX = 0;
	m_MouseY = 0;
	m_isRunning = false;
	m_state = StateMenu;
}

Menu::~Menu()
{
	if (m_playButton)
	{
		delete m_playButton;
	}

	if (m_exitButton)
	{
		delete m_exitButton;
	}

	if (m_background)
	{
		delete m_background;
	}

	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
	}

	if (m_window)
	{
		SDL_DestroyWindow(m_window);
	}

	SDL_Quit();
}

void Menu::Run()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		std::cout << "Error SDL2 Initialization : " << SDL_GetError() << std::endl;
		return;
	}

	m_window = SDL_CreateWindow("Menu",	SDL_WINDOWPOS_CENTERED,	SDL_WINDOWPOS_CENTERED,	WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

	if (!m_window)
	{
		std::cout << "Error window creation" << std::endl;
		return;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (!m_renderer)
	{
		std::cout << "Error renderer creation" << std::endl;
		return;
	}

	m_background = new Image(m_renderer, "..\\..\\Menu.bmp");
	m_background->Resize(WIDTH, HEIGHT);
	m_background->SetPosition(0, 0, 0, 0);

	m_playButton = new Image(m_renderer, "..\\..\\Play.png");
	m_playButton->SetPosition(CENTER_X, CENTER_Y, 0.5f, 0.5f);

	m_exitButton = new Image(m_renderer, "..\\..\\Exit.png");
	m_exitButton->SetPosition(CENTER_X, CENTER_Y + CENTER_Y / 2, 0.5f, 0.5f);

	m_isRunning = true;

	while (m_isRunning)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				m_isRunning = false;
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					int mouseX = event.button.x;
					int mouseY = event.button.y;

					if (m_playButton->ContainsPoint(mouseX, mouseY))
					{
						GameManager game;
						game.Loop();
						m_isRunning = false;
					}
					else if (m_exitButton->ContainsPoint(mouseX, mouseY))
					{
						m_isRunning = false;
					}
				}
			}
		}


		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_renderer);

		m_background->Draw(m_renderer);
		m_playButton->Draw(m_renderer);
		m_exitButton->Draw(m_renderer);

		SDL_RenderPresent(m_renderer);

		SDL_Delay(16); 
	}
}
