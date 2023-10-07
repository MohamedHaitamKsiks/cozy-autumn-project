#include "PlayerControllerSystem.h"

#define PLAYER_SPRING_FORCE 350.0f;
#define PLAYER_JUMP_SPRING_FORCE 50.0f;

void PlayerControllerSystem::OnCreate()
{
	m_DashID = ResourceManager<Sprite>::GetResourceId(UniqueString("sprites/player/dash.sprite.json"));
};

void PlayerControllerSystem::OnUpdate(float delta)
{
	ForEach([this, delta](ParticleEmitter2D& emitter2D, CameraController2D& camera2D, PlayerController& playerController, PhysicsBody2D& physicsBody2D, Gravity2D& gravity2D, CollisionBox2D& collisionBox2D, Transform2D& transform2D)
	{
		// spawn position
		if (playerController.Spawned && playerController.OnGround)
		{
			playerController.SpawnPosition = transform2D.Position;
			playerController.Spawned = false;
		}


		// particle emition
		playerController.ParticleTimer -= delta;
		if (playerController.ParticleTimer < 0.0f)
		{
			playerController.ParticleTimer = 0.03f;

			Particle2D particle2D{};
			particle2D.SpriteID = playerController.DustSpriteID;
			particle2D.FrameRate = 14.0f;
			
			// wall slide particles
			if (playerController.State == PlayerController::WallClimpState)
			{
				particle2D.Frame = Random::Range(3.0f, 8.0f);
				particle2D.Position = transform2D.Position + vec2::RIGHT() * playerController.LookDirection * 8 + vec2::UP() * 8;
				particle2D.LinearVelocity = vec2::LEFT().Rotate(Random::Range(-1.0f, 1.0f) * M_PI / 4.0f) * playerController.LookDirection * Random::Range(20.0f, 50.0f);

				emitter2D.Particles.Push(particle2D);
			}
			else if (playerController.State == PlayerController::FreeState && physicsBody2D.Velocity.y < -120.0f)
			{
				particle2D.Frame = Random::Range(4.0f, 8.0f);
				particle2D.Position = transform2D.Position + vec2{Random::Range(-1.0f, 1.0f), Random::Range(-1.0f, 1.0f)} * 2.0f;
				
				emitter2D.Particles.Push(particle2D);
			}
			else if (playerController.State == PlayerController::DashState)
			{
				particle2D.Frame = 0.0f;
				particle2D.FrameRate = 0.0f;
				particle2D.Position = transform2D.Position + vec2::UP() * 24.0f;
				particle2D.SpriteID = m_DashID;
				particle2D.FlipH = playerController.LookDirection < 0.0f;
				particle2D.LifeTime = 0.3f;
				particle2D.Layer = DrawLayer::BackParticles;
				particle2D.Modulate = ParticleParam<Color>(Color::WHITE(), Color{1.0f, 1.0f, 1.0f, 0.0f});

				emitter2D.Particles.Push(particle2D);
			}
		}


		// ground
		if (physicsBody2D.OnGround)
		{
			if (!playerController.OnGround)
			{
				PlayerAnimationSystem::LandSquash(physicsBody2D, transform2D);
				playerController.TimeSinceLand = 0.0f;
			
				// land audio feedback
				playerController.LandPlayer.Play();

				// land dust particles
				const float particleNumber = 12;
				for (int i = 0; i < particleNumber; i++)
				{
					Particle2D particle2D{};
					particle2D.SpriteID = playerController.DustSpriteID;
					particle2D.Position = transform2D.Position;
					particle2D.Time = 0.0f;
					particle2D.FrameRate = 15.0f;
					particle2D.Frame = Random::Range(2.0f, 8.0f);
					particle2D.LinearVelocity = ParticleParam<vec2>(vec2::RIGHT().Rotate(- M_PI * (float) i  / (float) particleNumber) * Random::Range(25.0f, 60.0f), vec2::ZERO());

					emitter2D.Particles.Push(particle2D);
				}
			}

			playerController.TimeSinceLand += delta;

			physicsBody2D.Velocity.y = 0.0f;
			playerController.OnGround = true;

			// dash ability
			playerController.CanDash = true;
		}
		else if (physicsBody2D.Velocity.y > 50.0f)
		{
			playerController.OnGround = false;
		}

		// celling collision
		if (physicsBody2D.OnCeilling)
			physicsBody2D.Velocity.y = 0.0f;

		// control gravity
		if (physicsBody2D.Velocity.y > 0.0f)
			gravity2D.Gravity = PLAYER_DOWN_GRAVITY;

		if (playerController.State == PlayerController::FreeState)
		{
			// move
			float direction = (float)playerController.InputRightPressed - (float)playerController.InputLeftPressed;
			float acc = (playerController.OnGround) ? PLAYER_ACC : PLAYER_FALL_ACC;
			float dec = (playerController.OnGround) ? PLAYER_ACC : PLAYER_FALL_DEC;

			// accelerate
			if (abs(direction) > 0.5f)
			{
				physicsBody2D.Velocity.x += direction * acc * delta;

			}
			else if (abs(physicsBody2D.Velocity.x) > 10.0f)
			{
				physicsBody2D.Velocity.x -= Sign(physicsBody2D.Velocity.x) * dec * delta;
			}
			else 
			{
				physicsBody2D.Velocity.x = 0.0f;
			}
			// player max speed
			if (abs(physicsBody2D.Velocity.x) > PLAYER_MAX_SPEED)
				physicsBody2D.Velocity.x = Sign(physicsBody2D.Velocity.x) * PLAYER_MAX_SPEED;
			
			// look direction
			if (playerController.OnGround && abs(direction) > 0.5f && direction != playerController.LookDirection)
			{
				playerController.LookDirection = direction;
			}
			else if (!playerController.OnGround && abs(physicsBody2D.Velocity.x) > 0.5f && physicsBody2D.Velocity.x * playerController.LookDirection < 0.0f)
			{
				playerController.LookDirection = Sign(physicsBody2D.Velocity.x);
			}

			// add wall climb
			if (!playerController.OnGround && physicsBody2D.Velocity.y > 0.0f && playerController.LookDirection * physicsBody2D.Velocity.x > 0.0f && physicsBody2D.OnWall)
			{
				// dash ability
				playerController.CanDash = true;
				playerController.LandPlayer.Play();
				playerController.State = PlayerController::WallClimpState;
			}

		}
		// on wall climb
		else if (playerController.State == PlayerController::WallClimpState)
		{
			physicsBody2D.Velocity.x = 10.0f * playerController.LookDirection;

			// free state on ground or when not on wall
			if (playerController.OnGround || !physicsBody2D.OnWall)
			{
				playerController.State = PlayerController::FreeState;
				physicsBody2D.Velocity.x = 0.0f;
			}
			
			// limit fall speed
			if (physicsBody2D.Velocity.y > PLAYER_WALL_FALL_SPEED)
				physicsBody2D.Velocity.y = PLAYER_WALL_FALL_SPEED;
		}

		// jump 
		playerController.JumpBuffer -= delta;

		if ( playerController.JumpBuffer > 0.0001f && (
		(playerController.OnGround && playerController.State == PlayerController::FreeState) ||
		(playerController.State == PlayerController::WallClimpState)) )
		{
			physicsBody2D.Velocity.y = - PLAYER_JUMP_FORCE;

			// add wall jump
			if (playerController.State == PlayerController::WallClimpState)
			{
				playerController.LookDirection *= -1.0f;
				physicsBody2D.Velocity.x = playerController.LookDirection * PLAYER_MAX_SPEED;
				playerController.State = PlayerController::FreeState;
			}

			playerController.OnGround = false;
			playerController.JumpBuffer = 0.0f;
			gravity2D.Gravity = PLAYER_UP_GRAVITY;
			playerController.StepPlayer.Play();

			PlayerAnimationSystem::JumpStretch(transform2D);
		} 
		if (!playerController.InputJumpPressed)
		{
			playerController.CanJump = true;
			gravity2D.Gravity = PLAYER_DOWN_GRAVITY;
		}

		// dash input
		if (playerController.State == PlayerController::FreeState && playerController.InputCanDashPress && playerController.InputDashPressed && playerController.CanDash)
		{
			vec2 direction{
				(float)playerController.InputRightPressed - (float)playerController.InputLeftPressed,
				(float)playerController.InputDownPressed - (float)playerController.InputUpPressed
			};
			if (direction.LengthSquared() < 0.001f)
			{
				direction.x = playerController.LookDirection;
			}
			if (abs(direction.x) > 0.001f)
			{
				playerController.LookDirection = direction.x;
			}
			physicsBody2D.Velocity = direction.Normalized() * PLAYER_DASH_SPEED;

			playerController.DashTimer = PLAYER_DASH_DURATION;
			playerController.State = PlayerController::DashState;

			// feedback of dash
			CameraSystem2D::Shake(2.2f, 0.2f);
			playerController.DashPlayer.Play();

			playerController.CanDash = false;
		}
		// on dash
		if (playerController.State == PlayerController::DashState)
		{
			gravity2D.Gravity = 0.0f;

			playerController.DashTimer -= delta;
			if (playerController.DashTimer < 0.0f)
			{
				if (physicsBody2D.Velocity.y < 0.0f)
					physicsBody2D.Velocity.y *= 0.2f;

				playerController.State = PlayerController::FreeState;
				gravity2D.Gravity = PLAYER_DOWN_GRAVITY;
			}
		}
		playerController.InputCanDashPress = !playerController.InputDashPressed;

		// death state
		if (playerController.State == PlayerController::DeathState)
		{
			physicsBody2D.Velocity = vec2::ZERO();
			gravity2D.Gravity = 0.0f;

			// death timer
			playerController.DeathTimer -= delta;
			if (playerController.DeathTimer < 0.0f)
			{
				camera2D.Transition = true;
				transform2D.Position = playerController.SpawnPosition;
				playerController.OnGround = true;
				playerController.State = PlayerController::FreeState;
			}
		}

		// transition system
		if (playerController.State == PlayerController::TransitionState)
		{
			playerController.TransitionTimer -= delta;
			if (playerController.TransitionTimer < 0.0f)
			{
				playerController.State = playerController.LastState;
				physicsBody2D.Velocity = playerController.LastVelocity;
				physicsBody2D.IsStatic = false;
			}
		}

		// collision with grass
		GrassCollisionSystem::CollisionWithGrass(playerController, collisionBox2D, transform2D);

		// kill test
		if (KillAreaCollisionSystem::Collide(collisionBox2D, transform2D) && playerController.State != PlayerController::DeathState)
		{
			playerController.HitPlayer.Play();

			playerController.State = PlayerController::DeathState;
			playerController.DeathTimer = PLAYER_DEATH_DURATION;

			physicsBody2D.Velocity = vec2::ZERO();
			gravity2D.Gravity = 0.0f;

			ScoreSystem::IncrementDeathCounter();

			CameraSystem2D::Shake(1.0f, 0.1f);
			CameraSystem2D::SlowMotion(0.5f);
		}

		// collide with grass
		if (LeafCollisionSystem::Collide(collisionBox2D, transform2D))
		{
			playerController.Spawned = true;
			CameraSystem2D::SlowMotion(0.5f);
		}

		if (PearlCollisionSystem::Collide(collisionBox2D, transform2D))
		{
			playerController.CanDash = true;
		}

		if (SpringCollisionSystem::Collide(collisionBox2D, transform2D))
		{
			transform2D.Position.y -= 4.0f;
			physicsBody2D.Velocity.y = -PLAYER_SPRING_FORCE;
			
			playerController.State = PlayerController::FreeState;

			playerController.CanDash = true;
			playerController.OnGround = false;

			playerController.SpringPlayer.Play();

			if (playerController.JumpBuffer > 0.0001f)
			{
				playerController.StepPlayer.Play();

				playerController.JumpBuffer = 0.0f;
				gravity2D.Gravity = PLAYER_UP_GRAVITY;
				physicsBody2D.Velocity.y -= PLAYER_JUMP_SPRING_FORCE;
			}
		}

	});
};

void PlayerControllerSystem::OnRender2D()
{
	// insert code ...
};

void PlayerControllerSystem::OnInputEvent(const InputEvent& event)
{
	ForEach([&event](ParticleEmitter2D& emitter2D, CameraController2D& camera2D,PlayerController &playerController, PhysicsBody2D &physicsBody2D, Gravity2D &gravity2D, CollisionBox2D &collisionBox2D, Transform2D &transform2D)
	{
		if (event.GetType() != InputEventType::KEYBOARD)
			return;

		// cast input event to keyboard type
		InputEventKeyboard keyEvent = event.Get<InputEventKeyboard>();

		// get input direction
		if (keyEvent.Code == GLFW_KEY_LEFT)
			playerController.InputLeftPressed = keyEvent.Pressed;

		if (keyEvent.Code == GLFW_KEY_RIGHT)
			playerController.InputRightPressed = keyEvent.Pressed;

		if (keyEvent.Code == GLFW_KEY_UP)
			playerController.InputUpPressed = keyEvent.Pressed;

		if (keyEvent.Code == GLFW_KEY_DOWN)
			playerController.InputDownPressed = keyEvent.Pressed;

		// jump just pressed
		if (keyEvent.Code == GLFW_KEY_SPACE)
		{
			if (!playerController.InputJumpPressed && keyEvent.Pressed)
			{
				playerController.JumpBuffer = PLAYER_JUMP_BUFFER;
				playerController.CanJump = false;
			}
			
			playerController.InputJumpPressed = keyEvent.Pressed;
		} 

		// dash button just pressed
		if (keyEvent.Code == GLFW_KEY_D)
		{
			playerController.InputDashPressed = keyEvent.Pressed;
		} 
	});
};
