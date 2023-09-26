#ifndef SYSTEM_PLAYERCONTROLLERSYSTEM_H
#define SYSTEM_PLAYERCONTROLLERSYSTEM_H

#include "components/Player/PlayerController.h"
#include "components/Physics2D/PhysicsBody2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class PlayerControllerSystem: public System<PlayerController, PhysicsBody2D>
{

	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_PLAYERCONTROLLERSYSTEM_H