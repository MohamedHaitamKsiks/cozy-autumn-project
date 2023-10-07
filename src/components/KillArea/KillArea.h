#ifndef COMPONENT_KILLAREA_H
#define COMPONENT_KILLAREA_H

#include "ASEngine.h"

using namespace ASEngine;

struct KillArea: public TComponent<KillArea>
{
	bool Collision = false;
};

#endif // COMPONENT_KILLAREA_H