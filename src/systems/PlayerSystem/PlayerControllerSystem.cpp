#include "PlayerControllerSystem.h"

void PlayerControllerSystem::OnCreate()
{
	// insert code ...
};

void PlayerControllerSystem::OnUpdate(float delta)
{
	ForEach([delta](PlayerController& playerController, PhysicsBody2D& physicsBody2D, Transform2D& transform2D)
	{
		// ground
		if (physicsBody2D.OnGround)
		{
			physicsBody2D.Velocity.y = 0.0f;
			playerController.OnGround = true;
		}
		else if (physicsBody2D.Velocity.y > 20.0f)
		{
			playerController.OnGround = false;
		}

		// celling collision
		if (physicsBody2D.OnCeilling)
			physicsBody2D.Velocity.y = 0.0f;

		// wall collision
		if (physicsBody2D.OnWall)
			physicsBody2D.Velocity.x = 0.0f; 

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
	ForEach([](PlayerController& playerController, PhysicsBody2D& physicsBody2D, Transform2D& transform2D)
	{
		SpriteDrawInfo spriteInfo;
		spriteInfo.Centered = true;
		spriteInfo.Layer = DrawLayer::Player;
		spriteInfo.SpriteID = playerController.SpriteID;

		RenderingSystem2D::DrawSprite(spriteInfo, transform2D);
	});
};

void PlayerControllerSystem::OnInputEvent(const InputEvent& event)
{
	ForEach([&event](PlayerController& playerController, PhysicsBody2D& physicsBody2D, Transform2D& transform2D)
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
