#ifndef COMPONENT_VISIBILITYNOTIFIER2D_H
#define COMPONENT_VISIBILITYNOTIFIER2D_H

#include "ASEngine.h"

using namespace ASEngine;

struct VisibilityNotifier2D: public TComponent<VisibilityNotifier2D>
{
	// is visible on screen
	bool Visible = false;
};

#endif // COMPONENT_VISIBILITYNOTIFIER2D_H