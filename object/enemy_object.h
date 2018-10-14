#pragma once
#ifndef ENEMY_OBJECT_H
#define ENEMY_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include "../render/texture.h"
#include "../render/sprite_renderer.h"
#include "game_object.h"

class EnemyObject : public GameObject
{
public:
	GLint HealthPoint;

	EnemyObject();
	EnemyObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, GLint hp, Texture2D sprite);

	glm::vec2 Move(GLfloat dt, GLuint window_width, GLuint window_height);
	void      Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif