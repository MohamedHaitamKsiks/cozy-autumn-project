#ifndef SYSTEM_PLAYERLEVELTRANSITIONSYSTEM_H
#define SYSTEM_PLAYERLEVELTRANSITIONSYSTEM_H

#include "components/World2D/World2D.h"
#include "components/Player/PlayerController.h"
#include "components/Player/CameraController2D.h"
#include "components/Transform2D/Transform2D.h"


#include "ASEngine.h"

using namespace ASEngine;

class PlayerLevelTransitionSystem: public System<PlayerController, CameraController2D, Transform2D>
{
	// is in level
	inline bool PositionInLevelBound(const vec2 &position, const Level2D &level)
	{
		return position.x <= level.Position.x + level.Size.x &&
			   position.y <= level.Position.y + level.Size.y &&
			   position.x >= level.Position.x &&
			   position.y >= level.Position.y;
	};

	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_PLAYERLEVELTRANSITIONSYSTEM_H