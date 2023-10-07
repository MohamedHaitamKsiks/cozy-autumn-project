#ifndef SYSTEM_PARALLAXRENDERINGSYSTEM2D_H
#define SYSTEM_PARALLAXRENDERINGSYSTEM2D_H

#include "components/ParallaxLayer2D/ParallaxLayer2D.h"
#include "components/Transform2D/Transform2D.h"

#include "systems/RenderingSystem2D/RenderingSystem2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class ParallaxRenderingSystem2D: public System<ParallaxLayer2D, Transform2D>
{
public:
	ParallaxRenderingSystem2D();

private:
	float m_Time = 0.0f;

	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_PARALLAXRENDERINGSYSTEM2D_H