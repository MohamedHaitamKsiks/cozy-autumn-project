#ifndef COMPONENT_CAMERACONTROLLER2D_H
#define COMPONENT_CAMERACONTROLLER2D_H

#include "ASEngine.h"

using namespace ASEngine;

struct CameraController2D: public TComponent<CameraController2D>
{
	vec2 Position = vec2::ZERO();
	float Zoom = 1.0f;

	vec2 TransitionOffset = vec2::ZERO();
	float TransitionSpeed = 0.0f;
	bool Transition = false;

	vec2 ShakeOffset = vec2::ZERO();
	float ShakeMag = 0.0f;
	float ShakeFreq = 0.0f;
	float ShakeAngle = 0.0f;
	float ShakeTime = 0.0f;
	float ShakeDuration = 1.0f;
	
	float Time = 0.0f;

	float SlowTimer = 0.0f;
	
	vec2 LookOffset = vec2::ZERO();
	float LookDistance = 0.0f;
	float LookSpeed = 4.0f;

};

#endif // COMPONENT_CAMERACONTROLLER2D_H