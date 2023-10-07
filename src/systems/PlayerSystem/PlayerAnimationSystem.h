#ifndef SYSTEM_PLAYERANIMATIONSYSTEM_H
#define SYSTEM_PLAYERANIMATIONSYSTEM_H

#include "components/AnimatedSprite2D/AnimatedSprite2D.h"
#include "components/Player/PlayerController.h"
#include "components/Physics2D/PhysicsBody2D.h"
#include "components/Transform2D/Transform2D.h"
#include "components/ParticleEmitter2D/ParticleEmitter2D.h"

#include "systems/CameraSystem2D/CameraSystem2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class PlayerAnimationSystem: public System<ParticleEmitter2D, PlayerController, AnimatedSprite2D, PhysicsBody2D, Transform2D>
{
public :
	PlayerAnimationSystem();

	// land squash
	static void LandSquash(const PhysicsBody2D& physicsBody2D, Transform2D& transform2D);

	// jump
	static void JumpStretch(Transform2D &transform2D);

private:
	// cache player sprites
	ResourceID m_IdleID;
	ResourceID m_RunID;
	ResourceID m_JumpID;
	ResourceID m_WallID;
	ResourceID m_WallWalkID;
	ResourceID m_DashID;
	ResourceID m_DeathID;
	ResourceID m_DeathParticlesID;

	// default methods
	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_PLAYERANIMATIONSYSTEM_H