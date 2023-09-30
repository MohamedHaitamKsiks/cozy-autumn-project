#include "PlayerController.h"

EXPORT(PlayerController, State)

UniqueString PlayerController::FreeState = UNIQUE_STRING_NULL;
UniqueString PlayerController::WallClimpState = UNIQUE_STRING_NULL;


void PlayerController::OnCreate()
{
    FreeState = UniqueString("Free");
    WallClimpState = UniqueString("WallClimp");
}
