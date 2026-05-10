#include "GameManager.h"

GameManager::GameManager()
{
}

int GenerateRandomNumber(int min, int max)
{
	return min + rand() % (max - min);
}



void GameManager::TargetEnnemy(std::vector<Helico>* allhelico, std::vector<Character>* allrockets)
{
	int dist = WIDTH * HEIGHT;

	for (int r = allrockets->size() - 1; r >= 0; r--)
	{
		if (allhelico->size() == 0)
		{
			(*allrockets)[r].NewTarget(0);
		}

		if ((*allrockets)[r].Target() >= 0)
		{
			continue;
		}

		for (int e = allhelico->size() - 1; e >= 0; e--)
		{
			int newdist = (*allrockets)[r].Proximity(&(*allhelico)[e]);
			if (newdist < dist)
			{
				(*allrockets)[r].NewTarget(e);
				dist = newdist;
			}
		}
	}
}



int GameManager::Loop()
{
	srand(time(NULL));




	std::ifstream monFichier("..\\..\\editeur_level.txt");
	if (!monFichier)
	{
		std::cout << "Fichier non trouve ou impossible a ouvrir" << std::endl;
		return 0;
	}

	std::string s;
	std::vector<std::string> maplevel;
	int newcolmax;
	int colmax = -1;

	while (getline(monFichier, s))
	{
		maplevel.push_back(s);
		newcolmax = s.size();
		if (newcolmax < colmax || colmax == -1)
		{
			colmax = newcolmax;
		}
	}

	monFichier.close();

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cout << "Erreur IMG_Init PNG: " << IMG_GetError() << std::endl;
		return 1;
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		std::cout << "Error SDL2 Initialization : " << SDL_GetError();
		return 1;
	}
	SDL_Window* window;
	SDL_Renderer* renderer;

	window = SDL_CreateWindow("Draw", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	if (window == NULL)
	{
		std::cout << "Error window creation";
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		std::cout << "Error renderer creation";
		return false;
	}

	//init
	Hero hero;
	hero.SetPosition(CENTER_X, HEIGHT - hero.GetRadius());


	Image voitureHero(renderer, "..\\..\\voiturehero.png");
	voitureHero.SetPosition(CENTER_X, HEIGHT - hero.GetRadius());

	
	Image Road1(renderer, "..\\..\\\Road.png");
	Road1.SetPosition(CENTER_X, 0, 0.5, 0);

	Image Road2(renderer, "..\\..\\Road.png");
	Road2.SetPosition(CENTER_X,-HEIGHT, 0.5, 0);

	Image Grass1(renderer, "..\\..\\Grass1.png");
	Grass1.SetPosition(0, 0, 0, 0);

	Image Grass2(renderer, "..\\..\\Grass1.png");
	Grass2.SetPosition(0, -HEIGHT, 0, 0);


	Image CarEnnemy(renderer, "..\\..\\CarEnnemy.png");
	Image MotoEnnemy(renderer, "..\\..\\Moto.png");

	std::vector<Character> allbullets;
	Image bulletHeroimage(renderer, "..\\..\\FlammeHero.png");

	Image bulletEnnemyimage(renderer, "..\\..\\FlammeEnnemy.png");

	std::vector<Character> allrockets;
	Image rocketHero(renderer, "..\\..\\rocketHero.png");
	
	Image rocketEnnemy(renderer, "..\\..\\rocketEnnemy .png");

	Image Helicopter(renderer, "..\\..\\Helico.png");

	Image civil(renderer, "..\\..\\VoitureCivil.png");

	Image GameOverImage(renderer, "..\\..\\GameOver.png");	

	Image NoImage(renderer, "..\\..\\No.png");
	
	Image TankImage(renderer, "..\\..\\tank.png");

	Image Coeur1(renderer, "..\\..\\coeur1.png");
	Image Coeur2(renderer, "..\\..\\coeur2.png");
	Image Coeur3(renderer, "..\\..\\coeur3.png"); 
	Image Coeur4(renderer, "..\\..\\coeur4.png");
	Image Coeur5(renderer, "..\\..\\coeur5.png");
	Image Coeur6(renderer, "..\\..\\coeur6.png");
	Image Coeur7(renderer, "..\\..\\coeur7.png");
	Image Coeur8(renderer, "..\\..\\coeur8.png");
	Image Coeur9(renderer, "..\\..\\coeur9.png");
	Image Coeur10(renderer, "..\\..\\coeur10.png");

	std::vector<Obstacle> allobstacle;

	std::vector<TankBoss> allboss;

	std::vector<Car> allcar;

	std::vector<Helico> allhelico;

	std::vector<Moto> allmoto;

	std::vector<Character> allbulletscar;

	std::vector<Character> allbulletshelico;

	std::vector<Character> allbulletsmoto;

	std::vector<Character> allbulletsboss;




	bool bosspattern = true;
	int latepattern = 0;

	int col = 0;

	int puissancebullet = 1;
	int puissancerocket = 2;


	int speedobstacle = 200;
	int speedRoad = 2500;
	int speedGrass = 1500;
	int speedbullet = 1000;
	int speedrocket = 500;
	int speedbulletcar = 700;
	int speedbullethelico = 700;
	int speedbulletmoto = 700;
	int speedbulletboss = 700;

	float deltaTime = 0;

	bool Victory = false;
	bool GameOver = false;
	bool boollevel = false;
	bool bulletshoot = false;
	bool rocketshoot = false;
	bool bulletcarshoot = false;
	bool bullethelicoshoot = false;
	bool bulletmotoshoot = false;
	bool bulletbossshoot = false;

	int turnlevel = 0;
	int turnbullet = 0;
	int turnbulletcar = 0;
	int turnbullethelico = 0;
	int turnbulletmoto = 0;
	int turnrocket = 0;
	int turnbulletboss = 0;

	while (true)
	{
		Uint64 start = SDL_GetTicks64();

		//EVENT
		InputManager::Get()->Update();

		if (GameOver)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			GameOverImage.SetPosition(WIDTH / 2, HEIGHT / 2, 0.5f, 0.5f);
			GameOverImage.Draw(renderer);
			NoImage.SetPosition(WIDTH / 2 - 80, HEIGHT / 1.3, 0.5f, 0.5f);
			NoImage.Draw(renderer);
			NoImage.SetPosition(WIDTH / 2 + 100, HEIGHT / 1.3, 0.5f, 0.5f);
			NoImage.Draw(renderer);



			SDL_RenderPresent(renderer);
			continue; 
		}

		if (Victory)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			Image VictoryImage(renderer, "..\\..\\WIN.png");
			VictoryImage.SetPosition(WIDTH / 2, HEIGHT / 2, 0.5f, 0.5f);
			VictoryImage.Draw(renderer);

			std::cout << "Win : Score -> " << score << std::endl;

			SDL_RenderPresent(renderer);
			continue;
		}

		//UPDATE
		if (InputManager::Get()->IsHeld(SDLK_z) || InputManager::Get()->IsHeld(SDLK_UP))
		{
			//move up
			hero.Move(0.f, -hero.GetSpeed() * deltaTime, WIDTH, HEIGHT);
			voitureHero.MoveHero(0.f, -hero.GetSpeed() * deltaTime, WIDTH, HEIGHT);

		}
		if (InputManager::Get()->IsHeld(SDLK_q) || InputManager::Get()->IsHeld(SDLK_LEFT))
		{
			//move left
			hero.Move(-hero.GetSpeed() * deltaTime, 0.f, WIDTH, HEIGHT);
			voitureHero.MoveHero(-hero.GetSpeed() * deltaTime, 0.f, WIDTH, HEIGHT);
		}
		if (InputManager::Get()->IsHeld(SDLK_s) || InputManager::Get()->IsHeld(SDLK_DOWN))
		{
			//move down
			hero.Move(0.f, hero.GetSpeed() * deltaTime, WIDTH, HEIGHT);
			voitureHero.MoveHero(0.f, hero.GetSpeed() * deltaTime, WIDTH, HEIGHT);
		}
		if (InputManager::Get()->IsHeld(SDLK_d) || InputManager::Get()->IsHeld(SDLK_RIGHT))
		{
			//move right
			hero.Move(hero.GetSpeed() * deltaTime, 0.f, WIDTH, HEIGHT);
			voitureHero.MoveHero(hero.GetSpeed() * deltaTime, 0.f, WIDTH, HEIGHT);
		}
		if (InputManager::Get()->IsHeld(SDLK_b))
		{
			//shoot
			if (bulletshoot)
			{
				allbullets.push_back(Character(10));
				allbullets[allbullets.size() - 1].SetPosition(hero.Shot('x') + hero.GetRadius(), hero.Shot('y') + hero.GetRadius());
				bulletshoot = false;
			}
		}
		if (InputManager::Get()->IsHeld(SDLK_n))
		{
			if (rocketshoot)
			{
				allrockets.push_back(Character(10));
				allrockets[allrockets.size() - 1].SetPosition(hero.Shot('x') + hero.GetRadius(), hero.Shot('y') + hero.GetRadius());
				rocketshoot = false;
			}
		}


		if (boollevel)
		{
			for (int row = 0; row <= 3; row++)
			{
				int pos;
				int posprecise = WIDTH / 4 / 2;
				switch (row)
				{
				case 0:
					pos = posprecise * 2;
					break;
				case 1:
					pos = posprecise * 3.4;
					break;
				case 2:
					pos = posprecise * 4.7;
					break;
				case 3:
					pos = posprecise * 6.1;
					break;
				}
				switch (maplevel[row][col])
				{
				case 'C':
					allcar.push_back(Car());
					allcar[allcar.size() - 1].SetPosition(pos, 0);
					break;
				case 'H':
					allhelico.push_back(Helico());
					allhelico[allhelico.size() - 1].SetPosition(pos, 0);
					break;
				case 'M':
					allmoto.push_back(Moto());
					allmoto[allmoto.size() - 1].SetPosition(pos, 0);
					break;
				case 'O':
					allobstacle.push_back(Obstacle());
					allobstacle[allobstacle.size() - 1].SetPosition(pos, 0);
					break;
				case 'T':
					allboss.push_back(TankBoss());
					allboss[allboss.size() - 1].SetPosition(pos, 0);
					break;
				}
			}

			col++;
			boollevel = false;
		}






		if (boollevel == false)
		{
			turnlevel++;
			if (turnlevel == TARGET_FPS && col <= colmax)
			{
				boollevel = true;
				turnlevel = 0;
			}
		}




		if (bulletcarshoot == false)
		{
			turnbulletcar++;
			if (turnbulletcar == TARGET_FPS * 2)
			{
				bulletcarshoot = true;
				turnbulletcar = 0;
			}
		}

		if (bullethelicoshoot == false)
		{
			turnbullethelico++;
			if (turnbullethelico == TARGET_FPS * 2)
			{
				bullethelicoshoot = true;
				turnbullethelico = 0;
			}
		}

		if (bulletmotoshoot == false)
		{
			turnbulletmoto++;
			if (turnbulletmoto == TARGET_FPS * 2)
			{
				bulletmotoshoot = true;
				turnbulletmoto = 0;
			}
		}

		if (bulletshoot == false)
		{
			turnbullet++;
			if (turnbullet == TARGET_FPS / 4)
			{
				bulletshoot = true;
				turnbullet = 0;
			}
		}


		if (rocketshoot == false)
		{
			turnrocket++;
			if (turnrocket == TARGET_FPS * 1.5)
			{
				rocketshoot = true;
				turnrocket = 0;
			}
		}

		if (bulletbossshoot == false)
		{
			turnbulletboss++;
			if (turnbulletboss == TARGET_FPS / 5)
			{
				bulletbossshoot = true;
				turnbulletboss = 0;
			}
		}


		Road1.BasiqueMove(0.f, speedRoad * deltaTime);

		if (Road1.GetPosition(0.f, 0.f).y >= HEIGHT)
		{
			Road1.SetPosition(WIDTH / 2, -HEIGHT, 0.5f, 0.f);
		}


		Road2.BasiqueMove(0.f, speedRoad* deltaTime);

		if (Road2.GetPosition(0.f, 0.f).y >= HEIGHT)
		{
			Road2.SetPosition(WIDTH / 2, -HEIGHT, 0.5f, 0.f);
		}

		Grass1.BasiqueMove(0.f, speedGrass* deltaTime);

		if (Grass1.GetPosition(0.f, 0.f).y >= HEIGHT)
		{
			Grass1.SetPosition(0, -HEIGHT, 0.f, 0.f);
		}


		Grass2.BasiqueMove(0.f, speedGrass* deltaTime);

		if (Grass2.GetPosition(0.f, 0.f).y >= HEIGHT)
		{
			Grass2.SetPosition(0, -HEIGHT, 0.f, 0.f);
		}


		//DRAW

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		Grass1.Draw(renderer);
		Grass2.Draw(renderer);

		Road1.Draw(renderer);
		Road2.Draw(renderer);



		for (int i = allobstacle.size() - 1; i >= 0; i--)
		{
			bool Draw = allobstacle[i].ManageObstacle(deltaTime, &allobstacle, i, hero, &score);

			if (Draw)
			{
				continue;
			}

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
			auto pos = allobstacle[i].GetPosition(0.5f, 0.5f);
			civil.SetPosition(pos.x, pos.y, 0.5f, 0.5f);
			civil.Draw(renderer);
		}


		for (int i = allcar.size() - 1; i >= 0; i--)
		{
			if (bulletcarshoot)
			{
				allbulletscar.push_back(Character(15));
				allbulletscar[allbulletscar.size() - 1].SetPosition(allcar[i].Shot('x') + allcar[i].GetRadius(), allcar[i].Shot('y') + allcar[i].GetRadius());
				if (i == 0)
				{
					bulletcarshoot = false;
				}
			}

			bool Draw = allcar[i].ManageCar(deltaTime, &allcar, i, &score);

			if (Draw)
			{
				continue;
			}

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			auto pos = allcar[i].GetPosition(0.5f, 0.5f);
			CarEnnemy.SetPosition(pos.x, pos.y, 0.5f, 0.5f);//image voiture
			CarEnnemy.Draw(renderer);
		}

		for (int i = allmoto.size() - 1; i >= 0; i--)
		{
			if (bulletmotoshoot)
			{
				allbulletsmoto.push_back(Character(15));
				allbulletsmoto[allbulletsmoto.size() - 1].SetPosition(allmoto[i].Shot('x') + allmoto[i].GetRadius(), allmoto[i].Shot('y') + allmoto[i].GetRadius());
				if (i == 0)
				{
					bulletmotoshoot = false;
				}
			}

			bool Draw = allmoto[i].ManageMoto(deltaTime, &allmoto, i, &score);

			if (Draw)
			{
				continue;
			}

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			auto pos = allmoto[i].GetPosition(0.5f, 0.5f);
			MotoEnnemy.SetPosition(pos.x, pos.y, 0.5f, 0.5f); //image moto
			MotoEnnemy.Draw(renderer);
		}

		for (int i = allboss.size() - 1; i >= 0; i--)
		{
			if (bulletbossshoot && latepattern >= 0)
			{
				allbulletsboss.push_back(Character(10));
				allbulletsboss[allbulletsboss.size() - 1].SetPosition(allboss[i].Shot('x') + allboss[i].GetRadius(), allboss[i].Shot('y') + allboss[i].GetRadius());
				if (i == 0)
				{
					bulletbossshoot = false;
				}
			}

			int Draw = 0;


			if (bosspattern)
			{
				Draw = allboss[i].Manage1Boss(deltaTime, &allboss, i);
			}

			if (!bosspattern)
			{
				Draw = allboss[i].Manage2Boss(deltaTime, &allboss, i, &hero);
				std::cout << hero.IsAlive() << std::endl;
			}

			if (Draw == 1)
			{
				Victory = true;

				continue;
			}

			if (Draw == 2)
			{
				bosspattern = !bosspattern;
				latepattern = 0;
			}

			if (Draw == 3)
			{
				latepattern = -1;
			}


			switch (allboss[i].IsAlive())
			{
			case 1:
				Coeur1.SetPosition(WIDTH - 110, 10, 0, 0);
				Coeur1.Draw(renderer);
				break;
			case 2:
				Coeur2.SetPosition(WIDTH - 110, 10, 0, 0);
				Coeur2.Draw(renderer);
				break;
			case 3:
				Coeur3.SetPosition(WIDTH - 110, 10, 0, 0);
				Coeur3.Draw(renderer);
				break;
			case 4:
				Coeur4.SetPosition(WIDTH - 110, 10, 0, 0);
				Coeur4.Draw(renderer);
				break;
			case 5:
				Coeur5.SetPosition(WIDTH - 110, 10, 0, 0);
				Coeur5.Draw(renderer);
				break;
			case 6:
				Coeur6.SetPosition(WIDTH - 110, 10, 0, 0);
				Coeur6.Draw(renderer);
				break;
			case 7:
				Coeur7.SetPosition(WIDTH - 110, 10, 0, 0);
				Coeur7.Draw(renderer);
				break;
			case 8:
				Coeur8.SetPosition(WIDTH - 110, 10, 0, 0);
				Coeur8.Draw(renderer);
				break;
			case 9:
				Coeur9.SetPosition(WIDTH - 110, 10, 0, 0);
				Coeur9.Draw(renderer);
				break;
			case 10:
				Coeur10.SetPosition(WIDTH - 110, 10, 0, 0);
				Coeur10.Draw(renderer);
				break;
			default:
				break;
			}



			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			auto pos = allboss[i].GetPosition(0.5f, 0.5f);
			TankImage.SetPosition(pos.x, pos.y, 0.5f, 0.5f); //image Tank
			TankImage.Draw(renderer);
		}

		bool erasebullet = false;

		for (int i = allbulletsboss.size() - 1; i >= 0; i--)
		{
			erasebullet = false;

			allbulletsboss[i].BasiqueMove(0.f, speedbulletboss * deltaTime);


			if (allbulletsboss[i].IsColliding(&hero))
			{
				hero.shot(puissancebullet);

				allbulletsboss.erase(allbulletsboss.begin() + i);
				continue;
			}

			for (int o = allobstacle.size() - 1; o >= 0; o--)
			{
				if (allbulletsboss.size() == 0)
				{
					continue;
				}

				if (allbulletsboss[i].IsColliding(&allobstacle[o]))
				{
					erasebullet = true;
				}
			}
			if (erasebullet)
			{
				continue;
			}

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			auto pos = allbulletsboss[i].GetPosition(0.5f, 0.5f);
			rocketEnnemy.SetPosition(pos.x, pos.y, 0.5f, 0.5f);
			rocketEnnemy.Draw(renderer);

		}

		for (int i = allbulletscar.size() - 1; i >= 0; i--)
		{
			erasebullet = false;

			allbulletscar[i].BasiqueMove(0.f, speedbulletcar * deltaTime);
			if (allbulletscar[i].GetPosition(0.f, 1.f).y > HEIGHT)
			{
				allbulletscar.erase(allbulletscar.begin() + i);
				continue;
			}

			if (allbulletscar[i].IsColliding(&hero))
			{
				hero.shot(puissancebullet);

				allbulletscar.erase(allbulletscar.begin() + i);
				continue;
			}

			for (int o = allobstacle.size() - 1; o >= 0; o--)
			{
				if (allbulletscar.size() == 0)
				{
					continue;
				}

				if (allbulletscar[i].IsColliding(&allobstacle[o]))
				{
					erasebullet = true;
				}
			}


			if (erasebullet)
			{
				continue;
			}


			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			//allbulletscar[i].Draw(renderer);
			auto pos = allbulletscar[i].GetPosition(0.5f, 0.5f);
			bulletEnnemyimage.SetPosition(pos.x, pos.y, 0.5f, 0.5f);
			bulletEnnemyimage.Draw(renderer);

		}




		for (int i = allbulletshelico.size() - 1; i >= 0; i--)
		{
			erasebullet = false;

			allbulletshelico[i].BasiqueMove(0.f, speedbullethelico * deltaTime);
			if (allbulletshelico[i].GetPosition(0.f, 1.f).y > HEIGHT)
			{
				allbulletshelico.erase(allbulletshelico.begin() + i);
				continue;
			}

			if (allbulletshelico[i].IsColliding(&hero))
			{
				hero.shot(puissancerocket);

				allbulletshelico.erase(allbulletshelico.begin() + i);
				continue;
			}


			for (int o = allobstacle.size() - 1; o >= 0; o--)
			{
				if (allbulletshelico.size() == 0)
				{
					continue;
				}

				if (allbulletshelico[i].IsColliding(&allobstacle[o]))
				{
					erasebullet = true;
				}
			}


			if (erasebullet)
			{
				continue;
			}


			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			auto pos = allbulletshelico[i].GetPosition(0.5f, 0.5f);
			rocketEnnemy.SetPosition(pos.x, pos.y, 0.5f, 0.5f); 
			rocketEnnemy.Draw(renderer);

		}




		for (int i = allbulletsmoto.size() - 1; i >= 0; i--)
		{
			erasebullet = false;

			allbulletsmoto[i].BasiqueMove(0.f, speedbulletmoto * deltaTime);
			if (allbulletsmoto[i].GetPosition(0.f, 1.f).y > HEIGHT)
			{
				allbulletsmoto.erase(allbulletsmoto.begin() + i);
				continue;
			}

			if (allbulletsmoto[i].IsColliding(&hero))
			{
				hero.shot(puissancebullet);

				allbulletsmoto.erase(allbulletsmoto.begin() + i);
				continue;
			}


			for (int o = allobstacle.size() - 1; o >= 0; o--)
			{
				if (allbulletsmoto.size() == 0)
				{
					continue;
				}

				if (allbulletsmoto[i].IsColliding(&allobstacle[o]))
				{
					erasebullet = true;
				}
			}


			if (erasebullet)
			{
				continue;
			}


			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			auto pos = allbulletsmoto[i].GetPosition(0.5f, 0.5f);
			bulletEnnemyimage.SetPosition(pos.x, pos.y, 0.5f, 0.5f);
			bulletEnnemyimage.Draw(renderer);

		}

		for (int i = allbullets.size() - 1; i >= 0; i--)
		{
			erasebullet = false;


			if (!allboss.empty())
			{
				for (int e = allboss.size() - 1; e >= 0; e--)
				{
					if (allbullets[i].IsColliding(&allboss[e]))
					{
						allboss[e].shot(puissancebullet);

						allbullets.erase(allbullets.begin() + i);
						erasebullet = true;
						break;
					}
				}
			}


			if (erasebullet)
				continue;


			if (!allmoto.empty())
			{
				for (int e = allmoto.size() - 1; e >= 0; e--)
				{
					if (allbullets[i].IsColliding(&allmoto[e]))
					{
						allmoto[e].shot(puissancebullet);

						allbullets.erase(allbullets.begin() + i);
						erasebullet = true;
						break;
					}
				}
			}


			if (erasebullet)
				continue;


			if (!allcar.empty())
			{
				for (int e = allcar.size() - 1; e >= 0; e--)
				{
					if (allbullets[i].IsColliding(&allcar[e]))
					{
						allcar[e].shot(puissancebullet);

						allbullets.erase(allbullets.begin() + i);
						erasebullet = true;
						break;
					}
				}
			}



			if (erasebullet)
				continue;




			allbullets[i].BasiqueMove(0.f, -speedbullet * deltaTime);
			if (allbullets[i].GetPosition(0.f, 1.f).y < 0)
			{
				allbullets.erase(allbullets.begin() + i);
				continue;
			}

			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			auto pos = allbullets[i].GetPosition(0.5f, 0.5f);
			bulletHeroimage.SetPosition(pos.x, pos.y, 0.5f, 0.5f);
			bulletHeroimage.Draw(renderer);
		}


		for (int i = allhelico.size() - 1; i >= 0; i--)
		{
			if (bullethelicoshoot)
			{
				allbulletshelico.push_back(Character(15));
				allbulletshelico[allbulletshelico.size() - 1].SetPosition(allhelico[i].Shot('x') + allhelico[i].GetRadius(), allhelico[i].Shot('y') + allhelico[i].GetRadius());
				if (i == 0)
				{
					bullethelicoshoot = false;
				}
			}

			bool Draw = allhelico[i].ManageHelico(deltaTime, &allhelico, i);

			if (Draw)
			{
				for (int r = allrockets.size() - 1; r >= 0; r--)
				{
					allrockets[r].NewTarget(allrockets[r].Target() - 1);
				}
				continue;
			}

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			auto pos = allhelico[i].GetPosition(0.5f, 0.5f);
			Helicopter.SetPosition(pos.x, pos.y, 0.5f, 0.5f);
			Helicopter.Draw(renderer);
		}


		TargetEnnemy(&allhelico, &allrockets);



		for (int i = allrockets.size() - 1; i >= 0; i--)
		{
			if (allhelico.size() > 0)
			{
				if (allrockets[i].IsColliding(&allhelico[allrockets[i].Target()]))
				{
					allhelico[allrockets[i].Target()].shot(puissancerocket);
					allhelico.erase(allhelico.begin() + allrockets[i].Target());
					score += 10;

					for (int r = allrockets.size() - 1; r >= 0; r--)
					{
						if (allrockets[r].Target() == allrockets[i].Target())
						{
							allrockets[r].NewTarget(-1);
						}
					}

					allrockets.erase(allrockets.begin() + i);

					TargetEnnemy(&allhelico, &allrockets);

					continue;
				}

				int rocket_x = allrockets[i].GetPosition(0.5f, 0.5f).x;
				int rocket_y = allrockets[i].GetPosition(0.5f, 0.5f).y;

				int ennemy_x = allhelico[allrockets[i].Target()].GetPosition(0.5f, 0.5f).x;
				int ennemy_y = allhelico[allrockets[i].Target()].GetPosition(0.5f, 0.5f).y;


				int transX = ennemy_x - rocket_x;
				int transY = ennemy_y - rocket_y;


				int distX = abs(transX);
				int distY = abs(transY);

				int distMax = std::max(distX, distY);


				float stepX = transX / (float)distMax;
				float stepY = transY / (float)distMax;

				allrockets[i].BasiqueMove((stepX * speedrocket) * deltaTime, (stepY * speedrocket) * deltaTime);
			}

			else
			{
				allrockets[i].BasiqueMove(0.f, -speedrocket * deltaTime);
			}


			if (allrockets[i].GetPosition(0.f, 1.f).y < 0)
			{
				allrockets.erase(allrockets.begin() + i);
				continue;
			}


			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			auto pos = allrockets[i].GetPosition(0.5f, 0.5f);
			rocketHero.SetPosition(pos.x, pos.y, 0.5f, 0.5f);
			rocketHero.Draw(renderer);
		}

		switch (hero.IsAlive())
		{
		case 1:
			Coeur1.SetPosition(10, 10, 0, 0);
			Coeur1.Draw(renderer);
			break;
		case 2:
			Coeur2.SetPosition(10, 10, 0, 0);
			Coeur2.Draw(renderer);
			break;
		case 3:
			Coeur3.SetPosition(10, 10, 0, 0);
			Coeur3.Draw(renderer);
			break;
		case 4:
			Coeur4.SetPosition(10, 10, 0, 0);
			Coeur4.Draw(renderer);
			break;
		case 5:
			Coeur5.SetPosition(10, 10, 0, 0);
			Coeur5.Draw(renderer);
			break;
		case 6:
			Coeur6.SetPosition(10, 10, 0, 0);
			Coeur6.Draw(renderer);
			break;
		case 7:
			Coeur7.SetPosition(10, 10, 0, 0);
			Coeur7.Draw(renderer);
			break;
		case 8:
			Coeur8.SetPosition(10, 10, 0, 0);
			Coeur8.Draw(renderer);
			break;
		case 9:
			Coeur9.SetPosition(10, 10, 0, 0);
			Coeur9.Draw(renderer);
			break;
		case 10:
			Coeur10.SetPosition(10, 10, 0, 0);
			Coeur10.Draw(renderer);
			break;
		default:
			break;
		}

		if (hero.IsAlive() <= 0)
		{
			GameOver = true;
		}


		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		voitureHero.Draw(renderer);

		SDL_RenderPresent(renderer);
		Uint64 end = SDL_GetTicks64();

		deltaTime = (end - start) / 1000.f;
		float diff = TARGET_DELTA_TIME - deltaTime;

		//Cap FPS
		if (diff > 0)
		{
			SDL_Delay(diff * 1000);
			deltaTime = TARGET_DELTA_TIME;
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

