#ifndef SYSTEM_PLAYERANIMATIONSYSTEM_H
#define SYSTEM_PLAYERANIMATIONSYSTEM_H

#include "components/AnimatedSprite2D/AnimatedSprite2D.h"
#include "components/Player/PlayerController.h"
#include "components/Physics2D/PhysicsBody2D.h"
#include "components/Transform2D/Transform2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class PlayerAnimationSystem: public System<PlayerController, AnimatedSprite2D, PhysicsBody2D, Transform2D>
{
public :
	// land squash
	static void LandSquash(const PhysicsBody2D& physicsBody2D, Transform2D& transform2D);

	// jump
	static void JumpStretch(Transform2D &transform2D);

private:
	// default methods
	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_PLAYERANIMATIONSYSTEM_H