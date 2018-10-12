#pragma once
#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <tuple>
#include <iostream>
#include "level.h"
#include "resource_manage.h"
#include "object/player_object.h"
#include "object/shell_object.h"
#include "render/text_renderer.h"
#include "headers/irrKlang/irrKlang.h"
#include "render/particle_generator.h"
#include "render/post_processor.h"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

const glm::vec2 PLAYER_SIZE(30, 25);
const glm::vec2 PLAYER_INIT_V(400.0f, 400.0f);
const glm::vec2 SHELL_INIT_V(500.0f, -300.0f);
const GLfloat SHELL_RADIUS = 6.0f;



class Game
{
public:
	GameState State;
	GLboolean Keys[1024];
	GLuint Width, Height;
	//Level LevelInGame;
	GLint LevelThInGame;

	Game(GLuint width, GLuint height);
	~Game();
	void Init();
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
	void DoCollisions();
	// Reset
	void ResetPlayer();
	void ResetShell();
};

Collision CheckCollisionGG(GameObject &one, GameObject &two);
Collision CheckCollisionSG(ShellObject &one, GameObject &two);
Direction VectorDirection(glm::vec2 closest);

#endif