#ifndef SYSTEM_PARTICLESYSTEM2D_H
#define SYSTEM_PARTICLESYSTEM2D_H

#include "components/ParticleEmitter2D/ParticleEmitter2D.h"
#include "systems/RenderingSystem2D/RenderingSystem2D.h"

#include "ASEngine.h"

using namespace ASEngine;


class ParticleSystem2D: public System<ParticleEmitter2D>
{

	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_PARTICLESYSTEM2D_H