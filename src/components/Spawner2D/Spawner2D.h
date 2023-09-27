#ifndef COMPONENT_SPAWNER2D_H
#define COMPONENT_SPAWNER2D_H

#include "components/Transform2D/Transform2D.h"

#include "ASEngine.h"

using namespace ASEngine;

// scenes spawned must not contain transform components
struct Spawner2D: public TComponent<Spawner2D>
{
	UniqueString SceneName;
	Transform2D SpawnTransform2D;

	void OnCreate();
};

#endif // COMPONENT_SPAWNER2D_H