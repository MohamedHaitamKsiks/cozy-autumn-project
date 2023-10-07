#include "Pearl.h"

EXPORT(Pearl, CreatePlayer, DestroyPlayer, PearlSpriteName, PearlParticlesSpriteName, PearlDisableSpriteName, PearlDestroySpriteName, PearlCreateSpriteName)

void Pearl::OnCreate()
{
    PearlSpriteID = ResourceManager<Sprite>::GetResourceId(PearlSpriteName);
    PearlParticlesSpriteID = ResourceManager<Sprite>::GetResourceId(PearlParticlesSpriteName);
    PearlDisableSpriteID = ResourceManager<Sprite>::GetResourceId(PearlDisableSpriteName);
    PearlDestroySpriteID = ResourceManager<Sprite>::GetResourceId(PearlDestroySpriteName);
    PearlCreateSpriteID = ResourceManager<Sprite>::GetResourceId(PearlCreateSpriteName);
}
