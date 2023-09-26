#ifndef COMPONENT_COLLISIONBOX2D_H
#define COMPONENT_COLLISIONBOX2D_H

#include "ASEngine.h"

using namespace ASEngine;

// collision layers are bitmask => 32 layer
using LayerBitMask = uint32_t;

struct CollisionBox2D: public TComponent<CollisionBox2D>
{
	vec2 Size = vec2::ZERO();

	vec2 Offset = vec2::ZERO();
	bool IsCentered = false;

	LayerBitMask CollisionLayers = 0;

	bool DrawDebug = true;
};

#endif // COMPONENT_COLLISIONBOX2D_H