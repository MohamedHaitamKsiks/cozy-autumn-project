#ifndef SYSTEM_VISIBILITYNOTIFINGSYSTEM2D_H
#define SYSTEM_VISIBILITYNOTIFINGSYSTEM2D_H

#include "components/VisibilityNotifier2D/VisibilityNotifier2D.h"
#include "components/Physics2D/CollisionBox2D.h"
#include "components/Transform2D/Transform2D.h"

#include "systems/PhysicsSystem2D/CollisionSystem2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class VisibilityNotifingSystem2D: public System<VisibilityNotifier2D, CollisionBox2D, Transform2D>
{
public:
	VisibilityNotifingSystem2D();

private:
	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_VISIBILITYNOTIFINGSYSTEM2D_H