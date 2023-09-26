#ifndef SYSTEM_PLAYERCONTROLLERSYSTEM_H
#define SYSTEM_PLAYERCONTROLLERSYSTEM_H

#include "components/Player/PlayerController.h"
#include "components/Physics2D/PhysicsBody2D.h"
#include "components/Transform2D/Transform2D.h"

#include "systems/RenderingSystem2D/RenderingSystem2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class PlayerControllerSystem: public System<PlayerController, PhysicsBody2D, Transform2D>
{

	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_PLAYERCONTROLLERSYSTEM_H