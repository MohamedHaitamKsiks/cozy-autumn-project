#ifndef COMPONENT_PARALLAXLAYER2D_H
#define COMPONENT_PARALLAXLAYER2D_H

#include "ASEngine.h"

using namespace ASEngine;

struct ParallaxLayer2D: public TComponent<ParallaxLayer2D>
{
	UniqueString BackgroundName;
	ResourceID BackgroundID;
	int BackgroundFrame = 0;

	float ScrollScale = 0.0f;

	void OnCreate();
};

#endif // COMPONENT_PARALLAXLAYER2D_H