#include "level.h"


const int ENEMY_NUM[LEVEL_NUM][ENEMY_GRADE] =
{
	8,4,2,0,0,
	8,5,3,1,0,
	8,6,4,2,1,
	8,6,4,2,1,
	8,6,4,2,1
};

//Need to be change here
const GLchar* LEVEL_BACKGROUND_FILE_NAME[LEVEL_NUM] =
{
	"res/pic/background.jpg",
	"res/pic/background.jpg",
	"res/pic/background.jpg",
	"res/pic/background.jpg",
	"res/pic/background.jpg"
};

//If it can be "background" + levelTh ?
const GLchar* LEVEL_BACKGROUND_TEXTURE_NAME[LEVEL_NUM] =
{
	"background1",
	"background2",
	"background3",
	"background4",
	"background5"
};

const GLchar* ENEMY_FILE_NAME[LEVEL_NUM][ENEMY_GRADE] =
{
	"res/pic/enemy11.png", "res/pic/enemy12.png", "res/pic/enemy13.png", "res/pic/enemy14.png", "res/pic/enemy15.png",
	"res/pic/enemy21.png", "res/pic/enemy22.png", "res/pic/enemy23.png", "res/pic/enemy24.png", "res/pic/enemy25.png",
	"res/pic/enemy31.png", "res/pic/enemy32.png", "res/pic/enemy33.png", "res/pic/enemy34.png", "res/pic/enemy35.png",
	"res/pic/enemy41.png", "res/pic/enemy42.png", "res/pic/enemy43.png", "res/pic/enemy44.png", "res/pic/enemy45.png",
	"res/pic/enemy51.png", "res/pic/enemy52.png", "res/pic/enemy53.png", "res/pic/enemy54.png", "res/pic/enemy55.png"
};

const GLchar* ENEMY_TEXTURE_NAME[LEVEL_NUM][ENEMY_GRADE] =
{
	"enemy11", "enemy12", "enemy13", "enemy14", "enemy15",
	"enemy21", "enemy22", "enemy23", "enemy24", "enemy25",
	"enemy31", "enemy32", "enemy33", "enemy34", "enemy35",
	"enemy41", "enemy42", "enemy43", "enemy44", "enemy45",
	"enemy51", "enemy52", "enemy53", "enemy54", "enemy55"
};

const glm::vec2 ENEMY_SIZE[LEVEL_NUM][ENEMY_GRADE] =
{
	glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f),
	glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f),
	glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f),
	glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f),
	glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f)
};
const glm::vec2 ENEMY_INIT_V[LEVEL_NUM][ENEMY_GRADE] =
{
	glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f),
	glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f),
	glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f),
	glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f),
	glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f)
};





//Renderer for every level's every Enemy
/*
void RendererInit()
{
	glm::mat4 EnemyProjection = glm::ortho(0.0f, static_cast<GLfloat>(WINDOW_WIDTH), static_cast<GLfloat>(WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f);
	ResourceManager::LoadShader("render/shaders/Sprite1.vss", "render/shaders/Sprite1.fss", NULL, "EnemySprite");
	ResourceManager::GetShader("EnemySprite").Use().SetInteger("enemyimage", 0);
	ResourceManager::GetShader("EnemySprite").SetMatrix4("enemyprojection", EnemyProjection);
	LevelRenderer = new SpriteRenderer(ResourceManager::GetShader("EnemySprite"));
}
*/


int getEveryLevelEnemyNum(const int enemyNum[])
{
	int enemyNumInThisLevel = 0;
	for (int j = 0; j < ENEMY_GRADE; j++)
	{
		enemyNumInThisLevel += enemyNum[j];
	}
	return enemyNumInThisLevel;
}

//Leve
Level::Level()
{
	levelTh = 0;
	enemyNumberInThisLevel = getEveryLevelEnemyNum(ENEMY_NUM[levelTh]);
}

void Level::LevelInit()
{
	ResourceManager::LoadTexture(LEVEL_BACKGROUND_FILE_NAME[levelTh], GL_FALSE, LEVEL_BACKGROUND_TEXTURE_NAME[levelTh]);
	for(int i = 0; i < ENEMY_GRADE; i++)
		ResourceManager::LoadTexture(ENEMY_FILE_NAME[levelTh][i], GL_TRUE, ENEMY_TEXTURE_NAME[levelTh][i]);
	int enemyCounts = 0, enemyPlus = 0;
	for (int i = 0; i < ENEMY_GRADE; i++)
	{
		for (int j = 0; j < ENEMY_NUM[levelTh][i]; j++)
		{
			enemyPlus = enemyCounts + j;
			glm::vec2 comeout = glm::vec2(WINDOW_WIDTH / 2 - 0.0, 0.0);
			Enemy[levelTh][enemyPlus] = new EnemyObject(comeout, ENEMY_SIZE[levelTh][i], ENEMY_INIT_V[levelTh][i] + glm::vec2(5 * i+ 10*enemyPlus, 7 * i), 20, ResourceManager::GetTexture(ENEMY_TEXTURE_NAME[levelTh][i]));
		}
		enemyCounts += ENEMY_NUM[levelTh][i];
	}
}

Level::~Level()
{
	for (int j = 0; j < enemyNumberInThisLevel-1; j++)
	{
		delete Enemy[levelTh][j];
		Enemy[levelTh][j] = NULL;
	}
}

void Level::EnemyMove(GLfloat dt)
{
	for (int i = 0; i < enemyNumberInThisLevel; i++)
	{
		Enemy[levelTh][i]->Move(dt, WINDOW_WIDTH, WINDOW_HEIGHT);
	}
}



/*
void Level::EnemyRender()
{
	//LevelRenderer->DrawSprite(ResourceManager::GetTexture(LEVEL_BACKGROUND_TEXTURE_NAME[levelTh]), glm::vec2(0, 0), glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT), 0.0f);

	for (int i = 0; i < enemyNumberInThisLevel; i++)
		Enemy[levelTh][i]->IsExist = GL_TRUE;

	for (int i = 0; i < enemyNumberInThisLevel; i++)
	if ((Enemy[levelTh][i]->IsExist == GL_TRUE) && Enemy[levelTh][i]->Destroyed == GL_FALSE )
		Enemy[levelTh][i]->Draw(*LevelRenderer);
}
*/