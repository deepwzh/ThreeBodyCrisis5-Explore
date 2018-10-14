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
	GLint Fuel; //Move will decrease this
	GLint FoodAndWater; // Time will decreasr this
	GLfloat Acceleration; //Speed-plus

	GLuint Direction; //UP,DOWN,LEFT,TIGHE = 1,2,3,4
	PlayerObject();
	PlayerObject(glm::vec2 pos, glm::vec2 size, glm::vec2 v, Texture2D sprite);
};

#endif