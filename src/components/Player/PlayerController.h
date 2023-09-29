#ifndef COMPONENT_PLAYERCONTROLLER_H
#define COMPONENT_PLAYERCONTROLLER_H

#include "ASEngine.h"

using namespace ASEngine;


struct PlayerController: public TComponent<PlayerController>
{
	// player state
	UniqueString State;

	float JumpBuffer = 0.0f;
	bool CanJump = true;
	bool OnGround = false;

	// look direction
	float LookDirection = 1;

	// input
	bool InputLeftPressed = false;
	bool InputRightPressed = false;
	bool InputJumpPressed = false;

};

#endif // COMPONENT_PLAYERCONTROLLER_H