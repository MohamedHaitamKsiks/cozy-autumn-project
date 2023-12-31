#include "PlayerLevelTransitionSystem.h"

void PlayerLevelTransitionSystem::OnCreate()
{
	// insert code ...
};

void PlayerLevelTransitionSystem::OnUpdate(float delta)
{
	World2D* world2D = World2D::Instance;
	if (!world2D) return;

	auto& currentLevel = world2D->Levels[world2D->CurrentLevelID];

	ForEach([this, &currentLevel, world2D] (PlayerController& playerController, PhysicsBody2D& physicsBody2D, CameraController2D& cameraController2D, Transform2D& transform2D)
	{
		// check if player out of bound
		if (!PositionInLevelBound(transform2D.Position, currentLevel))
		{
			// find level that player is in bound
			for (int i = 0; i < world2D->Levels.GetSize(); i++)
			{
				if (PositionInLevelBound(transform2D.Position, world2D->Levels[i]))
				{
					world2D->CurrentLevelID = i;
					cameraController2D.Transition = true;

					//change spawn position
					playerController.Spawned = true;

					// transittion player
					playerController.LastState = playerController.State;
					playerController.LastVelocity = physicsBody2D.Velocity;

					playerController.TransitionTimer = PLAYER_TRANSITION_DURATION;

					physicsBody2D.IsStatic = true;

					playerController.State = PlayerController::TransitionState;

					return;
				}
			}
		}
	});
	

};

void PlayerLevelTransitionSystem::OnRender2D()
{
	// insert code ...
};

void PlayerLevelTransitionSystem::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
