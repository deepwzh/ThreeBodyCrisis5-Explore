#include "enemy_object.h"

EnemyObject::EnemyObject()
	: GameObject(), HealthPoint(0), IsExist(0) { }


EnemyObject::EnemyObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, GLint hp, Texture2D sprite)
	: GameObject(pos, size, sprite, velocity), HealthPoint(hp),IsExist(GL_FALSE) {}


glm::vec2 EnemyObject::Move(GLfloat dt, GLuint window_width, GLuint window_height)
{
	//std::cout << "I can Move2";
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


void EnemyObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
	this->IsExist = false;
}