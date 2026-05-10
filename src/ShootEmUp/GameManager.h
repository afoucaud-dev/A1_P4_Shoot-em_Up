#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "Obstacle.h"
#include "Character.h"
#include "Image.h"
#include "Car.h"
#include "Helico.h"
#include "Moto.h"
#include "Hero.h"
#include <ctime>
#include "TankBoss.h"

#include "InputManager.h"


class GameManager
{
private:
	int score = 0;

public:
	GameManager();
	void TargetEnnemy(std::vector<Helico>* allhelico, std::vector<Character>* allrockets);
	int Loop();
};