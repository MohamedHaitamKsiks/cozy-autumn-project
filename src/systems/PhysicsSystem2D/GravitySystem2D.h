#ifndef SYSTEM_GRAVITYSYSTEM2D_H
#define SYSTEM_GRAVITYSYSTEM2D_H

#include "components/Physics2D/Gravity2D.h"
#include "components/Physics2D/PhysicsBody2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class GravitySystem2D: public System<Gravity2D, PhysicsBody2D>
{

	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_GRAVITYSYSTEM2D_H