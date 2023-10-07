#ifndef SYSTEM_PEARLRENDERINGSYSTEM_H
#define SYSTEM_PEARLRENDERINGSYSTEM_H

#include "components/Objects/Pearl.h"
#include "components/AnimatedSprite2D/AnimatedSprite2D.h"
#include "components/VisibilityNotifier2D/VisibilityNotifier2D.h"
#include "components/Transform2D/Transform2D.h"
#include "components/ParticleEmitter2D/ParticleEmitter2D.h"

#include "systems/CameraSystem2D/CameraSystem2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class PearlRenderingSystem: public System<VisibilityNotifier2D, Pearl, ParticleEmitter2D, AnimatedSprite2D, Transform2D>
{
	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);
};

#endif // SYSTEM_PEARLRENDERINGSYSTEM_H