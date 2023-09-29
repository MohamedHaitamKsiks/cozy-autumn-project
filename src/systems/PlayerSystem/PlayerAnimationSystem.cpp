#include "PlayerAnimationSystem.h"

#define PLAYER_SQUASH_STRETCH_SPEED 8.0f
#define PLAYER_MAX_LAND_SPEED 1500.0f

void PlayerAnimationSystem::LandSquash(const PhysicsBody2D &physicsBody2D, Transform2D &transform2D)
{
	transform2D.Scale = Interpolate::Linear(vec2::ONE(), vec2{1.5, 0.75}, physicsBody2D.Velocity.y / PLAYER_MAX_LAND_SPEED);
}

void PlayerAnimationSystem::JumpStretch(Transform2D &transform2D)
{
	transform2D.Scale = vec2{0.65f, 1.25f};
}

void PlayerAnimationSystem::OnCreate()
{
	
};

void PlayerAnimationSystem::OnUpdate(float delta)
{
	ForEach([delta](PlayerController &playerController, AnimatedSprite2D &animatedSprite2D, PhysicsBody2D& physicsBody2D, Transform2D &transform2D)
	{
		// flip sprite to look direction
		animatedSprite2D.FlipH = playerController.LookDirection < 0.5f;

		// animate scale for squash and stretch effect
		vec2 targetScale = vec2::ONE();
		if (physicsBody2D.Velocity.y > 0.0f)
			targetScale = Interpolate::Linear(vec2::ONE(), vec2{0.5f, 1.25f}, physicsBody2D.Velocity.y / 700.0f);
		
		transform2D.Scale = Interpolate::Linear(transform2D.Scale, targetScale, PLAYER_SQUASH_STRETCH_SPEED * delta);
	});
};

void PlayerAnimationSystem::OnRender2D()
{
	// insert code ...
};

void PlayerAnimationSystem::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
