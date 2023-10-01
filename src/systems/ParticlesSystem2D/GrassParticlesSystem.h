#ifndef SYSTEM_GRASSPARTICLESSYSTEM_H
#define SYSTEM_GRASSPARTICLESSYSTEM_H

#include "components/Particles2D/GrassParticles2D.h"
#include "components/VisibilityNotifier2D/VisibilityNotifier2D.h"
#include "components/Transform2D/Transform2D.h"

#include "systems/RenderingSystem2D/RenderingSystem2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class GrassParticlesSystem: public System<VisibilityNotifier2D, GrassParticles2D, Transform2D>
{
	ResourceID m_GrassSpriteID;
	float m_Time = 0.0f;

	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_GRASSPARTICLESSYSTEM_H