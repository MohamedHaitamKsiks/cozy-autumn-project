#include "PlayerControllerSystem.h"



void PlayerControllerSystem::OnCreate(){
    // insert code ...
};

void PlayerControllerSystem::OnUpdate(float delta)
{
	ForEach([delta](PlayerController& playerController, PhysicsBody2D& physicsBody2D, Gravity2D& gravity2D, CollisionBox2D& collisionBox2D, Transform2D& transform2D)
	{
		// ground
		if (physicsBody2D.OnGround)
		{
			if (!playerController.OnGround)
			{
				PlayerAnimationSystem::LandSquash(physicsBody2D, transform2D);
				playerController.TimeSinceLand = 0.0f;
			}

			playerController.TimeSinceLand += delta;

			physicsBody2D.Velocity.y = 0.0f;
			playerController.OnGround = true;
		}
		else if (physicsBody2D.Velocity.y > 100.0f)
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

				if (abs(physicsBody2D.Velocity.x) > PLAYER_MAX_SPEED)
					physicsBody2D.Velocity.x = Sign(physicsBody2D.Velocity.x) * PLAYER_MAX_SPEED;
			}
			else if (abs(physicsBody2D.Velocity.x) > 10.0f)
			{
				physicsBody2D.Velocity.x -= Sign(physicsBody2D.Velocity.x) * dec * delta;
			}
			else 
			{
				physicsBody2D.Velocity.x = 0.0f;
			}
				
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

			PlayerAnimationSystem::JumpStretch(transform2D);
		} 
		if (!playerController.InputJumpPressed)
		{
			playerController.CanJump = true;
			gravity2D.Gravity = PLAYER_DOWN_GRAVITY;
		}

		// collision with grass
		GrassCollisionSystem::CollisionWithGrass(playerController, collisionBox2D, transform2D);

	});
};

void PlayerControllerSystem::OnRender2D()
{
	// insert code ...
};

void PlayerControllerSystem::OnInputEvent(const InputEvent& event)
{
	ForEach([&event](PlayerController &playerController, PhysicsBody2D &physicsBody2D, Gravity2D &gravity2D, CollisionBox2D &collisionBox2D, Transform2D &transform2D)
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

		// jump just pressed
		if (keyEvent.Code == GLFW_KEY_SPACE)
		{
			if (!playerController.InputJumpPressed && keyEvent.Pressed)
			{
				playerController.JumpBuffer = PLAYER_JUMP_BUFFER;
				playerController.CanJump = false;
			}
			
			playerController.InputJumpPressed = keyEvent.Pressed;
		} });
};
