#ifndef COMPONENT_PLAYERCONTROLLER_H
#define COMPONENT_PLAYERCONTROLLER_H

#include "components/AudioPlayer2D/AudioPlayer2D.h"

#include "ASEngine.h"

using namespace ASEngine;

// define constants
#define PLAYER_ACC 800.0f
#define PLAYER_FALL_ACC 800.0f
#define PLAYER_FALL_DEC 200.0f

#define PLAYER_MAX_SPEED 150.0f
#define PLAYER_UP_GRAVITY 450.0f
#define PLAYER_DOWN_GRAVITY 800.0f
#define PLAYER_JUMP_FORCE 220.0f
#define PLAYER_WALL_FALL_SPEED 300.0f

#define PLAYER_JUMP_BUFFER 0.2f
#define PLAYER_LAND_DURATION 0.13f

#define PLAYER_DASH_SPEED 500.0f
#define PLAYER_DASH_DURATION 0.12f

#define PLAYER_DEATH_DURATION 1.5f

#define PLAYER_TRANSITION_DURATION 0.5f

struct PlayerController : public TComponent<PlayerController>
{
	// player state
	UniqueString State;
	// cache states name
	static UniqueString FreeState;
	static UniqueString WallClimpState;
	static UniqueString DashState;
	static UniqueString PrepareGroundPoundState;
	static UniqueString GroundPoundState;
	static UniqueString DeathState;
	static UniqueString TransitionState;

	// spawn position
	bool Spawned = true;
	vec2 SpawnPosition = vec2::ZERO();

	// jump data
	float JumpBuffer = 0.0f;
	bool CanJump = true;
	bool OnGround = true;
	float TimeSinceLand = 0.0f;

	// dash timer
	float DashTimer = 0.0f;
	bool CanDash = true;

	// look direction
	float LookDirection = 1;

	// death
	float DeathTimer = 0.0f;

	// particle timer
	float ParticleTimer = 0.0f;
	UniqueString DustSpriteName;
	ResourceID DustSpriteID;

	// transition
	float TransitionTimer = 0.0f;
	UniqueString LastState;
	vec2 LastVelocity;

	// audio players
	AudioPlayer2D StepPlayer;
	AudioPlayer2D LandPlayer;
	AudioPlayer2D DashPlayer;
	AudioPlayer2D HitPlayer;
	AudioPlayer2D DeathPlayer;
	AudioPlayer2D SpringPlayer;

	// input
	bool InputLeftPressed = false;
	bool InputRightPressed = false;
	bool InputUpPressed = false;
	bool InputDownPressed = false;
	bool InputJumpPressed = false;
	bool InputDashPressed = false;
	bool InputCanDashPress = true;

	void OnCreate();
};

#endif // COMPONENT_PLAYERCONTROLLER_H