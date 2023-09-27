#include "PlayerControllerSystem.h"

// define constants
#define PLAYER_ACC 700.0f
#define PLAYER_MAX_SPEED 150.0f
#define PLAYER_UP_GRAVITY 450.0f
#define PLAYER_DOWN_GRAVITY 700.0f
#define PLAYER_JUMP_FORCE 240.0f
// 300 ms jump buffer
#define PLAYER_JUMP_BUFFER 0.3f 

void PlayerControllerSystem::OnCreate(){
    // insert code ...
};

void PlayerControllerSystem::OnUpdate(float delta)
{
	ForEach([delta](PlayerController& playerController, PhysicsBody2D& physicsBody2D, Gravity2D& gravity2D, Transform2D& transform2D)
	{
		// ground
		if (physicsBody2D.OnGround)
		{
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

		// wall collision
		if (physicsBody2D.OnWall)
			physicsBody2D.Velocity.x = 0.0f;

		// control gravity
		if (physicsBody2D.Velocity.y > 0.0f)
			gravity2D.Gravity = PLAYER_DOWN_GRAVITY;

		// move
		float direction = (float)playerController.InputRightPressed - (float)playerController.InputLeftPressed;
		
		// accelerate
		if (abs(direction) > 0.5f)
		{
			physicsBody2D.Velocity.x += direction * PLAYER_ACC * delta;

			if (abs(physicsBody2D.Velocity.x) > PLAYER_MAX_SPEED)
				physicsBody2D.Velocity.x = Sign(physicsBody2D.Velocity.x) * PLAYER_MAX_SPEED;
		}
		else if (abs(physicsBody2D.Velocity.x) > 0.001f)
		{
			physicsBody2D.Velocity.x -= Sign(physicsBody2D.Velocity.x) * PLAYER_ACC * delta;
		}
		else 
		{
			physicsBody2D.Velocity.x = 0.0f;
		}
			
		// look direction
		if (abs(direction) > 0.5f && direction != playerController.LookDirection)
		{
			playerController.LookDirection = direction;
			transform2D.Scale.x = direction;
		} 

		// jump 
		playerController.JumpBuffer -= delta;

		if (playerController.JumpBuffer > 0.0001f &&  playerController.OnGround)
		{
			physicsBody2D.Velocity.y = - PLAYER_JUMP_FORCE;
			playerController.OnGround = false;
			playerController.JumpBuffer = 0.0f;
			gravity2D.Gravity = PLAYER_UP_GRAVITY;
		}
		if (!playerController.InputJumpPressed)
		{
			playerController.CanJump = true;
			gravity2D.Gravity = PLAYER_DOWN_GRAVITY;
		}

	});
};

void PlayerControllerSystem::OnRender2D()
{
	// insert code ...
};

void PlayerControllerSystem::OnInputEvent(const InputEvent& event)
{
	ForEach([&event](PlayerController &playerController, PhysicsBody2D &physicsBody2D, Gravity2D &gravity2D, Transform2D &transform2D)
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
		}
	});
};
