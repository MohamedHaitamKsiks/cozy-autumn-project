#include "PlayerAnimationSystem.h"

#define PLAYER_SQUASH_STRETCH_SPEED 8.0f
#define PLAYER_MAX_LAND_SPEED 500.0f

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
	m_DashID = ResourceManager<Sprite>::GetResourceId(UniqueString("sprites/player/dash.sprite.json"));
	m_DeathID = ResourceManager<Sprite>::GetResourceId(UniqueString("sprites/player/death.sprite.json"));
	m_DeathParticlesID = ResourceManager<Sprite>::GetResourceId(UniqueString("sprites/particles/death.sprite.json"));
};

void PlayerAnimationSystem::OnUpdate(float delta)
{
	ForEach([delta, this](ParticleEmitter2D& emitter2D, PlayerController &playerController, AnimatedSprite2D &animatedSprite2D, PhysicsBody2D& physicsBody2D, Transform2D &transform2D)
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

		if (playerController.State == PlayerController::DeathState)
		{
			targetScale = vec2::ONE() * 0.7f;

			if (abs(transform2D.Scale.x - 0.7f) < 0.01f && animatedSprite2D.Visible)
			{
				animatedSprite2D.Visible = false;

				// kill sfx
				playerController.DeathPlayer.Play();

				// screen feed back
				CameraSystem2D::Shake(2.0f, 0.2f);
				// death particles
				float rotationOffset =  Random::Float();
				const int particleNumber = 8;
				for (int i = 0; i < particleNumber; i++)
				{
					Particle2D particle2D{};
					particle2D.Position = transform2D.Position;
					particle2D.Outline = true;
					particle2D.FrameRate = 8.0f;
					particle2D.Layer = DrawLayer::FrontParticles;
					particle2D.SpriteID = m_DeathParticlesID;
					particle2D.LinearVelocity = vec2::RIGHT().Rotate(2.0f * M_PI * ( rotationOffset + (float) i / (float) particleNumber)) * 300.0f;
					particle2D.LifeTime = 5.0f;

					emitter2D.Particles.Push(particle2D);
				}
			}
		}
		
		else if (physicsBody2D.Velocity.y > 0.0f && playerController.State != PlayerController::WallClimpState)
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

		// make player visible if not death
		if (playerController.State != PlayerController::DeathState)
		{
			animatedSprite2D.Visible = true;
		}

		// modulate to red when not able to dahs
		animatedSprite2D.Modulate = (playerController.CanDash || playerController.State == PlayerController::DashState || playerController.State == PlayerController::DeathState) ? Color::WHITE() : Color{4.5f, 0.8f, 0.8f, 1.0f};

		// play animations
		if (playerController.State == PlayerController::WallClimpState)
		{
			animatedSprite2D.SpriteID = m_WallID;
		}
		else if (playerController.State == PlayerController::DeathState)
		{
			animatedSprite2D.SpriteID = m_DeathID;
		}
		else if (playerController.State == PlayerController::DashState)
		{
			animatedSprite2D.FrameRate = 0.0f;
			
			if (abs(physicsBody2D.Velocity.y) < 0.001f)
			{
				animatedSprite2D.SpriteID = m_DashID;
				animatedSprite2D.Frame = playerController.DashTimer > 0.1f;
			}
			else
			{
				animatedSprite2D.SpriteID = m_JumpID;
				animatedSprite2D.Frame = (physicsBody2D.Velocity.y > 0.0f)? 2.0f: 0.0f;
			}	
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

		animatedSprite2D.FrameRate *= (playerController.State == PlayerController::TransitionState)? 0.0f: 1.0f;
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
