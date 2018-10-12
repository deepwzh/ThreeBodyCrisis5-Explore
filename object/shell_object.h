#pragma once
#ifndef SHELL_OBJECT_H
#define SHELL_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../render/texture.h"
#include "../render/sprite_renderer.h"
#include "game_object.h"

class ShellObject : public GameObject
{
public:
	GLfloat		Radius;
	GLboolean	Stuck;
	GLint		AttackValue;

	ShellObject();
	ShellObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, GLint av, Texture2D sprite);

	glm::vec2 Move(GLfloat dt, GLuint window_width, GLuint window_height);

	void      Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif