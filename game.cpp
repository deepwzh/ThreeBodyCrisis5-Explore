#include "game.h"
using namespace irrklang;
const int SHELLNUM = 10;

SpriteRenderer		*Renderer;
PlayerObject		*Player;
ShellObject			*HuajiShell[SHELLNUM];
Level				*LevelInGame;
TextRenderer		*Text;
ParticleGenerator	*Particles;
PostProcessor		*Effects;
GLfloat				ShakeTime = 0.0f;
ISoundEngine		*SoundEngine = createIrrKlangDevice();



Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height),LevelThInGame(0){}

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
	LevelInGame = new Level();
	// Load and Configure shaders
	ResourceManager::LoadShader("render/shaders/sprite.vss", "render/shaders/sprite.fss", NULL, "sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	
	//Creat Player and Shells
	ResourceManager::LoadTexture("res/pic/huaji.png", GL_TRUE, "face");
	ResourceManager::LoadTexture("res/pic/myship.png", GL_TRUE, "player");
	ResourceManager::LoadTexture("res/pic/huaji.png", GL_TRUE, "huajishell");
	glm::vec2 playerPos = glm::vec2(0, WINDOW_HEIGHT - PLAYER_SIZE.y);
	Player = new PlayerObject(playerPos, PLAYER_SIZE, PLAYER_INIT_V, ResourceManager::GetTexture("player"));
	for (int i = 0; i < SHELLNUM; i++) 
	{
		glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - SHELL_RADIUS, -SHELL_RADIUS * 2);
		HuajiShell[i] = new ShellObject(ballPos, SHELL_RADIUS, SHELL_INIT_V + glm::vec2(5*i, 5*i), 1, ResourceManager::GetTexture("huajishell"));
	}

	//Load Level
	LevelInGame->LevelInit();

	//Load Fonts
	Text = new TextRenderer(this->Width, this->Height);
	Text->Load("res/fonts/yahei.ttf", 10);

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
	SoundEngine->play2D("res/sound/ddz.mp3", GL_TRUE);
}


GLboolean isV = GL_FALSE;
void Game::Update(GLfloat dt)
{
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
		if(HuajiShell[i]->Stuck == GL_FALSE)
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
	//ÒýÁ¦³¡ºÚ¶´
	if (Player->Position.x > 1200 && Player->Position.y > 500 && isV == GL_FALSE)
	{
		Player->Velocity *= 0.2;
		std::cout <<"Speed Now:"<< Player->Velocity.x << std::endl;
		isV = GL_TRUE;
	}
	if ((Player->Position.x <= 1200 || (Player->Position.x >= 1200 && Player->Position.y <= 500)) && isV == GL_TRUE)
	{
		Player->Velocity *= 5;
		std::cout << "Speed Now:" << Player->Velocity.x << std::endl;
		isV = GL_FALSE;
	}
}


void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		glm::vec2 velocity(Player->Velocity.x * dt, Player->Velocity.y * dt);
		// Move playerboard
		if (this->Keys[GLFW_KEY_LEFT] || this->Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0)
			{
				if (this->Keys[GLFW_KEY_Q]) velocity *= 2;
					Player->Position.x -= velocity.x;
			}
		}
		if (this->Keys[GLFW_KEY_RIGHT] || this->Keys[GLFW_KEY_D])
		{
			if (Player->Position.x <= this->Width - Player->Size.x)
			{
				if (this->Keys[GLFW_KEY_Q]) velocity *= 2;
				Player->Position.x += velocity.x;
			}
		}
		if (this->Keys[GLFW_KEY_DOWN] || this->Keys[GLFW_KEY_S])
		{
			if (Player->Position.y <= this->Height - Player->Size.y)
			{
				if (this->Keys[GLFW_KEY_Q]) velocity *= 2;
				Player->Position.y += velocity.y;
			}
		}
		if (this->Keys[GLFW_KEY_UP] || this->Keys[GLFW_KEY_W])
		{
			if (Player->Position.y >= 0)
			{
				if (this->Keys[GLFW_KEY_Q]) velocity *= 2;
				Player->Position.y -= velocity.y;
			}
		}

		//Function playerboard
		if (this->Keys[GLFW_KEY_J])
		{
			for (int i = 0; i < SHELLNUM; i++)
			{
				HuajiShell[i]->Position = Player->Position + glm::vec2(PLAYER_SIZE.x / 2 - SHELL_RADIUS, -SHELL_RADIUS * 2);
				HuajiShell[i]->Stuck = GL_FALSE;
			}
		}
		if (this->Keys[GLFW_KEY_SPACE])
		{
			for (int i = 0; i < SHELLNUM; i++)
				HuajiShell[i]->Reset(Player->Position, SHELL_INIT_V + glm::vec2(50 * i, 50 * i));
		}
	}
}


void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		Effects->BeginRender();
		//Move ViewWindow
		float magnification = 1.2;
		//if (Player->Position.y < (WINDOW_HEIGHT - PLAYER_SIZE.y * 2))
		//	glViewport(-(Player->Position.x) * (magnification - 1), -(WINDOW_HEIGHT - Player->Position.y) * (magnification - 1), WINDOW_WIDTH * magnification, WINDOW_HEIGHT * magnification);
		//else
			glViewport(-(Player->Position.x) * (magnification - 1), -(WINDOW_HEIGHT - Player->Position.y - PLAYER_SIZE.y) * (magnification - 1), WINDOW_WIDTH * magnification, WINDOW_HEIGHT * magnification);
		Renderer->DrawSprite(ResourceManager::GetTexture("background1"), glm::vec2(0, 0), glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT), 0.0f);
		//Render Background and Enemy
		for (int i = 0; i < LevelInGame->enemyNumberInThisLevel; i++)
			LevelInGame->Enemy[LevelThInGame][i]->IsExist = GL_TRUE;
		for (int i = 0; i < LevelInGame->enemyNumberInThisLevel; i++)
			if ((LevelInGame->Enemy[LevelInGame->levelTh][i]->IsExist == GL_TRUE) && LevelInGame->Enemy[LevelInGame->levelTh][i]->Destroyed == GL_FALSE)
			{
				LevelInGame->Enemy[LevelInGame->levelTh][i]->Draw(*Renderer);
			}
		//Render Player and Shells
		Player->Draw(*Renderer);
		Particles->Draw();
		for (int i = 0; i < SHELLNUM; i++)
			if (HuajiShell[i]->Stuck == false)
				HuajiShell[i]->Draw(*Renderer);
		//Render Fonts
		std::stringstream ss; ss << "Posx:" << Player->Position.x << "Posy:" << Player->Position.y;
		Text->RenderText("Your Pos:" + ss.str(), 0.0f, 890.0f, 1.0f);
		//End Effects
		Effects->EndRender();
		Effects->Render(glfwGetTime());
	}
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
			if (LevelInGame->Enemy[LevelThInGame][j]->Destroyed == false && HuajiShell[i]->Stuck == false)
			{
				Collision resultSG = CheckCollisionSG(*(HuajiShell[i]), *(LevelInGame->Enemy[LevelThInGame][j]));
				if (std::get<0>(resultSG))
				{
					SoundEngine->play2D("res/sound/boom.mp3", GL_FALSE);
					std::cout << "play" << std::endl;
					ShakeTime = 0.05f;
					Effects->Shake = GL_TRUE;
					Direction direct = std::get<1>(resultSG);
					if (direct == LEFT || direct == RIGHT)
					{
						HuajiShell[i]->Velocity.x = -HuajiShell[i]->Velocity.x;
						LevelInGame->Enemy[LevelThInGame][j]->Destroyed = GL_TRUE;
					}
					else
					{
						HuajiShell[i]->Velocity.y = -HuajiShell[i]->Velocity.y;
						LevelInGame->Enemy[LevelThInGame][j]->Destroyed = GL_TRUE;
					}
				}
			}
		}
	}

	//If Enemy hit me
	for (int i = 0; i < LevelInGame->enemyNumberInThisLevel; i++)
	{
		if (LevelInGame->Enemy[LevelThInGame][i]->Destroyed == GL_FALSE)
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


int KillTimes = 0;
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
		LevelInGame->Enemy[LevelThInGame][i]->Destroyed = GL_FALSE;
	}
	//std::cout << "You have been killed X " << KillTimes++ << std::endl;
}



void Game::ResetShell()
{
	glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	for (int i = 0; i < SHELLNUM; i++)
	{
		glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - SHELL_RADIUS, -SHELL_RADIUS * 2);
		HuajiShell[i]->Position = ballPos;
		HuajiShell[i]->Velocity = SHELL_INIT_V + glm::vec2(5 * i, 5 * i);
		HuajiShell[i]->Destroyed = false;
		HuajiShell[i]->Stuck = true;
	}
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