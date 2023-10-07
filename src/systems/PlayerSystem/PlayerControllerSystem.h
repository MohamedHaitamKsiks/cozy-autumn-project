#ifndef SYSTEM_PLAYERCONTROLLERSYSTEM_H
#define SYSTEM_PLAYERCONTROLLERSYSTEM_H

#include "components/Player/PlayerController.h"
#include "components/Player/CameraController2D.h"
#include "components/Physics2D/PhysicsBody2D.h"
#include "components/Physics2D/Gravity2D.h"
#include "components/Physics2D/CollisionBox2D.h"
#include "components/Transform2D/Transform2D.h"
#include "components/ParticleEmitter2D/ParticleEmitter2D.h"

#include "systems/CameraSystem2D/CameraSystem2D.h"
#include "systems/RenderingSystem2D/RenderingSystem2D.h"
#include "systems/SpriteAnimationSystem2D/SpriteAnimationSystem2D.h"

#include "GrassCollisionSystem.h"
#include "KillAreaCollisionSystem.h"
#include "LeafCollisionSystem.h"
#include "PlayerAnimationSystem.h"
#include "PearlCollisionSystem.h"
#include "SpringCollisionSystem.h"

#include "ASEngine.h"

using namespace ASEngine;

class PlayerControllerSystem: public System<ParticleEmitter2D, CameraController2D, PlayerController, PhysicsBody2D, Gravity2D, CollisionBox2D, Transform2D>
{
public:
	// get sign
	static inline float Sign(float num)
	{
		return (float) (num > 0.0f) - (float) (num < 0.0f);
	}

	// kill player
	static void Kill() {};

private:
	ResourceID m_DashID;

	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_PLAYERCONTROLLERSYSTEM_H