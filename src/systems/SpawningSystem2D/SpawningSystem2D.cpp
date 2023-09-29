#include "SpawningSystem2D.h"

void SpawningSystem2D::SpawnSceneAt(const Scene &scene, const Transform2D &transform2D)
{
	Scene newScene = scene;
	for (auto &builder : newScene.GetEntityBuilders())
	{
		builder.AddComponents(transform2D);
	}

	newScene.Instantiate();
}

void SpawningSystem2D::OnCreate(){
    // insert code ...
};

void SpawningSystem2D::OnUpdate(float delta)
{
	// insert code ...
};

void SpawningSystem2D::OnRender2D()
{
	// insert code ...
};

void SpawningSystem2D::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
