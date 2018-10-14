#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../render/texture.h"
#include "../render/sprite_renderer.h"


class GameObject
{
public:
	// Object state
	glm::vec2   Position, Size, Velocity;
	glm::vec3   Color;
	GLfloat     Rotation;
	GLboolean   IsSolid;
	GLboolean   IsExist;
	GLboolean	IsRender;
	int			EventUnicode[5];
	// Render state
	Texture2D   Sprite;
	// Constructor(s)
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	// Draw sprite
	virtual void Draw(SpriteRenderer &renderer);
};

#endif

/***********************************************************
********************About  EventUnicode*********************
EventUnicode is an int data, which define what would be 
happen when an event happen. For example: If one Enemy's
EventUnicode[5] is {1001,1002,1452,1207} , then if it hit 
Player, Player's hp-1; if hit enemy, then noting would be
happen; if it hit shell, it's hp-1;...;So we should set up
a table to define this Unicode.
************************************************************/