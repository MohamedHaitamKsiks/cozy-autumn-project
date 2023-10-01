#ifndef SYSTEM_SPAWNINGSYSTEM2D_H
#define SYSTEM_SPAWNINGSYSTEM2D_H

#include "components/EmptyComponent.h"
#include "components/Transform2D/Transform2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class SpawningSystem2D: public System<EmptyComponent>
{
public:
	template<typename T>
	static void AddComponentToScene(Scene& scene, const T& component)
	{
		for (auto &builder : scene.GetEntityBuilders())
			builder.AddComponents(component);
	}


private:
	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_SPAWNINGSYSTEM2D_H