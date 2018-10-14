#include "level.h"



/***********************************************
****************Enemy Paramater*****************
************************************************/
const int ENEMY_NUM[LEVEL_NUM][ENEMY_GRADE] =
{
//  1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6
	10,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	7, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	12,8, 8, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	5, 7, 7, 8,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0,
	4,2,1,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0,
	6,4,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0,
};
//If it can be "background" + levelTh ?
//Answer:YES! But We Restructure here(hiahiahia, please don't delete this)
std::string LEVEL_BACKGROUND_FILE_NAME[LEVEL_NUM];
std::string LEVEL_BACKGROUND_TEXTURE_NAME[LEVEL_NUM];
std::string ENEMY_FILE_NAME[LEVEL_NUM][ENEMY_GRADE];
std::string ENEMY_TEXTURE_NAME[LEVEL_NUM][ENEMY_GRADE];
const glm::vec2 ENEMY_SIZE[LEVEL_NUM][ENEMY_GRADE] =
{
	glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f),
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
	glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f),
	glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f)
};

/***********************************************
**************Substance Paramater***************
************************************************/
const int SUBSTANCE_NUM[LEVEL_NUM] = {5, 8, 10, 15, 24, 33};
std::string SUBSTANCE_FILE_NAME[LEVEL_NUM][SUBSTANCE_NUM_MAX];
std::string SUBSTANCE_TEXTURE_NAME[LEVEL_NUM][SUBSTANCE_NUM_MAX];
const glm::vec2 SUBSTANCE_SIZE[LEVEL_NUM][SUBSTANCE_NUM_MAX] = 
{
	glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f), glm::vec2(60.0f, 50.0f)
};
const glm::vec2 SUBSTANCE_INIT_V[LEVEL_NUM][SUBSTANCE_NUM_MAX] = 
{ 
	glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f), glm::vec2(400.0f, 400.0f)
};






std::string getName(std::string prefix, int firstNum, int secondNum, std::string suffix)
{
	std::ostringstream stream1, stream2;
	stream1 << firstNum;
	stream2 << secondNum;
	std::string intString1 = stream1.str();
	std::string result;
	if (secondNum == 32767)
	{
		result = prefix + intString1 + suffix;
	}
	else
	{
		std::string intString2 = stream2.str();
		result = prefix + intString1 + intString2 + suffix;
	}
	return result;
}

void assignName()
{
	for (int i = 0; i < LEVEL_NUM; i++)
	{
	   LEVEL_BACKGROUND_FILE_NAME[i] = getName("res/pic/background", i, 32767, ".jpg");
	   LEVEL_BACKGROUND_TEXTURE_NAME[i] = getName("background", i, 32767, "");
	   for (int j = 0; j < ENEMY_GRADE; j++)
	   {
		   ENEMY_FILE_NAME[i][j] = getName("res/pic/enemy", i, j, ".png");
		   ENEMY_TEXTURE_NAME[i][j] = getName("enemy", i, j, "");
	   }
	   for (int k = 0; k < SUBSTANCE_NUM[i]; k++)
	   {
		   SUBSTANCE_FILE_NAME[i][k] = getName("res/pic/substance", i, k, ".png");//i = levelTh, k = NumInThisLevel
		   SUBSTANCE_TEXTURE_NAME[i][k] = getName("substance", i, k, "");
		  // std::cout << SUBSTANCE_FILE_NAME[i][k] << ":" << SUBSTANCE_TEXTURE_NAME[i][k] << std::endl;
	   }
	}
}

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
	substanceNumberInThisLevel = SUBSTANCE_NUM[levelTh];
}

void Level::LevelInit()
{
	assignName();

	//EnemyInit
	ResourceManager::LoadTexture(LEVEL_BACKGROUND_FILE_NAME[levelTh].c_str(), GL_FALSE, LEVEL_BACKGROUND_TEXTURE_NAME[levelTh]);
	for (int i = 0; i < ENEMY_GRADE; i++)
		ResourceManager::LoadTexture(ENEMY_FILE_NAME[levelTh][i].c_str(), GL_TRUE, ENEMY_TEXTURE_NAME[levelTh][i]);
	int enemyCounts = 0, enemyPlus = 0;
	for (int i = 0; i < ENEMY_GRADE; i++)
	{
		for (int j = 0; j < ENEMY_NUM[levelTh][i]; j++)
		{
			enemyPlus = enemyCounts + j;
			glm::vec2 comeout = glm::vec2(this->Width / 2 - 0.0, 0.0);
			Enemy[levelTh][enemyPlus] = new EnemyObject(comeout, ENEMY_SIZE[levelTh][i], ENEMY_INIT_V[levelTh][i] + glm::vec2(5 * i + 10 * enemyPlus, 7 * i), 20, ResourceManager::GetTexture(ENEMY_TEXTURE_NAME[levelTh][i]));
		}
		enemyCounts += ENEMY_NUM[levelTh][i];
	}

	//Substance Init
	for (int i = 0; i < SUBSTANCE_NUM[levelTh]; i++)
	{
		ResourceManager::LoadTexture(SUBSTANCE_FILE_NAME[levelTh][i].c_str(), GL_TRUE, SUBSTANCE_TEXTURE_NAME[levelTh][i]);
		glm::vec2 substanceComeout = glm::vec2(this->Width / 4 - 0.0, this->Height * 0.8) + glm::vec2(40 * i, -35 * i);
		Substance[levelTh][i] = new GameObject(substanceComeout, SUBSTANCE_SIZE[levelTh][i], ResourceManager::GetTexture(SUBSTANCE_TEXTURE_NAME[levelTh][i]),glm::vec2(0.0f,0.0f));
		//std::cout << SUBSTANCE_SIZE[levelTh][i].x << "," << SUBSTANCE_SIZE[levelTh][i].y << std::endl;
	}
}

Level::~Level()
{
	for (int i = 0; i < SUBSTANCE_NUM[levelTh]; i++)
	{
		delete Substance[levelTh][i];
		Substance[levelTh][i] = NULL;
	}

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
		Enemy[levelTh][i]->Move(dt, this->Width, this->Height);
	}
}

void Level::getWindowSize(int width, int height)
{
	this->Width = width;
	this->Height = height;
}