#ifndef SYSTEM_SPAWNINGSYSTEM2D_H
#define SYSTEM_SPAWNINGSYSTEM2D_H

#include "components/EmptyComponent.h"
#include "components/Transform2D/Transform2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class SpawningSystem2D: public System<EmptyComponent>
{
public:
	static void SpawnSceneAt(const Scene& scene, const Transform2D& transform2D);

private:
	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_SPAWNINGSYSTEM2D_H