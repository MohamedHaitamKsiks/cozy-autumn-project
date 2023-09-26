#include "PlayerControllerSystem.h"

void PlayerControllerSystem::OnCreate()
{
	// insert code ...
};

void PlayerControllerSystem::OnUpdate(float delta)
{
	ForEach([delta](PlayerController& playerController, PhysicsBody2D& physicsBody2D)
	{
		
		if (physicsBody2D.OnGround)
		{
			physicsBody2D.Velocity.y = 0.0f;
			playerController.OnGround = true;
		}
		else if (physicsBody2D.Velocity.y > 20.0f)
		{
			playerController.OnGround = false;
		}

		// move
		float direction = (float)playerController.InputRightPressed - (float)playerController.InputLeftPressed;
		physicsBody2D.Velocity.x = direction * 100.0f;

		// jump
		if (playerController.InputJumpPressed && playerController.CanJump && playerController.OnGround)
		{
			physicsBody2D.Velocity.y = -200.0f;
			playerController.CanJump = false;
			playerController.OnGround = false;
		}
		if (!playerController.InputJumpPressed)
		{
			playerController.CanJump = true;
		}

	});
};

void PlayerControllerSystem::OnRender2D()
{
	// insert code ...
};

void PlayerControllerSystem::OnInputEvent(const InputEvent& event)
{
	ForEach([&event](PlayerController& playerController, PhysicsBody2D& physicsBody2D)
	{
		if (event.GetType() != InputEventType::KEYBOARD) return;

		// cast input event to keyboard type
		InputEventKeyboard keyEvent = event.Get<InputEventKeyboard>();

		// get input direction
		if (keyEvent.Code == GLFW_KEY_LEFT)
			playerController.InputLeftPressed = keyEvent.Pressed;

		if (keyEvent.Code == GLFW_KEY_RIGHT)
			playerController.InputRightPressed = keyEvent.Pressed;		
	
		// jump just pressed
		if (keyEvent.Code == GLFW_KEY_SPACE)
			playerController.InputJumpPressed = keyEvent.Pressed;
		
	});
};
