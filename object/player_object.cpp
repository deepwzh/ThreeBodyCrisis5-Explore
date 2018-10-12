#include "player_object.h"

PlayerObject::PlayerObject()
	: GameObject(){ }


PlayerObject::PlayerObject(glm::vec2 pos, glm::vec2 size, glm::vec2 v,Texture2D sprite)
	: GameObject(pos, size, sprite, v), Level(0), HealthPoint(100), ExperiencePoint(0), Acceleration(0.0f) {
	IsSolid = GL_TRUE;
}
