#include "game.h"
using namespace irrklang;
const int SHELLNUM = 10;
GLboolean speedDone = GL_FALSE;
int killedTimes = 0;
SpriteRenderer		*Renderer;
PlayerObject		*Player;
ShellObject			*HuajiShell[SHELLNUM];
Level				*LevelInGame;
TextRenderer		*Text;
ParticleGenerator	*Particles;
PostProcessor		*Effects;
GLfloat				ShakeTime = 0.0f;
ISoundEngine		*SoundEngine = createIrrKlangDevice();

void Skill1Swamp(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat speedplus);
void Skill2Blackhole(GLfloat posx, GLfloat posy, GLfloat intensity, GLfloat dt);

Game::Game()
	: State(GAME_ACTIVE), Keys(), CursorX(0),CursorY(0){
	LevelInGame = new Level();
	LevelThInGame = LevelInGame->levelTh;
}

Game::~Game()
{
	delete Effects;
	delete Particles;
	delete Renderer;
	delete Player;
	for(int i = 0; i < SHELLNUM; i++)
		delete HuajiShell[i];
	LevelInGame->~Level();
	delete LevelInGame;
}

void Game::Init()
{
	LevelInGame->getWindowSize(this->Width, this->Height);

	// Load and Configure shaders
	ResourceManager::LoadShader("render/shaders/sprite.vss", "render/shaders/sprite.fss", NULL, "sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	
	//Creat Player and Shells
	ResourceManager::LoadTexture("res/pic/huaji.png", GL_TRUE, "face");
	ResourceManager::LoadTexture("res/pic/myship0up.png", GL_TRUE, "player0up");
	ResourceManager::LoadTexture("res/pic/myship0left.png", GL_TRUE, "player0left");
	ResourceManager::LoadTexture("res/pic/myship0down.png", GL_TRUE, "player0down");
	ResourceManager::LoadTexture("res/pic/myship0right.png", GL_TRUE, "player0right");
	ResourceManager::LoadTexture("res/pic/shell0.png", GL_TRUE, "huajishell");
	glm::vec2 playerPos = glm::vec2(0, this->Height - PLAYER_SIZE.y);
	Player = new PlayerObject(playerPos, PLAYER_SIZE, PLAYER_INIT_V, ResourceManager::GetTexture("player0up"));
	Player->Direction = 1;
	for (int i = 0; i < SHELLNUM; i++) 
	{
		glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - SHELL_RADIUS, -SHELL_RADIUS * 2);
		HuajiShell[i] = new ShellObject(ballPos, SHELL_RADIUS, SHELL_INIT_V + glm::vec2(5*i, 5*i), 1, ResourceManager::GetTexture("huajishell"));
	}

	//Load Level
	LevelInGame->LevelInit();

	//Load Fonts
	Text = new TextRenderer(this->Width, this->Height);
	Text->Load("res/fonts/yahei.ttf", 24);

	//Load Particles
	ResourceManager::LoadShader("render/shaders/particle.vss", "render/shaders/particle.fss", nullptr, "particle");
	ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("particle").SetMatrix4("projection", projection);
	ResourceManager::LoadTexture("res/pic/particle.png", GL_TRUE, "particle");
	Particles = new ParticleGenerator(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("particle"), 50);

	//Load Effects
	ResourceManager::LoadShader("render/shaders/post_processing.vss", "render/shaders/post_processing.fss", nullptr, "postprocessing");
	Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->Width, this->Height);

	//Load Music
	//SoundEngine->play2D("res/sound/ddz.mp3", GL_TRUE);
}


void Game::Update(GLfloat dt, GLfloat poscx, GLfloat poscy)
{
	this->CursorX = poscx;
	this->CursorY = poscy;
	//Move Shells
	for (int i = 0; i < SHELLNUM; i++)
		HuajiShell[i]->Move(dt, this->Width,this->Height);

	//Move Enemy
	LevelInGame->EnemyMove(dt);

	//Check and deal with Collisions
	this->DoCollisions();

	//Check if load Particles	
	for (int i = 0; i < SHELLNUM; i++)
	{
		if(HuajiShell[i]->IsRender == GL_TRUE)
			Particles->Update(dt, *HuajiShell[i], 2, glm::vec2(HuajiShell[i]->Radius / 2));
	}

	//Define ShakeTime
	if (ShakeTime > 0.0f)
	{
		ShakeTime -= dt;
		if (ShakeTime <= 0.0f)
			Effects->Shake = GL_FALSE;
	}
	
	//If player was died
	if (Player->HealthPoint <= 0)
	{
		this->ResetPlayer();
	}
}


void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		glm::vec2 velocity(Player->Velocity.x * dt, Player->Velocity.y * dt);

		/********************************************************
		 ******************** Move playerboard*******************
		 ********************************************************/
		if (this->Keys[GLFW_KEY_LEFT] || this->Keys[GLFW_KEY_A])
		{
			Player->Sprite = ResourceManager::GetTexture("player0left");
			Player->Direction = 3;
			if (Player->Position.x >= 0)
			{
				if (this->Keys[GLFW_KEY_Q]) velocity *= 2;
					Player->Position.x -= velocity.x;
			}
		}
		if (this->Keys[GLFW_KEY_RIGHT] || this->Keys[GLFW_KEY_D])
		{
			Player->Sprite = ResourceManager::GetTexture("player0right");
			Player->Direction = 4;
			if (Player->Position.x <= this->Width - Player->Size.x)
			{
				if (this->Keys[GLFW_KEY_Q]) velocity *= 2;
				Player->Position.x += velocity.x;
			}
		}
		if (this->Keys[GLFW_KEY_DOWN] || this->Keys[GLFW_KEY_S])
		{
			Player->Sprite = ResourceManager::GetTexture("player0down");
			Player->Direction = 2;
			if (Player->Position.y <= this->Height - Player->Size.y)
			{
				if (this->Keys[GLFW_KEY_Q]) velocity *= 2;
				Player->Position.y += velocity.y;
			}
		}
		if (this->Keys[GLFW_KEY_UP] || this->Keys[GLFW_KEY_W])
		{
			Player->Sprite = ResourceManager::GetTexture("player0up");
			Player->Direction = 1;
			if (Player->Position.y >= 0)
			{
				if (this->Keys[GLFW_KEY_Q]) velocity *= 2;
				Player->Position.y -= velocity.y;
			}
		}
		/********************************************************
		 *******************Function playerboard*****************
		 ********************************************************/
		if (this->Keys[GLFW_KEY_J])
		{
			for (int i = 0; i < SHELLNUM; i++)
			{
				HuajiShell[i]->Position = Player->Position + glm::vec2(PLAYER_SIZE.x / 2 - SHELL_RADIUS, -SHELL_RADIUS * 2);
				HuajiShell[i]->IsExist = GL_TRUE;
				HuajiShell[i]->IsRender = GL_TRUE;
				switch (Player->Direction)
				{
				case 1:HuajiShell[i]->Velocity = glm::vec2(0.0f, -400.f); break;
				case 2:HuajiShell[i]->Velocity = glm::vec2(0.0f, 400.f); break;
				case 3:HuajiShell[i]->Velocity = glm::vec2(-400.0f, 0.f); break;
				case 4:HuajiShell[i]->Velocity = glm::vec2(400.0f, 0.f); break;
				default:std::cout << "ERROR::at:game.cpp::ProcessInput" << std::endl;
				}
			}
		}
		if (this->Keys[GLFW_KEY_SPACE])
		{
			for (int i = 0; i < SHELLNUM; i++)
				HuajiShell[i]->Reset(Player->Position, SHELL_INIT_V + glm::vec2(50 * i, 50 * i));
		}
		/********************************************************
		 **********************Mouse Function********************
		 ********************************************************/
		if (this->Mouse[GLFW_MOUSE_BUTTON_LEFT])
		{
			for (int i = 0; i < SHELLNUM; i++)
			{
				HuajiShell[i]->Position = Player->Position + glm::vec2(PLAYER_SIZE.x / 2 - SHELL_RADIUS, -SHELL_RADIUS * 2);
				HuajiShell[i]->IsExist = GL_TRUE;
				HuajiShell[i]->IsRender = GL_TRUE;
				double CursorLenth = sqrt((this->CursorX - Player->Position.x) * (this->CursorX - Player->Position.x) + (this->CursorY - Player->Position.y) * (this->CursorY -Player->Position.y));
				float Vx = (this->CursorX - Player->Position.x) / CursorLenth;
				float Vy = (this->CursorY - Player->Position.y) / CursorLenth;
				HuajiShell[i]->Velocity = glm::vec2(Vx * 400, Vy * 400);
			}
		}
		if (this->Mouse[GLFW_MOUSE_BUTTON_RIGHT])
		{
			double PlayerMouseLength = sqrt((this->CursorX - Player->Position.x) * (this->CursorX - Player->Position.x) + (this->CursorY - Player->Position.y) * (this->CursorY - Player->Position.y));
			float PMx = (this->CursorX - Player->Position.x) / PlayerMouseLength;
			float PMy = (this->CursorY - Player->Position.y) / PlayerMouseLength;
			Player->Position += glm::vec2(PMx * 200.0 * dt, PMy * 200.0 * dt);
		}
	}
}


void Game::Render()
{
	std::string BackgroundTextureNameInThisLevel[LEVEL_NUM];
	for(int i = 0; i < LEVEL_NUM; i++)
		BackgroundTextureNameInThisLevel[i] = getName("background", i , 32767, "");
	
	float magnification = 2;
	if (this->State == GAME_ACTIVE)
	{
		Effects->BeginRender();

		//Move ViewWindow
		/*if (Player->Position.y < (this->Height - PLAYER_SIZE.y * 2))
			glViewport(-(Player->Position.x) * (magnification - 1), -(this->Height - Player->Position.y) * (magnification - 1), WINDOW_WIDTH * magnification, this->Height * magnification);
		else*/
		glViewport(-(Player->Position.x) * (magnification - 1), -(this->Height - Player->Position.y -Player->Size.y) * (magnification - 1), this->Width * magnification, this->Height * magnification);

		//Render background
		Renderer->DrawSprite(ResourceManager::GetTexture(BackgroundTextureNameInThisLevel[LevelThInGame]), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);

		//Render Substance
		for (int i = 0; i < LevelInGame->substanceNumberInThisLevel; i++)
			if (LevelInGame->Substance[LevelThInGame][i]->IsExist == GL_TRUE && LevelInGame->Substance[LevelThInGame][i]->IsRender == GL_TRUE)
			{
				LevelInGame->Substance[LevelThInGame][i]->Draw(*Renderer);
			}

		//Render Enemy
		for (int i = 0; i < LevelInGame->enemyNumberInThisLevel; i++)
		{
			LevelInGame->Enemy[LevelThInGame][i]->IsRender = GL_TRUE;
			if ((LevelInGame->Enemy[LevelThInGame][i]->IsExist == GL_TRUE) && LevelInGame->Enemy[LevelInGame->levelTh][i]->IsRender == GL_TRUE)
			{
				LevelInGame->Enemy[LevelInGame->levelTh][i]->Draw(*Renderer);
			}
		}

		//Render Player and Shells
		Player->Draw(*Renderer);
		//Particles->Draw();
		for (int i = 0; i < SHELLNUM; i++)
			if (HuajiShell[i]->IsExist == GL_TRUE && HuajiShell[i]->IsRender == GL_TRUE)
				HuajiShell[i]->Draw(*Renderer);

		/*//Render Fonts Here
		std::stringstream ss; ss << "X:" << Player->Position.x << ",Y:" << Player->Position.y;
		float tm = (magnification * magnification - 1) / (magnification * magnification);
		//Text->RenderText(ss.str(), Player->Position.x * tm, (Player->Position.y + Player->Size.y) * tm, 1.0f);*/

		//End Effects
		Effects->EndRender();
		Effects->Render(glfwGetTime());
	}

	//Render Fonts
	std::stringstream ss; ss << "X:" << Player->Position.x << ",Y:" << Player->Position.y;
	float tm = 1 - 1/magnification;
	Text->RenderText(ss.str(), Player->Position.x * tm, (Player->Position.y + Player->Size.y) * tm, (1 - tm));

	Renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}


//Have not finished
void Game::DoCollisions()
{
	//If Shell hit Enemy
	for (int i = 0; i < SHELLNUM; i++)
	{
		for (int j = 0; j < LevelInGame->enemyNumberInThisLevel; j++)
		{
			if (LevelInGame->Enemy[LevelThInGame][j]->IsExist == GL_TRUE && HuajiShell[i]->IsExist == GL_TRUE)
			{
				Collision resultSG = CheckCollisionSG(*(HuajiShell[i]), *(LevelInGame->Enemy[LevelThInGame][j]));
				if (std::get<0>(resultSG))
				{
					SoundEngine->play2D("res/sound/boom.mp3", GL_FALSE);
					std::cout << "play" << std::endl;
					std::cout << Player->EventUnicode[2] << std::endl;
					ShakeTime = 0.05f;
					Effects->Shake = GL_TRUE;
					Direction direct = std::get<1>(resultSG);
					if (direct == LEFT || direct == RIGHT)
					{
						HuajiShell[i]->Velocity.x = -HuajiShell[i]->Velocity.x;
						LevelInGame->Enemy[LevelThInGame][j]->IsExist = GL_FALSE;
					}
					else
					{
						HuajiShell[i]->Velocity.y = -HuajiShell[i]->Velocity.y;
						LevelInGame->Enemy[LevelThInGame][j]->IsExist = GL_FALSE;
					}
				}
			}
		}
	}

	//If Enemy hit me
	for (int i = 0; i < LevelInGame->enemyNumberInThisLevel; i++)
	{
		if (LevelInGame->Enemy[LevelThInGame][i]->IsExist == GL_TRUE)
		{
			Collision resultGG = CheckCollisionGG(*(LevelInGame->Enemy[LevelThInGame][i]), *(Player));
			if (std::get<0>(resultGG))
			{
				Direction direct = std::get<1>(resultGG);
				if (direct == LEFT || direct == RIGHT)
				{
					LevelInGame->Enemy[LevelThInGame][i]->Velocity.x = -LevelInGame->Enemy[LevelThInGame][i]->Velocity.x;
				}
				if (direct == UP || direct == DOWN)
				{
					LevelInGame->Enemy[LevelThInGame][i]->Velocity.y = -LevelInGame->Enemy[LevelThInGame][i]->Velocity.y;
				}
				ResetPlayer();
				ResetShell();
			}
		}
	}
}

//Have not finished
void Game::ResetPlayer()
{
	Player->Size = PLAYER_SIZE;
	Player->Position = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	Player->HealthPoint = 100;
	Player->ExperiencePoint = 0;
	Player->Level = 0;
	Player->Velocity = PLAYER_INIT_V;
	for (int i = 0; i < LevelInGame->enemyNumberInThisLevel; i++)
	{
		LevelInGame->Enemy[LevelThInGame][i]->IsExist = GL_TRUE;
	}
	std::cout << "You have been killed X " << killedTimes++ << std::endl;
}



void Game::ResetShell()
{
	glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	for (int i = 0; i < SHELLNUM; i++)
	{
		glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - SHELL_RADIUS, -SHELL_RADIUS * 2);
		HuajiShell[i]->Position = ballPos;
		HuajiShell[i]->Velocity = SHELL_INIT_V + glm::vec2(5 * i, 5 * i);
		HuajiShell[i]->IsExist = GL_FALSE;
		HuajiShell[i]->IsRender = GL_FALSE;
	}
}

void Game::getWindowSize(int widthNow, int heightNow)
{
	this->Width = widthNow;
	this->Height = heightNow;
}


/*****************************************************************************
Skill Below:
1. Swmp:If player come into this, your speed will be reduced to the original
"speedplus"(0<speedplus<1);
2. Black hole: Player will be attracted to an object automatically with a
intensity;
*****************************************************************************/
void Skill1Swamp(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat speedplus)
{
	//Swamp
	if (speedDone == GL_FALSE && Player->Position.x > x1 && Player->Position.x < x2 && Player->Position.y > y1 && Player->Position.y < y2)
	{
		Player->Velocity *= speedplus;
		std::cout << "Speed Now:" << Player->Velocity.x << std::endl;
		speedDone = GL_TRUE;
	}

	if (speedDone == GL_TRUE && ((Player->Position.x <= x1) || (Player->Position.x >= x2) || (Player->Position.y <= y1) || (Player->Position.y > y2)))
	{
		Player->Velocity *= (1/speedplus);
		std::cout << "Speed Now:" << Player->Velocity.x << std::endl;
		speedDone = GL_FALSE;
	}
}

void Skill2Blackhole(GLfloat posx, GLfloat posy, GLfloat intensity, GLfloat dt)
{
	//Gravitational field black hole
	GLfloat speedLength = sqrt((posx - Player->Position.x) * (posx - Player->Position.x) + (posy - Player->Position.y) * (posy - Player->Position.y));
	Player->PlayerMoveItself(glm::vec2((posx / speedLength) * intensity, (posy / speedLength) * intensity), dt);
}

/**************************************************************************************
Collision Checkers Below;
Each frame is tested once;
First, check whether or not to collide;
If so, multiply the velocity vector by the unit vector in the four directions;
Now, we konw which direction the object was hit and how to deal with collision results;
***************************************************************************************/

Collision CheckCollisionGG(GameObject &one, GameObject &two) // AABB - AABB collision
{
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;

	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;

	glm::vec2 oneCenter(one.Position.x + one.Size.x / 2, one.Position.y + one.Size.y / 2);
	glm::vec2 twoCenter(two.Position.x + two.Size.x / 2, two.Position.y + two.Size.y / 2);
	glm::vec2 difference = twoCenter - oneCenter;

	if (collisionX && collisionY)
		return std::make_tuple(GL_TRUE, VectorDirection(difference), glm::vec2(0.0f, 0.0f));
	else
		return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
}


Collision CheckCollisionSG(ShellObject &one, GameObject &two) //AABB - Circle collision
{
	glm::vec2 center(one.Position + one.Radius);
	glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	glm::vec2 closest = aabb_center + clamped;
	difference = closest - center;

	if (glm::length(difference) < one.Radius)
		return std::make_tuple(GL_TRUE, VectorDirection(difference), difference);
	else
		return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
}


Direction VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};
	GLfloat max = 0.0f;
	GLuint best_match = -1;
	for (GLuint i = 0; i < 4; i++)
	{
		GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}