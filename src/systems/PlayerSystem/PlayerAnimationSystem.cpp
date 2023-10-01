#include "PlayerAnimationSystem.h"

#define PLAYER_SQUASH_STRETCH_SPEED 8.0f
#define PLAYER_MAX_LAND_SPEED 600.0f

PlayerAnimationSystem::PlayerAnimationSystem()
{
	m_Priority = 1;
}

void PlayerAnimationSystem::LandSquash(const PhysicsBody2D &physicsBody2D, Transform2D &transform2D)
{
	transform2D.Scale = Interpolate::Linear(vec2::ONE(), vec2{1.5, 0.65}, physicsBody2D.Velocity.y / PLAYER_MAX_LAND_SPEED);
}

void PlayerAnimationSystem::JumpStretch(Transform2D &transform2D)
{
	transform2D.Scale = vec2{0.65f, 1.4f};
}

void PlayerAnimationSystem::OnCreate()
{
	m_IdleID = ResourceManager<Sprite>::GetResourceId(UniqueString("sprites/player/idle.sprite.json"));
	m_RunID = ResourceManager<Sprite>::GetResourceId(UniqueString("sprites/player/run.sprite.json"));
	m_JumpID = ResourceManager<Sprite>::GetResourceId(UniqueString("sprites/player/jump.sprite.json"));
	m_WallID = ResourceManager<Sprite>::GetResourceId(UniqueString("sprites/player/wall.sprite.json"));
	m_WallWalkID = ResourceManager<Sprite>::GetResourceId(UniqueString("sprites/player/wall_walk.sprite.json"));
};

void PlayerAnimationSystem::OnUpdate(float delta)
{
	ForEach([delta, this](PlayerController &playerController, AnimatedSprite2D &animatedSprite2D, PhysicsBody2D& physicsBody2D, Transform2D &transform2D)
	{

		// flip sprite to look direction
		if (animatedSprite2D.FlipH != playerController.LookDirection < 0.5f)
		{
			if (playerController.OnGround)
				transform2D.Scale = vec2{1.2f, 0.8f};

			animatedSprite2D.FlipH = playerController.LookDirection < 0.5f;
		}

		// animate scale for squash and stretch effect
		vec2 targetScale = vec2::ONE();
		if (physicsBody2D.Velocity.y > 0.0f && playerController.State != PlayerController::WallClimpState)
			targetScale = Interpolate::Linear(vec2::ONE(), vec2{0.5f, 1.25f}, physicsBody2D.Velocity.y / 700.0f);
		
		transform2D.Scale = Interpolate::Linear(transform2D.Scale, targetScale, PLAYER_SQUASH_STRETCH_SPEED * delta);
	
		// rotate on jump to velocity
		if (playerController.OnGround || playerController.State != PlayerController::FreeState)
		{
			transform2D.Rotation = 0.0f;
		}
		else
		{
			float rotation = Interpolate::Linear(0.0f, (M_PI / 4.0f), playerController.LookDirection * abs(physicsBody2D.Velocity.x) * physicsBody2D.Velocity.y / (PLAYER_MAX_LAND_SPEED * PLAYER_MAX_SPEED));
			transform2D.Rotation = rotation;
		}
		

		// play animations
		if (playerController.State == PlayerController::WallClimpState)
		{
			animatedSprite2D.SpriteID = m_WallID;
		}
		else if (!playerController.OnGround)
		{
			animatedSprite2D.SpriteID = m_JumpID;

			// jump steps
			if (physicsBody2D.Velocity.y > 80.0f)
				animatedSprite2D.Frame = 2.0f;
			else if (physicsBody2D.Velocity.y > 0.0f)
				animatedSprite2D.Frame = 1.0f;
			else
				animatedSprite2D.Frame = 0.0f;
		}
		else if (abs(physicsBody2D.Velocity.x) > 30.0f && physicsBody2D.Velocity.x * playerController.LookDirection > 0.0f && playerController.TimeSinceLand > PLAYER_LAND_DURATION)
		{
			if (physicsBody2D.OnWall)
			{
				animatedSprite2D.SpriteID = m_WallWalkID;
				animatedSprite2D.FrameRate = 6.5f;
			}
			else 
			{
				// change sprite if not done
				if (animatedSprite2D.SpriteID != m_RunID)
				{
					animatedSprite2D.Frame = 0.0f;
					animatedSprite2D.SpriteID = m_RunID;
				}
				animatedSprite2D.FrameRate = Interpolate::Linear(0.0f, 10.0f, abs(physicsBody2D.Velocity.x) / PLAYER_MAX_SPEED);
			}

		}
		else
		{
			animatedSprite2D.SpriteID = m_IdleID;
			animatedSprite2D.FrameRate = 8.0f;
		}

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
