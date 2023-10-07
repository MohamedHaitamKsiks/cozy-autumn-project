#ifndef SYSTEM_PLAYERLEVELTRANSITIONSYSTEM_H
#define SYSTEM_PLAYERLEVELTRANSITIONSYSTEM_H

#include "components/World2D/World2D.h"
#include "components/Physics2D/PhysicsBody2D.h"
#include "components/Player/PlayerController.h"
#include "components/Player/CameraController2D.h"
#include "components/Transform2D/Transform2D.h"

#include "systems/CameraSystem2D/CameraSystem2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class PlayerLevelTransitionSystem: public System<PlayerController, PhysicsBody2D, CameraController2D, Transform2D>
{
	// is in level
	inline bool PositionInLevelBound(const vec2 &position, const Level2D &level)
	{
		return position.x + 12.0f <= level.Position.x + level.Size.x &&
			   position.y + 16.0f<= level.Position.y + level.Size.y &&
			   position.x - 12.0f >= level.Position.x &&
			   position.y - 16.0f>= level.Position.y;
	};

	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_PLAYERLEVELTRANSITIONSYSTEM_H