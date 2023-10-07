#ifndef SYSTEM_WORLDLEAFPARTICLESSYSTEM_H
#define SYSTEM_WORLDLEAFPARTICLESSYSTEM_H

#include "components/World2D/World2D.h"
#include "components/ParticleEmitter2D/ParticleEmitter2D.h"

#include "systems/RenderingSystem2D/RenderingSystem2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class WorldLeafParticlesSystem: public System<ParticleEmitter2D, World2D>
{

	ResourceID m_LeafParticlesID;
	float m_Time = 0.0f;

	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_WORLDLEAFPARTICLESSYSTEM_H