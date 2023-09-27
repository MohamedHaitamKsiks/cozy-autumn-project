#ifndef COMPONENT_PLAYERCONTROLLER_H
#define COMPONENT_PLAYERCONTROLLER_H

#include "ASEngine.h"

using namespace ASEngine;



struct PlayerController: public TComponent<PlayerController>
{
	// player state
	UniqueString State;
	bool CanJump = true;
	bool OnGround = false;

	// sprite animator
	ResourceID SpriteID;
	

	// input
	bool InputLeftPressed = false;
	bool InputRightPressed = false;
	bool InputJumpPressed = false;

	// on create
	void OnCreate();
};

#endif // COMPONENT_PLAYERCONTROLLER_H