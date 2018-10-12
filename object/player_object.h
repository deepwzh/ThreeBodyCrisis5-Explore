#pragma once
#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../render/texture.h"
#include "../render/sprite_renderer.h"
#include "game_object.h"

class PlayerObject : public GameObject
{
public:
	GLint Level; //LV
	GLint HealthPoint; //HP
	GLint ExperiencePoint; //EXP
	GLfloat Acceleration; //Speed-plus

	PlayerObject();
	PlayerObject(glm::vec2 pos, glm::vec2 size, glm::vec2 v, Texture2D sprite);
};

#endif