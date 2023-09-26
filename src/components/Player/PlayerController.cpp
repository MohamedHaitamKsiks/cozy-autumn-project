#include "PlayerController.h"

EXPORT(PlayerController, State)

void PlayerController::OnCreate()
{
    SpriteID = ResourceManager<Sprite>::GetResourceId(UniqueString("sprites/idle.sprite.json"));
}