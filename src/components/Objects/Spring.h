#ifndef COMPONENT_SPRING_H
#define COMPONENT_SPRING_H

#include "ASEngine.h"

using namespace ASEngine;

struct Spring: public TComponent<Spring>
{
	bool Collision = false;
};

#endif // COMPONENT_SPRING_H