#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "resource_manage.h"
#include "object/enemy_object.h"

const int LEVEL_NUM = 8;
const int ENEMY_GRADE = 20; // 13(little)+4*1(1234's big)+3*2(567's two big)+1*3(8's three big)
const int ENEMY_NUM_MAX = 128;
const int SUBSTANCE_NUM_MAX = 128;
const int REWARD_NUM_MAX = 128;
std::string getName(std::string prefix, int firstNum, int secondNum, std::string suffix);

class Level
{
public:
	int Width, Height;
	GLint levelTh;
	GLint enemyNumberInThisLevel;
	GLint substanceNumberInThisLevel;
	EnemyObject *Enemy[LEVEL_NUM][ENEMY_NUM_MAX];
	GameObject *Substance[LEVEL_NUM][SUBSTANCE_NUM_MAX];
	GLfloat MapMagnification[LEVEL_NUM];
	Level();
	~Level();
	void LevelInit();
	void EnemyMove(GLfloat dt);
	void getWindowSize(int width, int height);
};