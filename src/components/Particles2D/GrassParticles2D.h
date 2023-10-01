#ifndef COMPONENT_GRASSPARTICLES2D_H
#define COMPONENT_GRASSPARTICLES2D_H

#include "ASEngine.h"

using namespace ASEngine;

struct GrassBlade
{
	vec2 Position;
	float Rotation = 0.0f;

	int Frame = 0;

	float DefaultRotation = 0.0f;
	float DefaultScale = 1.0f;
};

struct GrassParticles2D: public TComponent<GrassParticles2D>
{
	TDynamicArray<GrassBlade> GrassBlades{};
	float PressionPosition = 0.0f;
	bool OnPression = false;
	float Width = 0.0f;

	void OnCreate();
};

#endif // COMPONENT_GRASSPARTICLES2D_H