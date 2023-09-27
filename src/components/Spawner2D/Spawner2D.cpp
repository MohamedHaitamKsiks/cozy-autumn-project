#include "Spawner2D.h"

EXPORT(Spawner2D, SceneName, SpawnTransform2D)

void Spawner2D::OnCreate()
{
    // get scene
    ResourceID sceneID = ResourceManager<Scene>::GetResourceId(SceneName);
    Scene scene = ResourceManager<Scene>::Get(sceneID);

    // add transform to entity
    auto& entityBuidlers = scene.GetEntityBuilders();
    for (auto& entityBuilder: entityBuidlers)
    {
        entityBuilder.AddComponents<Transform2D>(SpawnTransform2D);
    }

    scene.Instantiate();
}