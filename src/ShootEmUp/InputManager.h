#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <map>


class InputManager
{
	struct State
	{
		bool isDown;
		bool isHeld;
		bool isUp;
	};

	State m_states[SDL_NUM_SCANCODES];

private:
	InputManager()
	{
		std::memset(m_states, 0, sizeof(State) * SDL_NUM_SCANCODES);
	}

public:
	static InputManager* Get()
	{
		static InputManager instance;
		return &instance;
	}

	void Update()
	{
		for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
		{
			if (m_states[i].isDown)
				m_states[i].isHeld = true;

			if (m_states[i].isUp)
				m_states[i].isHeld = false;

			m_states[i].isDown = false;
			m_states[i].isUp = false;
		}

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
			{
				if (event.key.repeat)
					break;

				m_states[event.key.keysym.scancode].isDown = true;

				break;
			}
			case SDL_KEYUP:
			{
				m_states[event.key.keysym.scancode].isUp = true;

				break;
			}
			}
		}
	}

	bool IsDown(SDL_KeyCode key)
	{
		SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
		return m_states[scancode].isDown;
	}

	bool IsHeld(SDL_KeyCode key)
	{
		SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
		return m_states[scancode].isHeld;
	}

	bool IsUp(SDL_KeyCode key)
	{
		SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
		return m_states[scancode].isUp;
	}
};
