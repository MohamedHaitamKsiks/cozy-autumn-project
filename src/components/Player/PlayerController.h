#ifndef COMPONENT_PLAYERCONTROLLER_H
#define COMPONENT_PLAYERCONTROLLER_H

#include "ASEngine.h"

using namespace ASEngine;

// define constants
#define PLAYER_ACC 800.0f
#define PLAYER_FALL_ACC 650.0f
#define PLAYER_FALL_DEC 150.0f

#define PLAYER_MAX_SPEED 150.0f
#define PLAYER_UP_GRAVITY 450.0f
#define PLAYER_DOWN_GRAVITY 800.0f
#define PLAYER_JUMP_FORCE 220.0f
#define PLAYER_WALL_FALL_SPEED 300.0f
// 300 ms jump buffer
#define PLAYER_JUMP_BUFFER 0.2f 
#define PLAYER_LAND_DURATION 0.13f

struct PlayerController: public TComponent<PlayerController>
{
	// player state
	UniqueString State;
	// cache states name
	static UniqueString FreeState;
	static UniqueString WallClimpState;

	float JumpBuffer = 0.0f;
	bool CanJump = true;
	bool OnGround = false;

	float TimeSinceLand = 0.0f;

	// look direction
	float LookDirection = 1;

	// input
	bool InputLeftPressed = false;
	bool InputRightPressed = false;
	bool InputJumpPressed = false;

	void OnCreate();

};

#endif // COMPONENT_PLAYERCONTROLLER_H