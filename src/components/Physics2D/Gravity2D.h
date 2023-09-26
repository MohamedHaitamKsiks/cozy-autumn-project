#ifndef COMPONENT_GRAVITY2D_H
#define COMPONENT_GRAVITY2D_H

#include "ASEngine.h"

using namespace ASEngine;

struct Gravity2D: public TComponent<Gravity2D>
{
	float Gravity = 0.0f;
};

#endif // COMPONENT_GRAVITY2D_H