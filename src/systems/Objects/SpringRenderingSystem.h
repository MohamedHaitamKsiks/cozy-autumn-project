#ifndef SYSTEM_SPRINGRENDERINGSYSTEM_H
#define SYSTEM_SPRINGRENDERINGSYSTEM_H

#include "components/Objects/Spring.h"
#include "components/AnimatedSprite2D/AnimatedSprite2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class SpringRenderingSystem: public System<Spring, AnimatedSprite2D>
{

	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_SPRINGRENDERINGSYSTEM_H