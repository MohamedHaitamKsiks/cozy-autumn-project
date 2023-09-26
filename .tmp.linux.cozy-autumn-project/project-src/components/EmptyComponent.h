#ifndef COMPONENT_EMPTYCOMPONENT_H
#define COMPONENT_EMPTYCOMPONENT_H

#include "ASEngine.h"

using namespace ASEngine;


// empty components for systems without any components
struct EmptyComponent: public TComponent<EmptyComponent>
{
	int Placeholder;
};

#endif // COMPONENT_EMPTYCOMPONENT_H