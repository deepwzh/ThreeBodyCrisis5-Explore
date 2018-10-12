#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "resource_manage.h"
#include "object/enemy_object.h"

const GLuint WINDOW_WIDTH = 1600;
const GLuint WINDOW_HEIGHT = 900;

const int LEVEL_NUM = 5;
const int ENEMY_GRADE = 5;
const int ENEMY_NUM_MAX = 128;

class Level
{
public:
	GLint levelTh;
	GLint enemyNumberInThisLevel;
	EnemyObject *Enemy[LEVEL_NUM][ENEMY_NUM_MAX];
	Level();
	~Level();
	void LevelInit();
	void EnemyMove(GLfloat dt);
};