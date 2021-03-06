#include "game_object.h"


GameObject::GameObject()
	: Position(0, 0), Size(1, 1), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(GL_FALSE), IsExist(GL_FALSE) { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite,  glm::vec2 velocity)
	: Position(pos), Size(size), Sprite(sprite), Velocity(velocity), Color(1.0f), Rotation(0.0f), IsSolid(GL_FALSE), IsExist(GL_TRUE), IsRender(GL_FALSE), EventUnicode{0,0,0,0,0} { }

void GameObject::Draw(SpriteRenderer &renderer)
{
	renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}