#include "PlayerController.h"

EXPORT(PlayerController, DeathPlayer, HitPlayer, SpringPlayer, StepPlayer, DashPlayer, LandPlayer, State, DustSpriteName)

UniqueString PlayerController::FreeState = UNIQUE_STRING_NULL;
UniqueString PlayerController::WallClimpState = UNIQUE_STRING_NULL;
UniqueString PlayerController::DashState = UNIQUE_STRING_NULL;
UniqueString PlayerController::PrepareGroundPoundState = UNIQUE_STRING_NULL;
UniqueString PlayerController::GroundPoundState = UNIQUE_STRING_NULL;
UniqueString PlayerController::DeathState = UNIQUE_STRING_NULL;
UniqueString PlayerController::TransitionState = UNIQUE_STRING_NULL;


void PlayerController::OnCreate()
{
    FreeState = UniqueString("Free");
    WallClimpState = UniqueString("WallClimp");
    DashState = UniqueString("DashState");
    PrepareGroundPoundState = UniqueString("PrepareGroundPound");
    GroundPoundState = UniqueString("GroundPound");
    DeathState = UniqueString("Death");
    TransitionState = UniqueString("Transition");

    DustSpriteID = ResourceManager<Sprite>::GetResourceId(DustSpriteName);
}
