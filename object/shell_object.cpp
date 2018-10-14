#include "shell_object.h"

ShellObject::ShellObject()
	: GameObject(), Radius(12.5f) {
	IsExist = GL_FALSE;
}


ShellObject::ShellObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, GLint av, Texture2D sprite)
	: GameObject(pos, glm::vec2(radius * 2, radius * 2), sprite, velocity), AttackValue(av), Radius(radius){
	IsExist = GL_FALSE;
}


glm::vec2 ShellObject::Move(GLfloat dt, GLuint window_width, GLuint window_height)
{
	if (this->IsExist)
	{
		this->Position += this->Velocity * dt;

		if (this->Position.x <= 0.0f)
		{
			this->Velocity.x = -this->Velocity.x;
			this->Position.x = 0.0f;
		}
		else if (this->Position.x + this->Size.x >= window_width)
		{
			this->Velocity.x = -this->Velocity.x;
			this->Position.x = window_width - this->Size.x;
		}
		if (this->Position.y <= 0.0f)
		{
			this->Velocity.y = -this->Velocity.y;
			this->Position.y = 0.0f;
		}
		else if (this->Position.y + this->Size.y >= window_height)
		{
			this->Velocity.y = -this->Velocity.y;
			this->Position.y = window_height - this->Size.y;
		}
	}
	return this->Position;
}


void ShellObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
	this->IsExist = GL_FALSE;
}